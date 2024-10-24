/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:36:11 by amylle            #+#    #+#             */
/*   Updated: 2024/10/25 01:00:13 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//line = NULL only happens if ctrl-d is pressed,
//which makes this function run, free and exit minshell

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

//barely know why but this makes the thing work man
int	event(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
