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

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**splitpath;
	char	*tmp;

	i = -1;
	path = NULL;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_substr(envp[i], 6, ft_strlen(envp[i]) - 6);
	splitpath = ft_split(path, ':');
	free (path);
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

int	do_cmd(char *line, char **envp)
{
	char	**splitline;
	char	**paths;
	char	*pathcmd;
	int		i;

	i = -1;
	pathcmd = NULL;
	splitline = ft_split(line, ' ');
	if (!access(splitline[0], F_OK))
	{
		execve(splitline[0], splitline, envp);
		exit (0);
	}
	paths = get_paths(envp);
	while (paths[++i])
	{
		pathcmd = ft_strjoin(paths[i], splitline[0]);
		if (!access(pathcmd, F_OK))
			execve(pathcmd, splitline, envp);
		free(pathcmd);
	}
	printf("minishell: command not found: %s\n", splitline[0]);
	free_array(paths);
	free_array(splitline);
	exit (127);
}

int	execute(char *line, char **envp)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		do_cmd(line, envp);
	waitpid(pid, &status, 0);
	return (0);
}
