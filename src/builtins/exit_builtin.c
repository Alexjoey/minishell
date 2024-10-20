/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:42:04 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 23:55:14 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/inc/libft.h"

void	free_everything(t_tools *tools)
{
	reset_parser(tools->parser);
	free_array(tools->envp);
	free (tools);
}

void	exit_builtin(char **args, t_tools *tools)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	if (args[1])
		i = ft_atoi(args[1]);
	else
		i = 0;
	free_everything(tools);
	exit(i);
}
