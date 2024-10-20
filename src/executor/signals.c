/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:36:11 by amylle            #+#    #+#             */
/*   Updated: 2024/10/15 13:36:36 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//line = NULL only happens if ctrl-d is pressed,
//which makes this function run, free and exit minshell
int	free_tools(t_tools *tools)
{
	free_array(tools->envp);
	free (tools);
	rl_clear_history();
	return (0);
}

void	sigint_handler(int signal)
{
	(void) signal;
	if (g_global.in_heredoc == true)
	{
		rl_done = 1;
		g_global.stophdoc = true;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	write(STDERR_FILENO, "\n", 1);
	if (g_global.in_fork == true)
		return ;
	if (g_global.in_fork == false)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
