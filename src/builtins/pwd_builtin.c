/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:35:41 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 06:01:03 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <complex.h>

int	pwd_builtin(char **args, t_tools *tools)
{
	int		i;
	char	*cwd;

	(void) tools;
	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (EXIT_FAILURE);
		printf("%s\n", cwd);
		free (cwd);
		return (EXIT_SUCCESS);
	}
}
