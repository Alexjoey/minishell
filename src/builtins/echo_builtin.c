/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:20:37 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 06:01:05 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_builtin(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
		n_flag = 1;
	i = 0;
	while (args[++i + n_flag])
	{
		ft_putstr_fd(args[i + n_flag], STDOUT_FILENO);
		if (args[i + n_flag + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
