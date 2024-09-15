/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:51:06 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 06:01:03 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	do_builtin(t_tools *tools, char **args)
{
	if (!ft_strncmp(args[0], "cd", 3))
		return (cd_builtin(args, tools));
	if (!ft_strncmp(args[0], "echo", 5))
		return (echo_builtin(args));
	if (!ft_strncmp(args[0], "pwd", 4))
		return (pwd_builtin(args, tools));
	if (!ft_strncmp(args[0], "env", 4))
		return (env_builtin(args, tools));
	return (EXIT_FAILURE);
}
