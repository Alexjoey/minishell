/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:17:10 by amylle            #+#    #+#             */
/*   Updated: 2024/10/03 17:26:05 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

t_global g_global;

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
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
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
		if (args->prev)
			free(args->prev);
		free (args->str);
		free_array (args->split);
		args = args->nxt;
	}
	free (parser->args_start);
	free (parser->std_o);
	free (parser->std_in);
	free (parser);
	g_global.stophdoc = false;
	g_global.in_cmd = false;
	g_global.in_heredoc = false;
}

//line = NULL only happens if ctrl-d is pressed,
//which makes this function run, free and exit minshell
int	free_tools(t_tools *tools)
{
	free_array(tools->envp);
	free_array(tools->paths);
	free (tools);
	rl_clear_history();
	return (0);
}

void	sigint_handler(int signal)
{
	(void) signal;
	if (g_global.in_heredoc == false)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global.in_cmd)
	{
		g_global.stophdoc = true;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
	init_signals();
	while (1)
	{
		line = readline("minishell ~> ");
		if (line == NULL)
			return (free_tools(tools));
		tools->parser = parser_input(line, tools);
		add_history(line);
		free (line);
		execute(tools->parser->args_start, tools);
		reset_parser(tools->parser);
	}
}
