#ifndef PARSER_H
#define PARSER_H

# include "../minishell.h"
# include <stdbool.h>

typedef struct t_pars_start	t_pars_start;
typedef struct t_pipe		t_pipe;

/*
	str			= Raw split data from Readline
	extracted	= If TYPE calls for it example $VAR will 
					expand to the right value
	type		= Type of the arg 
					1 : Buildin, 
					2: $, 
					3: I(Pipe), 
					4: (-)arg: 
					5: TBD
	index		= Location in the Linked list
	init_s		= Redirect to the start struct
	nxt			= Next arg in the list
	prev		= Prev arg in the list if index is 0 then NULL
	pipe		= If type is a pipe this will redirect to the pipe info
*/
typedef struct s_args
{
	char				*str;
	char				*extracted;
	int					type;
	int					index;
	struct t_Pars_start	*init_s;
	struct s_Args		*nxt;
	struct s_Args		*prev;
	struct t_Pipe		*pipe;
}	t_args;

/*
	start_pipe	= Arg number where the Pipe Starts
	stop_pipe	= Arg number where the pipe stops
	index		= Place where the stack is
	start_arg	= Location where the pipe starts
	init_s		= Redirect to the start struct
	nxt			= Next pipe info if index is 0 then redirect the Start
	prev		= prev pipe info
*/
typedef struct s_pipe
{
	int					start_pipe;
	int					stop_pipe;
	int					index;
	struct s_Args		*start_arg;
	struct t_Pars_start	*init_s;
	struct t_Pipe		*nxt;
	struct t_Pipe		*prev;

}	t_pipe;


/*
	x_args 		= Ammount of args that are expected in the struct t_args
	pipe_info 	= Stuct containing all pipe info
	args_start	= Start of the linked list of s_Args
*/
typedef struct s_start
{
	int				x_args;
	struct t_Pipe	*pipe_info;
	struct s_Args	*args_start;

}	t_pars_start;


bool	parser_input(char *line);

void	p_line_s_init(t_pars_start *line_i, char *line);
bool	p_fil_inset_arg(t_pars_start *line_i, char *arg, int idx);

void	p_struct_arg_init(t_pars_start *line_i, t_args *arg_i);
void	p_struct_pipe_init(t_pars_start *line_i, t_pipe *pipe_i);
void	p_struct_redir_init(t_pars_start *line_i);


#endif