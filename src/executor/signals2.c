/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:57:05 by amylle            #+#    #+#             */
/*   Updated: 2024/10/25 00:59:49 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_tools(t_tools *tools)
{
	free_array(tools->envp);
	free (tools);
	rl_clear_history();
	return (0);
}

void	sigint_heredoc_handler(int signal)
{
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_signum = signal;
}
