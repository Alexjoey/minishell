/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:17:10 by amylle            #+#    #+#             */
/*   Updated: 2024/07/24 16:20:53 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	if (argc != 1)
	{
		printf("This program does not accept any input\n");
		return (0);
	}
	while (1)
	{
	line = readline("minishell ~> ");
	add_history(line);
	execute(line, envp);
	free (line);
	}
}
