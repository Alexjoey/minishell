/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:36:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 16:52:17 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "../minishell.h"

void	parser_error(t_tools *tools, char *err)
{
	tools->pars_good = false;
	ft_putendl_fd(err, STDERR_FILENO);
	return ;
}

static void	p_fil_type_arg(t_args *new, char *arg, t_tools *tools)
{
	int		idx;

	new->str = arg;
	new->split = ft_split_ignoring_parentheses(arg, ' ');
	idx = -1;
	while (new->split && new->split[++idx])
		new->split[idx] = replace_dollarsigns(new->split[idx], tools);
	if (p_u_get_std_out(new) || p_u_get_std_in(new))
		return (parser_error(tools, ""));
	p_perentisy_remove(new->split);
}

/*
	fills all the needed args
	WIP need to add Maloc shit all temp code for now
	Will add a 'new' link in the list in the last pos
*/
bool	p_fil_inset_arg(t_pars_start *line_i, char *arg, t_tools *tool)
{
	t_args			*curr;
	t_args			*new;

	new = ft_calloc(1, sizeof(t_args));
	if (!new)
		return (false);
	if (line_i->args_start)
	{
		curr = line_i->args_start;
		while (curr->nxt)
			curr = curr->nxt;
		curr->nxt = new;
		new->prev = curr;
	}
	else
		line_i->args_start = new;
	new->init_s = line_i;
	new->index = line_i->x_args;
	p_fil_type_arg(new, arg, tool);
	if (new->split)
		line_i->x_args += 1;
	return (tool->pars_good);
}

/*
	init phase of the executor struct
	Null all needed vars to then fill them with precious DATA :D
*/
void	p_line_s_init(t_pars_start *line_i, char *line, t_tools *tools)
{
	char	**split;
	int		i;

	split = NULL;
	split = ft_split_ignoring_parentheses(line, '|');
	i = 0;
	while (split && split[i])
	{
		if (!p_fil_inset_arg(line_i, split[i], tools))
			return (parser_error(tools, ""));
		i++;
	}
	free(split);
}

t_pars_start	*parser_input(char *line, t_tools *tools)
{
	t_pars_start	*line_s;

	tools->pars_good = true;
	line_s = ft_calloc(sizeof(t_pars_start), 1);
	if (line_s == NULL)
	{
		parser_error(tools, "");
		return (NULL);
	}
	p_line_s_init(line_s, line, tools);
	return (line_s);
}
