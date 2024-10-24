/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:09:34 by amylle            #+#    #+#             */
/*   Updated: 2024/10/25 00:58:05 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "executor.h"
#include <fcntl.h>

//need to add signal handling for ctrl-c, rest is all done basically
int	handle_heredoc(char *delimit, char *filename)
{
	char	*line;
	int		fd;

	signal(SIGINT, sigint_heredoc_handler);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	line = readline("> ");
	while (ft_strncmp(delimit, line, ft_strlen(delimit)) != 0)
	{
		if (!line)
			ft_error("warning: delimited by eof instead of desired:", delimit);
		if (g_signum != 0 || !line)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("> ");
	}
	signal(SIGINT, sigint_handler);
	free (line);
	close (fd);
	if (g_signum != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(char *std_in)
{
	int	fd;

	if (ft_strncmp("<<", std_in, 2) == 0)
		fd = open(std_in + 2, O_RDONLY);
	else
		fd = open(std_in + 1, O_RDONLY);
	if (fd < 0)
		return (ft_error("minishell: infile: No such file or directory: " \
				, std_in + 2));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe\n", NULL));
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_output_redirection(char *std_o)
{
	int	fd;

	if (ft_strncmp(">>", std_o, 2) == 0)
		fd = open(std_o + 2, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	else
		fd = open(std_o + 1, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
		return (ft_error("minishell: outfile: error opening file: " \
				, std_o + 2));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe\n", NULL));
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_pipes(t_args *args, int pipefd[2], int fd_in)
{
	if (args->prev)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close(fd_in);
	}
	if (args->nxt)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close(pipefd[1]);
	}
	while (args->std_in)
	{
		if (handle_input_redirection(args->std_in->content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		args->std_in = args->std_in->next;
	}
	while (args->std_o)
	{
		if (handle_output_redirection(args->std_o->content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		args->std_o = args->std_o->next;
	}
	return (EXIT_SUCCESS);
}
