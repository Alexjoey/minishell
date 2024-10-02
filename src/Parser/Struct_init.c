/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:10:14 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/02 23:12:00 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Init of args for the executer struct 
	arg_s is a shortcut so i dont need to fucking type the 
	whole struct all the time ;/
*/
void	p_struct_arg_init(t_pars_start *line_i, t_args *arg_i)
{
	t_args	*arg_s;

	if (line_i)
	{
		if (!line_i->args_start)
		{
			line_i->args_start = calloc(sizeof(t_args *), 1);
			return ;
		}
		arg_s = line_i->args_start;
		while (arg_s->nxt)
			arg_s = arg_s->nxt;
		arg_s->nxt = calloc(sizeof(t_args *), 1);

	}
	else
		arg_s = arg_i;
	arg_s = calloc(sizeof(t_args *), 1);
}

/*
	init phase of the executor struct
	Null all needed vars to then fill them with precious DATA :D
*/
void	p_line_s_init(t_pars_start *line_i, char *line)
{
	char	**split;
	int		i;
	//t_args	*tmp;

	p_struct_arg_init(line_i, NULL);
	split = ft_split(line, '|');
	i = 0;
	while (split[i])
	{
		if (!p_fil_inset_arg(line_i, split[i]))
		{
			/*ERROR MANAGEMENT if adding arg fails (malloc or unexpected arg)*/
		}
		i++;
	}
	i = 0;
	line_i->std_in = p_u_get_std_in(line_i);
	line_i->std_o = p_u_get_std_out(line_i);
}
