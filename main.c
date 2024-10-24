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

#include "libft/inc/libft.h"
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

void	ft_unlink_heredocs(t_list	**std_in)
{
	t_list	*curr;

	curr = *std_in;
	while (curr)
	{
		if (!ft_strncmp(curr->content, "<<", 2))
			unlink(curr->content + 2);
		curr = curr->next;
	}
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
		ft_lstclear(&args->std_o, free);
		ft_unlink_heredocs(&args->std_in);
		ft_lstclear(&args->std_in, free);
		if (!args->nxt)
		{
			free(args);
			break ;
		}
		args = args->nxt;
	}
	free (parser);
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
		i = ft_strlen(tools->envp[i]) - 5;
	else
		i = 0;
	rl_text = ft_strjoin("\e[36m~", cwd + i);
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
		if (g_signum != 0)
			tools->errornum = g_signum + 128;
		g_signum = 0;
		tools->parser = parser_input(line, tools);
		add_history(line);
		free (line);
		execute(tools->parser->args_start, tools);
		reset_parser(tools->parser);
	}
}
