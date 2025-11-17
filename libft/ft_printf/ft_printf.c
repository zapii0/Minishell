/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:00:29 by apieniak          #+#    #+#             */
/*   Updated: 2025/02/27 19:36:52 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_par(char c, va_list arg)
{
	int	counter;

	counter = 0;
	if (c == 'd')
		counter += ft_putnbr_pf(va_arg(arg, int));
	else if (c == 'i')
		counter += ft_putnbr_pf(va_arg(arg, int));
	else if (c == 'u')
		counter += ft_udec(va_arg(arg, unsigned int));
	else if (c == 'x')
		counter += ft_hex(va_arg(arg, unsigned int));
	else if (c == 'X')
		counter += ft_hex_up(va_arg(arg, unsigned int));
	else if (c == 'p')
		counter += ft_print_ptr(va_arg(arg, unsigned long long));
	else if (c == 's')
		counter += ft_putstr_pf(va_arg(arg, char *));
	else if (c == 'c')
		counter += ft_putchar_pf(va_arg(arg, int));
	else if (c == '%')
		counter += ft_putchar_pf('%');
	return (counter);
}

int	ft_printf(const char *string, ...)
{
	int		return_number;
	va_list	args;

	return_number = 0;
	va_start(args, string);
	while (*string)
	{
		if (*string == '%')
			return_number += format_par(*++string, args);
		else
			return_number += ft_putchar_pf(*string);
		string++;
	}
	va_end(args);
	return (return_number);
}
