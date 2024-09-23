/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:30:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/09/23 01:38:46 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

static void p_join_str_extracted(t_args *arg, char** join)
{
	int		idx;
	char	*ret;

	idx = 2;
	ret = ft_strjoin(join[0], join[1]);
	while (join[idx])
	{
		ret = ft_strjoinfree(ret, join[idx]);
		idx++;
	}
	
	arg->extracted = ret;
}

static void	p_fil_type_arg(t_args *new, char *arg)
{
	int 	idx;
	char	**tmp;
	
	idx = 0;
	new->str = arg;
	new->split = ft_split(arg, ' ');
	tmp = ft_split(arg, ' ');
	while (new->split[idx])
	{
		if (ft_strchr(new->split[idx], '$'))
		{
			tmp[idx] = getenv(new->split[idx]++);
			new->split[idx]--;
		}
		else
			tmp[idx] = new->split[idx];
		idx++;
	}
	
	p_join_str_extracted(new, tmp);
}

/*
	filles all the needed args
	WIP need to add Maloc shit all temp code for now
	Will add a 'new' link in the list in the last pos
*/
bool	p_fil_inset_arg(t_pars_start *line_i, char *arg)
{
	t_args			*curr;
	t_args			*new;
	int				idx;

	idx = P_U_get_size_Total(line_i->args_start) + 1;
	new = ft_calloc(1, sizeof(t_args *));
	if (!new)
		return (false);
	p_struct_arg_init(NULL, curr);
	if (line_i->x_args <= idx)
		line_i->x_args = idx;
	curr = line_i->args_start;
	while (curr->nxt)
		curr = curr->nxt;
	new->prev = curr;
	curr->nxt = new;
	new->init_s = line_i;
	new->index = idx;
	p_fil_type_arg(new, arg);
}
