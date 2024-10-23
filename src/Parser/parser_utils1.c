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
	split[i + 1] = NULL;
}

//made it readable and work properly for now
//still has issues because < and << could have invalid input after or 
//if theres input after < or << it will just disappear and leak
int	p_u_get_std_in(t_args *arg)
{
	int	i;
	char	*tmp;
	char	**split;

	i = 0;
	split = arg->split;
	while (split[i])
	{
		if ((!ft_strncmp(split[i], "<", ft_strlen(split[i])) ||
			!ft_strncmp(split[i], "<<", ft_strlen(split[i])))
			&& split[i + 1])
		{
			if (arg->std_in)
				return (EXIT_FAILURE);
			tmp = ft_strjoin(split[i], split[i + 1]);
			free_and_join_stdinorout_split(split, i);
			arg->std_in = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//need to be able to handle no space inbetween
int	p_u_get_std_out(t_args *args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args->split[i])
	{
		if ((!ft_strncmp(args->split[i], ">", ft_strlen(args->split[i])) ||
			!ft_strncmp(args->split[i], ">>", ft_strlen(args->split[i])))
			&& args->split[i + 1])
		{
			if (args->std_o)
				return (EXIT_FAILURE);
			tmp = ft_strjoin(args->split[i], args->split[i + 1]);
			free_and_join_stdinorout_split(args->split, i);
			args->std_o = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
