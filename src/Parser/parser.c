/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:36:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 14:14:22 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

t_pars_start	*parser_input(char *line)
{
	t_pars_start	*line_s;

	line_s = calloc(sizeof(t_pars_start *), 1);
	line_s->args_start = NULL;
	line_s->std_in = "";
	line_s->std_o = "";
	line_s->x_args = 0;
	p_line_s_init(line_s, line);
	return (line_s);
}
