/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:54:50 by amylle            #+#    #+#             */
/*   Updated: 2024/10/21 05:43:53 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"
#include <complex.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

//returns 1 if it is builtin
int	isbuiltin(char *str)
{
	if (!ft_strncmp("cd", str, 3) || !ft_strncmp("echo", str, 5) \
		|| !ft_strncmp("pwd", str, 4) || !ft_strncmp("exit", str, 5) \
		|| !ft_strncmp("unset", str, 6) || !ft_strncmp("env", str, 4) \
		|| !ft_strncmp("export", str, 7))
		return (1);
	return (0);
}

int	ft_error(char *errormessage, char *filename)
{
	ft_putstr_fd(errormessage, STDERR_FILENO);
	if (filename)
		ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

//returns a split $PATH
char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**splitpath;
	char	*tmp;

	path = NULL;
	splitpath = NULL;
	i = find_envp_index(envp, "PATH");
	if (i == -1)
		return (NULL);
	path = (envp[i] + ft_strlen("PATH="));
	splitpath = ft_split(path, ':');
	i = -1;
	while (splitpath[++i])
	{
		if (splitpath[i][ft_strlen(splitpath[i]) - 1] != '/')
		{
			tmp = ft_strjoin(splitpath[i], "/");
			free (splitpath[i]);
			splitpath[i] = tmp;
		}
	}
	return (splitpath);
}

//tries to find command in either bin/paths or just relative path
//then executes
int	find_cmd(char **split, t_tools *tools)
{
	char	*pathcmd;
	int		i;
	char	**path;

	i = -1;
	pathcmd = NULL;
	path = get_paths(tools->envp);
	signal(SIGQUIT, SIG_DFL);
	if (isbuiltin(split[0]))
		exit(do_builtin(tools, split));
	if (!access(split[0], F_OK))
		execve(split[0], split, tools->envp);
	while (path && path[++i])
	{
		pathcmd = ft_strjoin(path[i], split[0]);
		if (!access(pathcmd, F_OK))
			execve(pathcmd, split, tools->envp);
		free(pathcmd);
	}
	free_array(path);
	ft_error("minishell: command not found: ", split[0]);
	exit (127);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".tmpheredoc", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	g_global.in_heredoc = true;
	g_global.stophdoc = false;
	line = readline("heredoc> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)) != 0 && g_global.stophdoc == false)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("heredoc> ");
	}
	g_global.in_heredoc = false;
	free (line);
	close (fd);
	fd = open(".tmpheredoc", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe", NULL));
	close (fd);
	unlink(".tmpheredoc");
	if (g_global.stophdoc == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(char *std_in)
{
	int	fd;

	if (ft_strncmp("<<", std_in, 2) != 0)
	{
		fd = open(std_in + 2, O_RDONLY);
		if (fd < 0)
			return (ft_error("minishell: infile: No such file or directory: " \
					, std_in + 1));
		if (dup2(fd, STDIN_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close (fd);
	}
	else if (handle_heredoc(std_in + 2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_output_redirection(char *std_o)
{
	int	fd;

	if (ft_strncmp(">>", std_o, 2) == 0)
		fd = open(std_o + 2, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	else
		fd = open(std_o + 1, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
		return (ft_error("minishell: outfile: No such file or directory: " \
				, std_o + 2));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe\n", NULL));
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_pipes(t_args *args, t_tools *tools, int pipefd[2], int fd_in)
{
	if (!args->prev && tools->parser->std_in)
		if (handle_input_redirection(tools->parser->std_in) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (args->prev)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close(fd_in);
	}
	if (args->nxt)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close(pipefd[1]);
	}
	if (!args->nxt && tools->parser->std_o)
		return (handle_output_redirection(tools->parser->std_o));
	return (EXIT_SUCCESS);
}

//makes a fork for each args, tries to do redirections and pipes
//will return errornum
int	make_fork(t_args *args, t_tools *tools, int pipefd[2])
{
	int	pid;
	int	status;
	int	fd_in;

	if (args->prev)
		fd_in = pipefd[0];
	if (args->nxt)
		pipe(pipefd);
	g_global.in_fork = true;
	pid = fork();
	if (pid < 0)
		return (ft_error("minishell: Failed to create fork", NULL));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (handle_pipes(args, tools, pipefd, fd_in) == EXIT_FAILURE)
			exit (1);
		find_cmd(args->split, tools);
	}
	waitpid(pid, &status, 0);
	if (args->prev)
		close(fd_in);
	if (args->nxt)
		close(pipefd[1]);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	nofork_builtin(char **array)
{
	if (!ft_strncmp(array[0], "exit", ft_strlen(array[0])) || \
		!ft_strncmp(array[0], "cd", ft_strlen(array[0])) || \
		!ft_strncmp(array[0], "export", ft_strlen(array[0])) || \
		!ft_strncmp(array[0], "unset", ft_strlen(array[0])))
		return (true);
	return (false);
}

//
int	execute(t_args *args, t_tools *tools)
{
	int		pipefd[2];

	if (tools->parser->x_args == 1 && nofork_builtin(args->split) == true)
	{
		tools->errornum = do_builtin(tools, args->split);
		return (0);
	}
	while (args)
	{
		tools->errornum = make_fork(args, tools, pipefd);
		args = args->nxt;
	}
	return (0);
}
