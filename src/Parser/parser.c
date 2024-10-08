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

#include "Parser.h"

t_pars_start	*parser_input(char *line)
{
	t_pars_start	*line_s;

	line_s = ft_calloc(sizeof(t_pars_start), 1);
	p_line_s_init(line_s, line);
	return (line_s);
}
