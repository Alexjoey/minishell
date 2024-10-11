/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:47:59 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 17:39:50 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
/*List of functions that helps navigating the Struct*/
//TBA

int	p_u_get_size_total(t_args *arg_list)
{
	t_args	*temp;
	int		i;

	i = 0;
	if (!(arg_list))
		return (0);
	if (!(arg_list->prev))
		return (1);
	while (arg_list->prev)
		temp = arg_list->prev;
	while (temp->nxt)
	{
		temp = temp->nxt;
		i++;
	}
	return (i);
}

//strnstr will try to find any substring in a string, u need to use strncmp
//+ this function does not need parser fed to it, just feeding it the split is fine
char	*p_u_get_std_in(t_pars_start *parser)
{
	int	i;
	char	*tmp;

	i = 0;
	if (parser->x_args > 0)
	{
		while (parser->args_start->split[i])
		{
			if ((ft_strnstr(parser->args_start->split[i], "<",
						ft_strlen(parser->args_start->split[i])))
				|| (ft_strnstr(parser->args_start->split[i], "<<",
						ft_strlen(parser->args_start->split[i]))))
				{
					tmp = ft_strjoin(parser->args_start->split[i],
					parser->args_start->split[i + 1]);
					free(parser->args_start->split[i + 1]);
					free(parser->args_start->split[i]);
					parser->args_start->split[i] = NULL;
					return (tmp);
				}
			i++;
		}
	}
	return (NULL);
}

char	*p_u_get_std_out(t_pars_start *parser)
{
	int		i;
	t_args	*curr;
	char	*tmp;

	i = 0;
	curr = parser->args_start;
	if (parser->x_args > 0)
	{
		while(curr->nxt)
			curr = curr->nxt;
		while (curr->split[i])
		{
			if ((ft_strnstr(curr->split[i], ">",
						ft_strlen(curr->split[i])))
				|| (ft_strnstr(curr->split[i], ">>",
						ft_strlen(curr->split[i]))))
				{
					tmp = ft_strjoin(curr->split[i],
					curr->split[i + 1]);
					free(curr->split[i]);
					curr->split[i] = NULL;
					free(curr->split[i + 1]);
					return (tmp);
				}

			i++;
		}
	}
	return (NULL);
}
