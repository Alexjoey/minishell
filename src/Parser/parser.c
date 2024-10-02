/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:36:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/02 22:47:54 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parser_input(char *line)
{
	t_pars_start	line_s;

	line_s.args_start = NULL;
	line_s.std_in = "";
	line_s.std_o = "";
	line_s.x_args = 0;
	p_line_s_init(&line_s, line);
	return (true);
}
