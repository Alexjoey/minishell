/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:10:14 by tlaverge          #+#    #+#             */
/*   Updated: 2024/09/06 04:06:43 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"

/*
	Init of args for the executer struct 
	arg_s is a shortcut so i dont need to fucking type the 
	whole struct all the time ;/
*/
static void	p_struct_arg_init(t_pars_start *line_i, t_args *arg_i)
{
	t_args	*arg_s;

	if (line_i)
		arg_s = line_i->args_start;
	else
		arg_s = arg_i;

	arg_s->extracted = NULL;
	arg_s->index = NULL;
	arg_s->init_s = line_i;
	arg_s->nxt = NULL;
	arg_s->pipe = NULL;
	arg_s->str = NULL;
	arg_s->type = NULL;

}

static void	p_struct_pipe_init(t_pars_start *line_i, t_pipe *pipe_i)
{
	t_pipe	*pp_s;

	pp_s = line_i->pipe_info;

	pp_s->index = NULL;
	pp_s->init_s = line_i;
	pp_s->nxt = NULL;
	pp_s->prev = NULL;
	pp_s->start_arg = NULL;
	pp_s->start_pipe = NULL;
	pp_s->stop_pipe = NULL;

}

static void	p_struct_redir_init(t_pars_start *line_i)
{

}

/*
	init phase of the executor struct
	Null all needed vars to then fill them with precious DATA :D
*/
void	p_line_s_init(t_pars_start *line_i, char *line)
{
	char	**split;
	int		i;
	int		j;

	p_struct_arg_init(line_i, NULL);
	p_struct_pipe_init(line_i, NULL);
	p_struct_redir_init(line_i);


	split = ft_split(line, ' ');

	i = 0;
	while (split[i])
	{
		if (!p_fil_inset_arg(line_i, split[i], i))
		{
			/*ERROR MANAGEMENT if adding arg fails (malloc or unexpected arg)*/
		}
		i++;
	}
}
