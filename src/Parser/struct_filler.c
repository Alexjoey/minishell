/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:30:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 17:25:30 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

static char	*p_make_charp(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));

	if (str == NULL)
		return (NULL);

	str[0] = c;
	str[1] = '\0';

	return (str);
}

static void	p_perentisy_check(t_args *arg)
{
	int		i;
	char	*tmp;
	char	*c;

	tmp = NULL;
	i = 0;
	while (arg->str[i])
	{
		c = p_make_charp(arg->str[i]);
		if (arg->str[i] == (char)34 || arg->str[i] == (char)39)
		{
			ft_strjoinfree(tmp, " ");
			ft_strjoinfree(tmp, c);
			ft_strjoinfree(tmp, " ");
		}
		else
			ft_strjoinfree(tmp, c);
		i++;
		free(c);
	}
	arg->split = ft_split(tmp, ' ');
	free(tmp);
}

static void	p_fil_type_arg(t_args *new, char *arg)
{
	int		idx;
	char	**tmp;

	idx = 0;
	new->str = arg;
	tmp = ft_split(arg, ' ');
	if (ft_strchr(new->str, (char)34) || ft_strchr(new->str, (char)39))
		p_perentisy_check(new);
	else
		new->split = ft_split(arg, ' ');
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
	new->split = tmp;
	ft_freearray(tmp);
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

	idx = p_u_get_size_total(line_i->args_start) + 1;
	new = ft_calloc(1, sizeof(t_args));
	if (!new)
		return (false);
	//p_struct_arg_init(NULL, new);
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
	p_fil_type_arg(new, arg);
	return (true);
}
