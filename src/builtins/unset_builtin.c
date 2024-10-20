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

int	unset_builtin(char	**args, t_tools *tools)
{
	int	i;
	int	j;
	int	envp_i;
	char	**tmp;

	i = 0;
	envp_i = find_envp_index(tools->envp, args[1]);
	while (tools->envp[i])
		i++;
	tmp = ft_calloc(sizeof(char *), i);
	i = 0;
	j = 0;
	while(tools->envp[i + j])
	{
		if (i == envp_i)
		{
			free(tools->envp[i]);
			j++;
		}
		tmp[i] = tools->envp[i + j];
		i++;
	}
	free(tools->envp);
	tools->envp = tmp;
	if (ft_strncmp(args[1], "PATH", ft_strlen(args[1])) == 0)
	{
		free_array(tools->paths);
		tools->paths = get_paths(tools->envp);
	}
	return (EXIT_SUCCESS);
}
