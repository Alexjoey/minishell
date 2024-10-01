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
#include "src/Parser/Parser.h"
#include "src/minishell.h"

//just gets $PATH
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
	tools->parser = ft_calloc(2, sizeof(t_pars_start));
	tools->parser->args_start = ft_calloc(3, sizeof(t_args));
	tools->parser->args_start[0].split = ft_split("ps aux", ' ');
	tools->parser->args_start[0].nxt = &tools->parser->args_start[1];
	tools->parser->args_start[1].prev = &tools->parser->args_start[0];
	tools->parser->args_start[1].split = ft_split("grep python", ' ');
	tools->parser->args_start[1].nxt = &tools->parser->args_start[2];
	tools->parser->args_start[2].prev = &tools->parser->args_start[1];
	tools->parser->args_start[2].split = ft_split("awk '{print", ' ');
	tools->parser->std_o = ft_strdup(">> text.txt");
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

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	reset_parser(t_pars_start *parser)
{
	t_args	*args;

	args = parser->args_start;
	while (args)
	{
		free (args->str);
		free_array (args->split);
		free (args->extracted);
		args = args->nxt;
	}
	free (parser->std_o);
	free (parser->std_in);
	free (parser);
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
		execute(tools->parser, tools);
		free (line);
//		reset_parser(tools->parser);
		printf("end of while loop\n");
	}
}
