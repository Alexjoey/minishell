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
		return (EXIT_SUCCESS);
	ret = chdir(tools->envp[i] + ft_strlen(path) + 1);
	if (!ft_strncmp(path, "OLDPWD", ft_strlen("OLDPWD")))
		printf("%s\n", tools->envp[i] + ft_strlen(path) + 1);
	return (ret);
}

//need to change some shit here in case i unset shit
void	change_pwd(t_tools *tools, char *oldpwd)
{
	char	*tmp;
	char	*cwd;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	export_builtin((char *[]){"export", tmp, ""}, tools);
	free (tmp);
	free (oldpwd);
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	export_builtin((char *[]){"export", tmp, ""}, tools);
	free (cwd);
	free (tmp);
}

int	cd_builtin(char **array, t_tools *tools)
{
	int		ret;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!array[1])
		ret = specific_path(tools, "HOME");
	else if (ft_strncmp(array[1], "-", 2) == 0)
		ret = specific_path(tools, "OLDPWD");
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
	{
		free (oldpwd);
		return (EXIT_FAILURE);
	}
	change_pwd(tools, oldpwd);
	return (EXIT_SUCCESS);
}
