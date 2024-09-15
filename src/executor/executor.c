/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:54:50 by amylle            #+#    #+#             */
/*   Updated: 2024/09/03 01:55:56 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	isbuiltin(char *str)
{
	if (!ft_strncmp("cd", str, 3) || !ft_strncmp("echo", str, 5) \
		|| !ft_strncmp("pwd", str, 4))
		return (1);
	return (0);
}

int	find_cmd(char *line, t_tools *tools)
{
	char	**splitline;
	char	*pathcmd;
	int		i;

	i = -1;
	pathcmd = NULL;
	splitline = ft_split(line, ' ');
	if (isbuiltin(splitline[0]))
		exit(do_builtin(tools, splitline));
	if (!access(splitline[0], F_OK))
		execve(splitline[0], splitline, tools->envp);
	while (tools->paths[++i])
	{
		pathcmd = ft_strjoin(tools->paths[i], splitline[0]);
		if (!access(pathcmd, F_OK))
			execve(pathcmd, splitline, tools->envp);
		free(pathcmd);
	}
	printf("minishell: command not found: %s\n", splitline[0]);
	free_array(splitline);
	exit (127);
}

int	execute(char *line, t_tools *tools)
{
	int		pid;
	int		status;
	int		ret;
	char	**splitline;

	if (ft_strncmp(line, "cd", 2) == 0)
	{
		splitline = ft_split(line, ' ');
		ret = cd_builtin(splitline, tools);
		free_array(splitline);
		return (ret);
	}
	pid = fork();
	if (pid == 0)
		find_cmd(line, tools);
	waitpid(pid, &status, 0);
	return (0);
}
