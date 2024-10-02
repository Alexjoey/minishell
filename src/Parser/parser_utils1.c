/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:47:59 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/02 22:58:01 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*List of functions that helps navigating the Struct*/
//TBA

int	p_u_get_size_total(t_args *arg_list)
{
	t_args	*temp;
	int		i;

	i = 0;
	while (arg_list->prev)
		temp = arg_list->prev;
	while (temp->nxt)
	{
		temp = temp->nxt;
		i++;
	}
	return (i);
}

char	*p_u_get_std_in(t_pars_start *parser)
{
	int	i;

	i = 0;
	if (parser->x_args > 0)
	{
		while (parser->args_start->split[i])
		{
			if ((ft_strnstr(parser->args_start->split[i], "<",
						ft_strlen(parser->args_start->split[i])))
				|| (ft_strnstr(parser->args_start->split[i], "<<",
						ft_strlen(parser->args_start->split[i]))))
				return (ft_strjoin(parser->args_start->split[i - 1],
						parser->args_start->split[i]));
		}
	}
	return ("");
}

char	*p_u_get_std_out(t_pars_start *parser)
{
	int	i;

	i = 0;
	if (parser->x_args > 0)
	{
		while (parser->args_start->split[i])
		{
			if ((ft_strnstr(parser->args_start->split[i], ">",
						ft_strlen(parser->args_start->split[i])))
				|| (ft_strnstr(parser->args_start->split[i], ">>",
						ft_strlen(parser->args_start->split[i]))))
				return (ft_strjoin(parser->args_start->split[i - 1],
						parser->args_start->split[i]));
		}
	}
	return ("");
}
