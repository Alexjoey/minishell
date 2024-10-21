/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:30:11 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 17:25:30 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*p_make_charp(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));

	if (str == NULL)
		return (NULL);

	str[0] = c;
	str[1] = '\0';

	return (str);
}

static void	p_perentisy_check(t_args *arg)
{
	int		i;
	char	*tmp;
	char	*c;
	bool	quote;

	tmp = NULL;
	quote = false;
	i = 0;
	while (arg->str[i])
	{
		c = p_make_charp(arg->str[i]);
		if (arg->str[i] == (char)39
				|| ((arg->str[i] == (char)34) && !(arg->str[i - 1] == (char) 92)))
		{
			tmp = ft_strjoinfree(tmp, "\n");
			if (quote)
				quote = false;
			else
				quote = true;
		}
		else if (arg->str[i] == (char)32 && !quote)
			tmp = ft_strjoinfree(tmp, "\n");
		else
			tmp = ft_strjoinfree(tmp, c);
		i++;
		free(c);
	}
	arg->split = ft_split(tmp, (char) 10);
	free(tmp);
}

static char	*strdup_till_spaceordollar(char *str)
{
	int		i;
	char	*ret;
	int		len;

	len = 0;
	while(str[len] && str[len] != ' ' && str[len] != '$')
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
static char	*substitute_dollarsign(char *str, char *endofstr, int envp_i, t_tools *tools)
{
	char	*ret;

	ret = NULL;
	if (envp_i == -2)
	{
		endofstr = ft_strjoinfree(ft_itoa(tools->errornum), endofstr);
		ret = ft_strjoin(str, endofstr);
		free (endofstr);
	}
	else if (envp_i >= 0)
	{
		ret = ft_strjoin(str, ft_strchr(tools->envp[envp_i], '=') + 1);
		ret = ft_strjoinfree(ret, endofstr);
	}
	else
		ret = ft_strjoin(str, endofstr);
	return (ret);
}

//fully works now, with ? and no spaces inbetween
static char	*replace_dollarsigns(char *str, t_tools *tools)
{
	int		i;
	int		envp_i;
	char	*path_var;
	char	*endofstr;
	char	*ret;

	i = -1;
	ret = NULL;
	while (str && str[++i])
	{
		if (str[i] == '$')
		{
			path_var = strdup_till_spaceordollar(&str[i + 1]);
			envp_i = find_envp_index(tools->envp, path_var);
			endofstr = &str[i] + 1 + ft_strlen(path_var);
			free (path_var);
			str[i] = '\0';
			ret = substitute_dollarsign(str, endofstr, envp_i, tools);
			free (str);
			str = ret;
			i = -1;
		}
	}
	return (ret);
}

static void	p_fil_type_arg(t_args *new, char *arg, t_tools *tools)
{
	int		idx;

	idx = 0;
	new->str = arg;
	if (ft_strchr(new->str, (char)34) || ft_strchr(new->str, (char)39))
		p_perentisy_check(new);
	else
		new->split = ft_split(arg, ' ');
	while (new->split[idx])
	{
		if (ft_strchr(new->split[idx], '$')
			&& !(ft_strchr(new->split[idx], (char) 39)))
		{
			new->split[idx] = replace_dollarsigns(new->split[idx], tools);
		}
		idx++;
	}
}

/*
	filles all the needed args
	WIP need to add Maloc shit all temp code for now
	Will add a 'new' link in the list in the last pos
*/
bool	p_fil_inset_arg(t_pars_start *line_i, char *arg, t_tools *tool)
{
	t_args			*curr;
	t_args			*new;
	int				idx;

	idx = p_u_get_size_total(line_i->args_start) + 1;
	new = ft_calloc(1, sizeof(t_args));
	if (!new)
		return (false);
	if (line_i->x_args <= idx)
		line_i->x_args = idx;
	if (line_i->args_start)
	{
		curr = line_i->args_start;
		while (curr->nxt)
			curr = curr->nxt;
		curr->nxt = new;
		new->prev = curr;

	}
	else
		line_i->args_start = new;
	new->init_s = line_i;
	new->index = idx;
	p_fil_type_arg(new, arg, tool);
	return (true);
}
