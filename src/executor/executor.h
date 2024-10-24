/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:31:47 by amylle            #+#    #+#             */
/*   Updated: 2024/10/03 17:00:58 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_tools	t_tools;
typedef struct s_start	t_pars_start;
typedef struct s_args	t_args;

void	execute(t_args *args, t_tools *tools);
int		ft_error(char *errormessage, char *filename);
int		handle_pipes(t_args *args, int pipefd[2], int fd_in);
int		is_nofork_builtin(char **array);
int		isbuiltin(char *str);

#endif
