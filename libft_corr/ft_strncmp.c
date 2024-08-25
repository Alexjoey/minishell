/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:48:29 by tlaverge          #+#    #+#             */
/*   Updated: 2024/01/09 19:50:06 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	cmp_char(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
	{
		if (ft_isascii(c1) || ft_isascii(c2))
			return ((unsigned char)c1 - (unsigned char)c2);
		else
		{
			return ((unsigned char)c1 + (unsigned char)c2);
		}
	}
	return (0);
}

int
	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (!(s1) || !(s2))
		return (-1);
	while (s1[i] && s2[i] && i < n)
	{
		if (cmp_char(s1[i], s2[i]))
		{
			if (ft_isascii(s1[i]) && ft_isascii(s2[i]))
				return (s1[i] - s2[i]);
			else
				return (cmp_char (s1[i], s2[i]));
		}
		i++;
	}
	if (i < n)
		return (cmp_char(s1[i], s2[i]));
	return (0);
}
