/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:36:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/09/23 01:13:25 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

bool	parser_input(char *line)
{
	t_pars_start	line_s;
	line_s.args_start = NULL;
	line_s.std_in = STDIN_FILENO;
	line_s.std_o = STDOUT_FILENO;
	line_s.x_args = NULL;

	p_line_s_init(&line_s, line);

}
