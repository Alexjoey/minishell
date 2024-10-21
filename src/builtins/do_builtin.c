/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:51:06 by amylle            #+#    #+#             */
/*   Updated: 2024/10/21 05:43:21 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	do_builtin(t_tools *tools, char **args)
{
	if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
		return (cd_builtin(args, tools));
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
		return (echo_builtin(args));
	if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		return (pwd_builtin(args, tools));
	if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
		return (env_builtin(args, tools));
	if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
		exit_builtin(args, tools);
	if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		return (unset_builtin(args, tools));
	if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
		return (export_builtin(args, tools));
	return (EXIT_FAILURE);
}
