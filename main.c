/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:17:10 by amylle            #+#    #+#             */
/*   Updated: 2024/07/24 16:20:53 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include "src/minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**splitpath;
	char	*tmp;

	path = NULL;
	splitpath = NULL;
	i = find_envp_index(envp, "PATH=");
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

t_tools	*init_tools(char **envp)
{
	t_tools	*tools;

	tools = ft_calloc(1, sizeof(t_tools));
	tools->paths = get_paths(envp);
	tools->envp = ft_duparray(envp);
	return (tools);
}

int	find_envp_index(char **envp, char *path)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], path, ft_strlen(path)) == 0)
			return (i);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	*tools;

	(void)argv;
	if (argc != 1)
	{
		printf("This program does not accept any input\n");
		return (0);
	}
	tools = init_tools(envp);
	while (1)
	{
		line = readline("minishell ~> ");
		add_history(line);
		execute(line, tools);
		free (line);
	}
}
