/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 03:31:47 by amylle            #+#    #+#             */
/*   Updated: 2024/09/03 03:32:44 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_tools	t_tools;

int		execute(char *line, t_tools *tools);

#endif
