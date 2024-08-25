/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:22:33 by tlaverge          #+#    #+#             */
/*   Updated: 2023/10/23 17:23:55 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "ft_printf.h"

int	ft_formats(va_list va, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(va, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(va, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(va, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(va, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(va, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(va, unsigned int), format);
	else if (format == '%')
		print_length += ft_printpercent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	va_list	va;
	int		print_length;
	int		i;

	i = 0;
	print_length = 0;
	va_start(va, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formats(va, str[i + 1]);
			i++;
		}
		else
			print_length += ft_printchar(str[i]);
		i++;
	}
	va_end(va);
	return (print_length);
}
