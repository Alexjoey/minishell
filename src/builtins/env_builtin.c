/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:09:06 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 06:13:21 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(char **args, t_tools *tools)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		return (EXIT_FAILURE);
	i = -1;
	while (tools->envp[++i])
		ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
