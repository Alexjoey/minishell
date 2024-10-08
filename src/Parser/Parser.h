/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:23:55 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 17:26:16 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include "../../libft/inc/libft.h"

typedef struct s_start	t_pars_start;
typedef struct s_args	t_args;
typedef struct s_tools	t_tools;

/*
	str			= Raw split data from Readline
	split		= Split of str
	index		= Location in the Linked list
	init_s		= Redirect to the start struct
	nxt			= Next arg in the list
	prev		= Prev arg in the list if index is 0 then NULL
	pipe		= If type is a pipe this will redirect to the pipe info
*/
typedef struct s_args
{
	char				*str;
	char				**split;
	int					index;
	struct s_start		*init_s;
	t_args				*nxt;
	t_args				*prev;
}	t_args;

/*
	x_args 		= Ammount of args that are expected in the struct t_args
	std_in		= String to STD IN or here doc shit
	std_o		= string to STD OUT or Append shit idfk
	pipe_info 	= Stuct containing all pipe info
	args_start	= Start of the linked list of s_Args splits on pipe
*/
typedef struct s_start
{
	int				x_args;
	char			*std_in;
	char			*std_o;
	t_args			*args_start;
}	t_pars_start;

t_pars_start	*parser_input(char *line, t_tools *tools);

void			p_line_s_init(t_pars_start *line_i, char *line, t_tools *tools);
bool			p_fil_inset_arg(t_pars_start *line_i, char *arg, t_tools *tool);

void			p_struct_arg_init(t_pars_start *line_i, t_args *arg_i);

int				p_u_get_size_total(t_args *arg_list);
char			*p_u_get_std_in(t_pars_start *parser);
char			*p_u_get_std_out(t_pars_start *parser);

#endif
