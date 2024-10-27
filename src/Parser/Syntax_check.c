/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:40:02 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/27 18:54:33 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "Parser.h"

//searches for c in str, if it encounter a parenthesis itll skip till it finds
//the matching one, if it doesnt find one itll go to the end and return null
//modified to return n till next c
static int	ft_strchrparenthesis_int(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (ft_strchr(&str[i + 1], str[i]))
				i += ft_strchr(&str[i + 1], str[i]) - &str[i] + 1;
			else
				i += ft_strlen(str);
		}
		else
			i++;
	}
	return (i);
}

bool	p_syntax_first_check(char *str, t_tools *tools)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '|')
		parser_error(tools, "minishell: parse error near '|'\n");
	if (str[i + 1] && str[i])
	{
		i += ft_strchrparenthesis_int(str, '|') + 1;
		p_syntax_first_check(&str[i], tools);
	}
	return (tools->pars_good);
}
