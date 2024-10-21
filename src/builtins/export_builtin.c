/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 05:25:24 by amylle            #+#    #+#             */
/*   Updated: 2024/10/21 05:43:56 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static size_t	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	find_envp_index_export(char **envp, char *path)
{
	int	i;
	int	eq_len;

	i = -1;
	if (path)
	{
		while (envp[++i])
		{
			eq_len = 0;
			while (envp[i][eq_len] && envp[i][eq_len] != '=')
				eq_len++;
			if (!ft_strncmp(envp[i], path, eq_len + 1))
				return (i);
		}
	}
	return(-1);
}

int	export_builtin(char	**args, t_tools *tools)
{
	int		envp_i;
	char	**tmp;
	int		i;

	envp_i = find_envp_index_export(tools->envp, args[1]);
	if (envp_i >= 0)
	{
		free (tools->envp[envp_i]);
		tools->envp[envp_i] = ft_strdup(args[1]);
	}
	else
	{
		tmp = ft_calloc(sizeof(char *), ft_arrlen(tools->envp) + 2);
		if (!tmp)
			return (ft_error("export malloc fail", NULL));
		i = -1;
		while (tools->envp[++i])
			tmp[i] = tools->envp[i];
		tmp[i] = ft_strdup(args[1]);
		free (tools->envp);
		tools->envp = tmp;
	}
	return (EXIT_SUCCESS);
}
