/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollarsigns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 08:47:29 by amylle            #+#    #+#             */
/*   Updated: 2024/10/27 19:01:07 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*strdup_till_spaceordollar(char *str)
{
	int		i;
	char	*ret;
	int		len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '$'\
		&& str[len] != '\"' && str[len] != '\'')
		len++;
	ret = ft_calloc(sizeof(char), (len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (len > ++i)
		ret[i] = str[i];
	return (ret);
}

//sorry for this clusterfuck, fuck the norm
//this is given beginning of string, envp_i, and endofstr
//then joins beginning - expanded $ - endofstr
static char	*sub_dollar(char *str, char *eofstr, int envp_i, t_tools *tools)
{
	char	*ret;

	ret = NULL;
	if (envp_i == -2)
	{
		eofstr = ft_strjoinfree(ft_itoa(tools->errornum), eofstr);
		ret = ft_strjoin(str, eofstr);
		free (eofstr);
	}
	else if (envp_i >= 0)
	{
		ret = ft_strjoin(str, ft_strchr(tools->envp[envp_i], '=') + 1);
		ret = ft_strjoinfree(ret, eofstr);
	}
	else
		ret = ft_strjoin(str, eofstr);
	free (str);
	return (ret);
}

//fully works now, with ? and no spaces inbetween
char	*replace_dollarsigns(char *str, t_tools *tools)
{
	int		i;
	int		envp_i;
	char	*path_var;
	char	*endofstr;
	int		in_single_quote;

	i = -1;
	in_single_quote = 0;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '$' && in_single_quote == 0 && str[i + 1] && \
			str[i + 1] != '\"' && str[i + 1] != '\'')
		{
			path_var = strdup_till_spaceordollar(&str[i + 1]);
			envp_i = find_envp_index(tools->envp, path_var);
			endofstr = &str[i] + 1 + ft_strlen(path_var);
			free (path_var);
			str[i] = '\0';
			str = sub_dollar(str, endofstr, envp_i, tools);
			i = -1;
		}
	}
	return (str);
}
