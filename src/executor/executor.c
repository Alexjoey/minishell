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
	while(array[++i])
		free (array[i]);
	free (array);
}

char	**get_paths(char **envp)
{
	int	i;
	char *path;
	char **splitpath;

	i = -1;
	path = NULL;
	while(envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_substr(envp[i], 6, ft_strlen(envp[i]) - 6);
			break ;
		}
	}
	splitpath = ft_split(path, ':');
	free (path);
	return (splitpath);
}

int	execute(char *line, char **envp)
{
	char	**splitline;
	char	**paths;
	char	*pathcmd;
	char	*tmp;
	int		i;

	i = -1;
	pathcmd = NULL;
	splitline = ft_split(line, ' ');
	if (!access(splitline[0], F_OK))
		execve(splitline[0], splitline, envp);
	else
	{
		paths = get_paths(envp);
		while(paths[++i])
		{
			tmp = ft_strjoin(paths[i], "/");
			pathcmd = ft_strjoin(tmp, splitline[0]);
			free (tmp);
			if (!access(pathcmd, F_OK))
			{
				execve(pathcmd, splitline, envp);
				printf("yo1\n");
			}
			free(pathcmd);
		}
	}
	free_array(splitline);
	return (0);
}
