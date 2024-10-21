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
	return (-1);
}

char	**arraddback(char **array, char *str)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof (char *), ft_arrlen(array) + 2);
	if (!tmp)
	{
		ft_error("export malloc fail", NULL);
		return (NULL);
	}
	i = -1;
	while (array[++i])
		tmp[i] = array[i];
	tmp[i] = ft_strdup(str);
	return (tmp);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	valid_parameter(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (ft_error("not an identifier: ", str));
	if (!ft_strchr(str, '='))
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (ft_error("invalid export input: ", str));
	i = -1;
	while (str[++i] != '=')
		if (check_valid_identifier(str[i]))
			return (ft_error("not an identifier: ", str));
	return (EXIT_SUCCESS);
}

int	export_builtin(char	**args, t_tools *tools)
{
	int		envp_i;
	char	**tmp;
	int		i;

	if (!args[1])
		return (env_builtin(args, tools));
	i = 0;
	while (args[++i])
	{
		envp_i = find_envp_index_export(tools->envp, args[i]);
		if (valid_parameter(args[i]) == false)
			return (EXIT_FAILURE);
		else if (envp_i >= 0)
		{
			free (tools->envp[envp_i]);
			tools->envp[envp_i] = ft_strdup(args[i]);
		}
		else
		{
			tmp = arraddback(tools->envp, args[i]);
			free (tools->envp);
			tools->envp = tmp;
		}
	}
	return (EXIT_SUCCESS);
}
