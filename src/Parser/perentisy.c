/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perentisy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:32:44 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/25 17:36:58 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//given index i, will shift everything to the left starting from i,
//basically just removing it
static void	remove_char_from_str(char *str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

//given a split, will remove parentheses
//if theres only 1 parenthesis itll just remove that one and move onto next str
void	p_perentisy_remove(char	**split)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	while (split && split[++i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\"' || split[i][j] == '\'')
			{
				if (!ft_strchr(&split[i][j + 1], split[i][j]))
				{
					remove_char_from_str(split[i], j);
					break ;
				}
				tmp = ft_strchr(&split[i][j + 1], split[i][j]) - &split[i][j];
				remove_char_from_str(split[i], j);
				remove_char_from_str(split[i], tmp + 1);
				j += tmp - 2;
			}
			j++;
		}
	}
}
