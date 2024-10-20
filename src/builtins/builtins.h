/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:56:58 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 05:59:44 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_tools	t_tools;

int		do_builtin(t_tools *tools, char **line);

int		echo_builtin(char **args);
int		cd_builtin(char **args, t_tools *tools);
int		pwd_builtin(char **args, t_tools *tools);
int		env_builtin(char **args, t_tools *tools);
void	exit_builtin(char **args, t_tools *tools);
int		unset_builtin(char	**args, t_tools *tools);

#endif
