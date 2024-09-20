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

int	handle_heredoc(char *std_in, t_tools *tools)
{
	return (0);
}

int	handle_input_redirection(char *std_in, t_tools *tools)
{
	int	fd;

	if (std_in == NULL)
		return (STDIN_FILENO);
	if (ft_strncmp("< ", std_in, 2) == 0)
	{
		fd = open(std_in + 2, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: infile: No such file or directory: ", STDERR_FILENO);
			ft_putendl_fd(std_in + 2, STDERR_FILENO);
			return (-1);
		}
		return (fd);
	}
	if (ft_strncmp("<< ", std_in, 3))
	{
		fd = handle_heredoc(std_in + 3, tools);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: infile: No such file or directory: ", STDERR_FILENO);
			ft_putendl_fd(std_in + 3, STDERR_FILENO);
			return (-1);
		}
		return (fd);
	}
	return (-1);
}

//
int	execute(t_pars_start *parser, t_tools *tools)
{
	int fd;

	if (ft_strncmp(parser->args_start->split[0], "cd", 3) == 0)
		return (cd_builtin(parser->args_start->split, tools));
	if (ft_strncmp(parser->args_start->split[0], "exit", 5) == 0)
	{
		exit_builtin(parser->args_start->split, tools);
		exit (0);
	}
	fd = handle_input_redirection(parser->std_in, tools);
	if (fd < 0)
		return (EXIT_FAILURE);
	while(parser->args_start)
	{
	}
	return (0);
}

int	make_fork(t_pars_start *parser, t_tools *tools)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		find_cmd(parser->args_start->split, tools);
	waitpid(pid, &status, 0);
	return (0);
}
