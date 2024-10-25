/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:36:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 16:52:17 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_error(t_tools *tools)
{
	tools->pars_good = false;
	return ;
}

t_pars_start	*parser_input(char *line, t_tools *tools)
{
	t_pars_start	*line_s;

	tools->pars_good = true;
	line_s = ft_calloc(sizeof(t_pars_start), 1);
	if (line_s == NULL)
	{
		parser_error(tools);
		return (NULL);
	}
	p_line_s_init(line_s, line, tools);
	return (line_s);
}
