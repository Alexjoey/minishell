/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:07:24 by tlaverge          #+#    #+#             */
/*   Updated: 2023/10/25 15:00:33 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizeint(int s)
{
	int	i;

	i = 1;
	if (s == 0)
		return (1);
	if (s == -2147483648)
		s = 2147483647;
	else if (s < 0)
		s *= -1;
	while (s > 0)
	{
		s /= 10;
		i++;
	}
	return (i);
}

static int
	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

static void
	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

char
	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	int		count;
	size_t	length;

	if (n <= 0)
		count = ft_sizeint(n) + 1;
	else
		count = ft_sizeint(n);
	is_neg = (n < 0);
	str = ft_calloc(count, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (is_neg)
		str[length] = '-';
	ft_strrev(str);
	return (str);
}
