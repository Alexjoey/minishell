/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:47 by amylle            #+#    #+#             */
/*   Updated: 2024/10/03 15:28:28 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../minishell.h"

static int	unset_errors(char **args)
{
	int	i;

	i = -1;
	if (!args[1])
		return (ft_error("minishell: unset: not enough arguments", NULL));
	while (args[++i])
		if (ft_strchr(args[i], '=') || ft_strchr(args[i], '/'))
			return (ft_error("unset: not a valid parameter name: ", args[i]));
	return (EXIT_SUCCESS);
}

static int	unset_var(char *arg, t_tools *tools)
{
	int		j;
	int		envp_i;
	char	**tmp;
	int		i;

	envp_i = find_envp_index(tools->envp, arg);
	if (envp_i == -1)
		return (EXIT_SUCCESS);
	tmp = ft_calloc(sizeof(char *), ft_arrlen(tools->envp));
	if (!tmp)
		return (ft_error("unset: malloc failure ermm", NULL));
	i = 0;
	j = 0;
	while (tools->envp[i + j])
	{
		if (i == envp_i)
			j++;
		tmp[i] = tools->envp[i + j];
		i++;
	}
	free(tools->envp[envp_i]);
	free(tools->envp);
	tools->envp = tmp;
	return (EXIT_SUCCESS);
}

int	unset_builtin(char	**args, t_tools *tools)
{
	int	i;

	if (unset_errors(args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (args[++i])
		if (unset_var(args[i], tools) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
