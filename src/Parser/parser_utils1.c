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

//give index of the < << >> >, itll free remove, and rejoin the split so the
//input after it wont just get removed and leak
void	free_and_join_stdinorout_split(char **split, int	i)
{
	free (split[i]);
	free (split[i + 1]);
	while (split[i + 2])
	{
		split[i] = split[i + 2];
		i++;
	}
	split[i] = NULL;
}

//made it readable and work properly for now
//still has issues because < and << could have invalid input after or 
//if theres input after < or << it will just disappear and leak
char	*p_u_get_std_in(t_pars_start *parser)
{
	int	i;
	char	*tmp;
	char 	**split;

	i = 0;
	if (parser->x_args <= 0)
		return (NULL);
	split = parser->args_start->split;
	while (split[i])
	{
		if ((!ft_strncmp(split[i], "<", ft_strlen(split[i])) ||
			!ft_strncmp(split[i], "<<", ft_strlen(split[i])))
			&& split[i + 1])
		{
			tmp = ft_strjoin(split[i], split[i + 1]);
			free_and_join_stdinorout_split(split, i);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

//need to be able to handle no space inbetween
char	*p_u_get_std_out(t_pars_start *parser)
{
	int		i;
	t_args	*curr;
	char	*tmp;

	i = 0;
	curr = parser->args_start;
	if (parser->x_args <= 0)
		return (NULL);
	while(curr->nxt)
		curr = curr->nxt;
	while (curr->split[i])
	{
		if ((!ft_strncmp(curr->split[i], ">", ft_strlen(curr->split[i])) ||
			!ft_strncmp(curr->split[i], ">>", ft_strlen(curr->split[i])))
			&& curr->split[i + 1])
		{
			tmp = ft_strjoin(curr->split[i], curr->split[i + 1]);
			free_and_join_stdinorout_split(curr->split, i);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
