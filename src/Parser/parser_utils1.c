/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 03:47:59 by tlaverge          #+#    #+#             */
/*   Updated: 2024/10/03 17:39:50 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "../minishell.h"
/*List of functions that helps navigating the Struct*/
//TBA

int	p_u_get_size_total(t_args *arg_list)
{
	t_args	*temp;
	int		i;

	i = 0;
	if (!(arg_list))
		return (0);
	if (!(arg_list->prev))
		return (1);
	while (arg_list->prev)
		temp = arg_list->prev;
	while (temp->nxt)
	{
		temp = temp->nxt;
		i++;
	}
	return (i);
}

//give index of the < << >> >, itll free remove, and rejoin the split so the
//input after it wont just get removed and leak
void	free_and_join_stdinorout_split(char **split, int i)
{
	free (split[i]);
	free (split[i + 1]);
	while (split[i + 2])
	{
		split[i] = split[i + 2];
		i++;
	}
	split[i] = NULL;
	split[i + 1] = NULL;
}

char	*gen_heredoc_filename(void)
{
	static int	i = 0;
	char		*digit;
	char		*ret;

	ret = NULL;
	digit = ft_itoa(++i);
	if (!digit)
	{
		ft_error("malloc error in itoa", NULL);
		return (NULL);
	}
	ret = ft_strjoin("<<.tmpheredoc", digit);
	if (!ret)
	{
		ft_error("malloc error in strjoin", NULL);
		return (NULL);
	}
	free (digit);
	return (ret);
}

//made it readable and work properly for now
//need to be able to check for invalid identifiers
int	p_u_get_std_in(t_args *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg->split[i])
	{
		if (!ft_strncmp(arg->split[i], "<", 2) && arg->split[i + 1])
		{
			tmp = ft_strjoin(arg->split[i], arg->split[i + 1]);
			free_and_join_stdinorout_split(arg->split, i);
			ft_lstadd_back(&arg->std_in, ft_lstnew(tmp));
			i--;
		}
		else if (!ft_strncmp(arg->split[i], "<<", 3) && arg->split[i + 1])
		{
			tmp = gen_heredoc_filename();
			handle_heredoc(arg->split[i + 1], tmp + 2);
			free_and_join_stdinorout_split(arg->split, i);
			ft_lstadd_back(&arg->std_in, ft_lstnew(tmp));
			i--;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//need to be able to handle no space inbetween
int	p_u_get_std_out(t_args *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg->split[i])
	{
		if ((!ft_strncmp(arg->split[i], ">", ft_strlen(arg->split[i])) || \
			!ft_strncmp(arg->split[i], ">>", ft_strlen(arg->split[i])))
			&& arg->split[i + 1])
		{
			tmp = ft_strjoin(arg->split[i], arg->split[i + 1]);
			free_and_join_stdinorout_split(arg->split, i);
			ft_lstadd_back(&arg->std_o, ft_lstnew(tmp));
			i--;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
