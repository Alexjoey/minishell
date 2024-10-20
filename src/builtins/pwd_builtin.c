/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:35:41 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 06:01:03 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(char **args, t_tools *tools)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		i = find_envp_index(tools->envp, "PWD");
		ft_putendl_fd(tools->envp[i] + 4, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
}
