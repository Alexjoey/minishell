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
#include <unistd.h>

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
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signum = signal;
}

void	sigquit_handler(int signal)
{
	ft_putstr_fd("quit (core dumped) (not rlly im lying)", STDERR_FILENO);
	ft_putnbr_fd(signal, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_signum = signal;
}

void	sigint_fork_handler(int signal)
{
	write(STDERR_FILENO, "\n", 1);
	g_signum = signal;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
