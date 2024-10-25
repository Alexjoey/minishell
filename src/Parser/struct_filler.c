/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:30:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/21 08:48:25 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_fil_type_arg(t_args *new, char *arg, t_tools *tools)
{
	int		idx;

	idx = 0;
	new->str = arg;
	if (ft_strchr(new->str, (char)34) || ft_strchr(new->str, (char)39))
		p_perentisy_check(new, tools);
	else
		new->split = ft_split(arg, ' ');
	while (new->split[idx])
	{
		if (ft_strchr(new->split[idx], '$')
			&& !(ft_strchr(new->split[idx], (char) 39)))
		{
			new->split[idx] = replace_dollarsigns(new->split[idx], tools);
		}
		idx++;
	}
	if (p_u_get_std_out(new) || p_u_get_std_in(new))
		return (parser_error(tools));
	p_perentisy_remove(new, tools);
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
	int				idx;

	idx = p_u_get_size_total(line_i->args_start) + 1;
	new = ft_calloc(1, sizeof(t_args));
	if (!new)
		return (false);
	if (line_i->x_args <= idx)
		line_i->x_args = idx;
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
	new->index = idx;
	p_fil_type_arg(new, arg, tool);
	return (tool->pars_good);
}
