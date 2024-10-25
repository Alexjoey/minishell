/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:18:57 by amylle            #+#    #+#             */
/*   Updated: 2024/10/25 00:59:48 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/inc/libft.h"
# include "Parser/Parser.h"
# include "executor/executor.h"
# include "builtins/builtins.h"

typedef struct s_start	t_pars_start;
//general struct where you throw everything in yk
typedef struct s_tools
{
	char					**envp;
	struct s_start			*parser;
	int						errornum;
	bool					pars_good;
}	t_tools;

//todo:
//
//maybe add dollarsign and "" '' to heredoc, will see
//
//stdin/out errorchecking in parser
//pipe error checking in parser
//whitespace shit
//communicate to executor to not execute if theres parser error 
//
//will find the str starting with path inside of envp and return the index
//returns -1 if nothing is found
int		find_envp_index(char **envp, char *path);
void	free_array(char **array);
//resets and frees entire parser
void	reset_parser(t_pars_start *parser);
char	**get_paths(char **envp);

//gets called on ctrl-d, frees and exits
int		free_tools(t_tools *tools);

void	init_signals(void);
void	sigquit_handler(int sig);
void	sigint_fork_handler(int signal);
void	sigint_handler(int signal);
void	sigint_heredoc_handler(int signal);

extern int				g_signum;

#endif
