/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:09:23 by amylle            #+#    #+#             */
/*   Updated: 2024/10/22 14:09:37 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../minishell.h"

//returns 1 if it is builtin
int	isbuiltin(char *str)
{
	if (!ft_strncmp("cd", str, 3) || !ft_strncmp("echo", str, 5) \
		|| !ft_strncmp("pwd", str, 4) || !ft_strncmp("exit", str, 5) \
		|| !ft_strncmp("unset", str, 6) || !ft_strncmp("env", str, 4) \
		|| !ft_strncmp("export", str, 7))
		return (1);
	return (0);
}

int	is_nofork_builtin(char **array)
{
	if (!ft_strncmp(array[0], "exit", ft_strlen("exit")) || \
		!ft_strncmp(array[0], "cd", ft_strlen("cd")) || \
		!ft_strncmp(array[0], "export", ft_strlen("export")) || \
		!ft_strncmp(array[0], "unset", ft_strlen("unset")))
		return (true);
	return (false);
}

int	ft_error(char *errormessage, char *filename)
{
	ft_putstr_fd(errormessage, STDERR_FILENO);
	if (filename)
		ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

//returns -1 if it finds nothin, returns -2 if its supposed to be errornum
//otherwise return index of path in envp
int	find_envp_index(char **envp, char *path)
{
	int	i;
	int	eq_len;

	i = -1;
	if (path)
	{
		if (!ft_strncmp("?", path, 2))
			return (-2);
		while (envp[++i])
		{
			eq_len = 0;
			while (envp[i][eq_len] && envp[i][eq_len] != '=')
				eq_len++;
			if (!ft_strncmp(envp[i], path, eq_len) && path[eq_len] == '\0')
				return (i);
		}
	}
	return (-1);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
