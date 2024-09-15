/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:30:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/09/16 00:36:00 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

static void	p_fil_type_arg(/*TBD*/)
{
	
}

/*
	filles all the needed args
	WIP need to add Maloc shit all temp code for now
*/
bool	p_fil_inset_arg(t_pars_start *line_i, char *arg, int idx)
{
	static t_args	prev_arg;
	t_args			*curr;

	curr = ft_calloc(1, sizeof(t_args *));
	if (!curr)
		return (NULL);
	p_struct_arg_init(NULL, curr);
	if (line_i->x_args <= idx)
		line_i->x_args = idx;
	curr = line_i->args_start;
	while (curr->index && curr->index < idx)
		curr = curr->nxt;
	curr->str = arg;
	curr->index = idx;
}
