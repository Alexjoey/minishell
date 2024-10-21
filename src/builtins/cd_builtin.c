/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 01:23:05 by amylle            #+#    #+#             */
/*   Updated: 2024/09/15 05:56:59 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//
int	specific_path(t_tools *tools, char *path)
{
	int	i;
	int	ret;

	i = find_envp_index(tools->envp, path);
	if (i == -1)
	{
		write(STDERR_FILENO, path, ft_strlen(path) - 1);
		write(STDERR_FILENO, " not set\n", ft_strlen(" not set\n"));
		return (EXIT_FAILURE);
	}
	ret = chdir((tools->envp[i] + ft_strlen(path)));
	return (ret);
}

//need to change some shit here in case i unset shit
void	change_pwd(t_tools *tools)
{
	char	*cwd;
	char	*temp_pwd;
	int		i;

	i = find_envp_index(tools->envp, "PWD");
	temp_pwd = tools->envp[i];
	i = find_envp_index(tools->envp, "OLDPWD");
	free (tools->envp[i]);
	tools->envp[i] = ft_strjoin("OLDPWD=", (temp_pwd + ft_strlen("PWD=")));
	i = find_envp_index(tools->envp, "PWD");
	free (tools->envp[i]);
	cwd = getcwd(NULL, 0);
	tools->envp[i] = ft_strjoin("PWD=", cwd);
	free (cwd);
}

int	cd_builtin(char **array, t_tools *tools)
{
	int	ret;

	if (!array[1])
		ret = specific_path(tools, "HOME=");
	else if (ft_strncmp(array[1], "-", 2) == 0)
		ret = specific_path(tools, "OLDPWD=");
	else
	{
		ret = chdir(array[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(array[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_pwd(tools);
	return (EXIT_SUCCESS);
}
