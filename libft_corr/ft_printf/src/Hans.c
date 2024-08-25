/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hans.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:20:01 by tlaverge          #+#    #+#             */
/*   Updated: 2023/11/22 13:31:29 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "ft_printf.h"

int	ft_printchar(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printpercent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

int	ft_printnbr(int nbr)
{
	int		len;
	char	*num;

	num = ft_itoa(nbr);
	len = ft_printstr(num);
	free(num);
	return (len);
}
