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

int		g_signum;

t_tools	*init_tools(char **envp)
{
	t_tools	*tools;

	tools = ft_calloc(1, sizeof(t_tools));
	tools->envp = ft_duparray(envp);
	g_signum = 0;
	return (tools);
}

//returns -1 if it finds nothin, returns -2 if its supposed to be errornum
//otherwise return index of path in envp
int	find_envp_index(char **envp, char *path)
{
	int	i;
	int	eq_len;

	i = -1;
	if (path)
	{
		if (!ft_strncmp("?", path, 2))
			return (-2);
		while (envp[++i])
		{
			eq_len = 0;
			while (envp[i][eq_len] && envp[i][eq_len] != '=')
				eq_len++;
			if (!ft_strncmp(envp[i], path, eq_len) && path[eq_len] == '\0')
				return (i);
		}
	}
	return (-1);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	reset_parser(t_pars_start *parser, t_tools *tools)
{
	t_args	*args;

	args = parser->args_start;
	while (args)
	{
		if (args->prev)
			free(args->prev);
		free (args->str);
		free_array (args->split);
		if (!args->nxt)
		{
			free(args);
			break;
		}
		args = args->nxt;
	}
	free (parser->std_o);
	free (parser->std_in);
	free (parser);
	unlink(".tmpheredoc");
	if (g_signum != 0)
		tools->errornum = 128 + g_signum;
	g_signum = 0;
}

//shows directory as readline message, with colors etc
char	*ft_readline(t_tools *tools)
{
	char	*cwd;
	char	*rl_text;
	int		i;
	char	*ret;

	cwd = NULL;
	rl_text = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (readline("minishell > "));
	i = find_envp_index(tools->envp, "HOME");
	if (i >= 0 && ft_strnstr(cwd, tools->envp[i] + 5, ft_strlen(cwd)))
		i = ft_strlen(tools->envp[i]) - 4;
	else
		i = 0;
	rl_text = ft_strjoin("\e[36m", cwd + i);
	rl_text = ft_strjoinfree(rl_text, " $ \e[0m");
	free (cwd);
	if (!rl_text)
		return (readline("minishell > "));
	ret = readline(rl_text);
	free (rl_text);
	return (ret);
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
		init_signals();
		line = ft_readline(tools);
		if (line == NULL)
			return (free_tools(tools));
		tools->parser = parser_input(line, tools);
		add_history(line);
		free (line);
		execute(tools->parser->args_start, tools);
		reset_parser(tools->parser, tools);
	}
}
