#ifndef PARSER_H
#define PARSER_H

# include "../minishell.h"

typedef struct t_Pars_start t_Pars_start;
typedef struct t_Pipe t_Pipe;

typedef struct s_Args
{
	char				*str; 			//Raw split data from Readline
	char				*extracted;		//If TYPE calls for it example $VAR will expand to the right value
	int					type;			//Type of the arg {1 : Buildin, 2: $, 3: I(Pipe), 4: TBD}
	int					index;			//Location in the Linked list
	struct t_Pars_start	*init_s;		//Redirect to the start struct
	struct s_Args		*nxt;			//Next arg in the list
	struct s_Args		*prev;			//Prev arg in the list if index is 0 then redirect the Start
	struct t_Pipe		*pipe;			//If type is a pipe this will redirect to the pipe info
}	t_Args;

typedef struct s_Pipe
{
	int					start_pipe;		//Arg number where the Pipe Starts
	int					stop_pipe;		//Arg number where the pipe stops
	int					index;			//Place where the stack is
	struct s_Args		*start_Arg;		//Location where the pipe starts
	struct t_Pars_start	*init_s;		//Redirect to the start struct
	struct t_Pipe		*nxt;			//Next pipe info if index is 0 then redirect the Start
	struct t_Pipe		*prev;			//prev pipe info

}	t_Pipe;



typedef struct s_start
{
	int				x_args;			//Ammount of args that are expected in the struct t_args
	struct t_Pipe	*pipe_Info;		//Stuct containing all pipe info
	struct s_Args	*args_start;	//Start of the linked list of s_Args

}	t_Pars_start;



#endif
