/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitparenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:09:17 by amylle            #+#    #+#             */
/*   Updated: 2024/10/26 17:09:58 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "../minishell.h"

//searches for c in str, if it encounter a parenthesis itll skip till it finds
//the matching one, if it doesnt find one itll go to the end and return null
static char	*ft_strchrparenthesis(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (ft_strchr(&str[i + 1], str[i]))
				i += ft_strchr(&str[i + 1], str[i]) - &str[i] + 1;
			else
				i += ft_strlen(str);
		}
		else
			i++;
	}
	return (NULL);
}

static int	get_wordcount(char *line, char c)
{
	int	wordcount;
	int	i;
	int	skip;

	skip = 1;
	i = 0;
	wordcount = 0;
	while (line && line[i])
	{
		if (line[i] != c && skip == 1)
		{
			wordcount++;
			skip = 0;
		}
		else if (line[i] == c)
			skip = 1;
		if ((line[i] == '\'' || line[i] == '\"') && \
			ft_strchr(&line[i + 1], line[i]))
			i += ft_strchr(&line[i + 1], line[i]) - &line[i] + 1;
		else if (line[i] == '\'' || line[i] == '\"')
			i += ft_strlen(line);
		else
			i++;
	}
	return (wordcount);
}

static void	make_words(char **split, char *line, char c, int wordcount)
{
	char	*ptr;

	while (*line && *line == c)
		line++;
	while (wordcount--)
	{
		ptr = ft_strchrparenthesis(line, c);
		if (ptr)
		{
			*split = ft_substr(line, 0, ptr - line);
			while (*ptr && *ptr == c)
				ptr++;
			line = ptr;
		}
		else
			*split = ft_substr(line, 0, ft_strlen(line) + 1);
		split++;
	}
}

//split made to split around c but skipping parenthesis
//if parenthesis arent closed it will act like theres 
//a matching one at the end of the str
char	**ft_split_ignoring_parentheses(char *line, char c)
{
	char	**split;
	int		wordcount;

	split = NULL;
	if (!line)
		return (NULL);
	wordcount = get_wordcount(line, c);
	if (wordcount <= 0)
		return (NULL);
	split = ft_calloc(wordcount + 1, sizeof(char *));
	if (!split)
		return (NULL);
	make_words(split, line, c, wordcount);
	if (!split)
		return (NULL);
	return (split);
}
