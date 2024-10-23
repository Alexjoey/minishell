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
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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

//makes a fork for each args, tries to do redirections and pipes
//will return errornum
int	make_fork(t_args *args, t_tools *tools, int pipefd[2])
{
	int	pid;
	int	status;
	int	fd_in;

	signal(SIGQUIT, sigquit_handler);
	if (args->prev)
		fd_in = pipefd[0];
	if (args->nxt)
		pipe(pipefd);
	pid = fork();
	if (pid < 0)
		return (ft_error("minishell: Failed to create fork", NULL));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (handle_pipes(args, pipefd, fd_in) == EXIT_FAILURE)
			exit (1);
		find_cmd(args->split, tools);
	}
	signal(SIGINT, sigint_fork_handler);
	waitpid(pid, &status, 0);
	if (args->prev)
		close(fd_in);
	if (args->nxt)
		close(pipefd[1]);
	if (WIFSIGNALED(status))
		return (g_signum + 128);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

//
int	execute(t_args *args, t_tools *tools)
{
	int		pipefd[2];

	if (tools->parser->x_args == 1 && is_nofork_builtin(args->split) == true)
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
