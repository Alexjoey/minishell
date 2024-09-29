/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:54:50 by amylle            #+#    #+#             */
/*   Updated: 2024/09/03 01:55:56 by amylle           ###   ########.fr       */
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

//tries to find command in either bin/paths or just relative path
//then executes
int	find_cmd(char **split, t_tools *tools)
{
	char	*pathcmd;
	int		i;

	i = -1;
	pathcmd = NULL;
	if (isbuiltin(split[0]))
		exit(do_builtin(tools, split));
	if (!access(split[0], F_OK))
		execve(split[0], split, tools->envp);
	while (tools->paths[++i])
	{
		pathcmd = ft_strjoin(tools->paths[i], split[0]);
		if (!access(pathcmd, F_OK))
			execve(pathcmd, split, tools->envp);
		free(pathcmd);
	}
	printf("minishell: command not found: %s\n", split[0]);
	exit (127);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".tmpheredoc", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	line = readline("heredoc> ");
	while (ft_strncmp(delimiter, line, ft_strlen(line)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("heredoc> ");
	}
	free (line);
	close (fd);
	fd = open(".tmpheredoc", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putendl_fd("minishell: piping error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(char *std_in)
{
	int	fd;

	if (ft_strncmp("< ", std_in, 2) == 0)
	{
		fd = open(std_in + 2, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: infile: No such file or directory: ", STDERR_FILENO);
			ft_putendl_fd(std_in + 2, STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			ft_putendl_fd("minishell: piping error", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close (fd);
	}
	else if (ft_strncmp("<< ", std_in, 3) == 0)
	{
		if (handle_heredoc(std_in + 3) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	make_fork(t_args *args, t_tools *tools)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		find_cmd(args->split, tools);
		exit (0);
	}
	waitpid(pid, &status, 0);
	return (0);
}

//
int	execute(t_pars_start *parser, t_tools *tools)
{
	t_args	*args;

	args = parser->args_start;
	if (parser->std_in != NULL)
		if (handle_input_redirection(parser->std_in) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	while(args)
	{
		make_fork(args, tools);
		args = args->nxt;
	}
	dup2(0, STDIN_FILENO);
	return (0);
}
