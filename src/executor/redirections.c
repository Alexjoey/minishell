/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:09:34 by amylle            #+#    #+#             */
/*   Updated: 2024/10/22 14:09:36 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "executor.h"
#include <fcntl.h>

int	handle_heredoc(char *d)
{
	char	*line;
	int		fd;

	fd = open(".tmpheredoc", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	line = readline("heredoc> ");
	while (ft_strncmp(d, line, ft_strlen(d)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("heredoc> ");
	}
	free (line);
	close (fd);
	fd = open(".tmpheredoc", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe", NULL));
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(char *std_in)
{
	int	fd;

	if (ft_strncmp("<<", std_in, 2) != 0)
	{
		fd = open(std_in + 2, O_RDONLY);
		if (fd < 0)
			return (ft_error("minishell: infile: No such file or directory: " \
					, std_in + 1));
		if (dup2(fd, STDIN_FILENO) < 0)
			return (ft_error("minishell: Failed to create a pipe\n", NULL));
		close (fd);
	}
	else if (handle_heredoc(std_in + 2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
		return (ft_error("minishell: outfile: No such file or directory: " \
				, std_o + 2));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_error("minishell: Failed to create a pipe\n", NULL));
	close (fd);
	return (EXIT_SUCCESS);
}

int	handle_pipes(t_args *args, t_tools *tools, int pipefd[2], int fd_in)
{
	if (!args->prev && tools->parser->std_in)
		if (handle_input_redirection(tools->parser->std_in) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
	if (!args->nxt && tools->parser->std_o)
		return (handle_output_redirection(tools->parser->std_o));
	return (EXIT_SUCCESS);
}
