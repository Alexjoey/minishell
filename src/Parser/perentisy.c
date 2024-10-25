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

static char	*p_make_charp(char c, t_tools *tools)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (str == NULL)
	{
		parser_error(tools);
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*p_perentisy_add(char *tmp, char *c, bool *quote)
{
	if (*quote)
	{
		*quote = false;
		tmp = ft_strjoinfree(tmp, c);
		tmp = ft_strjoinfree(tmp, "\n");
	}
	else
	{
		*quote = true;
		tmp = ft_strjoinfree(tmp, "\n");
		tmp = ft_strjoinfree(tmp, c);
	}
	return (tmp);
}

void	p_perentisy_remove(t_args *arg, t_tools *tools)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (arg->split[i])
	{
		if ((arg->split[i][0] == (char)34) || (arg->split[i][0] == (char) 39))
		{
			j = 1;
			new = (char *)ft_calloc(ft_strlen(arg->split[i]) - 1, sizeof(char));
			if (new == NULL)
				return (parser_error(tools));
			while (ft_strlen(arg->split[i]) - 1 > (size_t)j)
			{
				new[j - 1] = arg->split[i][j];
				j++;
			}
			new[j] = '\0';
			free(arg->split[i]);
			arg->split[i] = new;
		}
		i++;
	}
}

void	p_perentisy_check(t_args *arg, t_tools *tools)
{
	int		i;
	char	*tmp;
	char	*c;
	bool	quote;

	tmp = NULL;
	quote = false;
	i = 0;
	while (arg->str[i])
	{
		c = p_make_charp(arg->str[i], tools);
		if (arg->str[i] == (char)39
			|| ((arg->str[i] == (char)34) && !(arg->str[i - 1] == (char) 92)))
			tmp = p_perentisy_add(tmp, c, &quote);
		else if (arg->str[i] == (char)32 && !quote)
			tmp = ft_strjoinfree(tmp, "\n");
		else
			tmp = ft_strjoinfree(tmp, c);
		i++;
		free(c);
		if (tmp == NULL)
			return (parser_error(tools));
	}
	arg->split = ft_split(tmp, (char) 10);
	free(tmp);
}
