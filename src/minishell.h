/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:18:57 by amylle            #+#    #+#             */
/*   Updated: 2024/09/16 00:45:02 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_corr/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "executor/executor.h"
# include "builtins/builtins.h"

typedef struct t_pars_start	t_pars_start;
//general struct where you throw everything in yk
typedef struct s_tools
{
	char					**paths;
	char					**envp;
	struct t_pars_start		*parser
}	t_tools;

//will find the str starting with path inside of envp and return the index
//returns -1 if nothing is found
int		find_envp_index(char **envp, char *path);

#endif
