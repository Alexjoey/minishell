/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:44:30 by tlaverge          #+#    #+#             */
/*   Updated: 2023/10/26 14:10:47 by tlaverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *str, ...);

int	ft_printchar(int c);

int	ft_printstr(char *str);

int	ft_print_ptr(unsigned long long ptr);

int	ft_printnbr(int nbr);

int	ft_print_unsigned(unsigned int nbr);

int	ft_print_hex(unsigned int nbr, const char c);

int	ft_printpercent(void);

#endif