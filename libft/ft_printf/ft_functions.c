/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:13:49 by apieniak          #+#    #+#             */
/*   Updated: 2025/02/27 19:36:52 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_pf(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		i += write(1, "(null)", 6);
		return (i);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_pf(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar_pf('-');
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr_pf(n / 10);
	}
	count += ft_putchar_pf(n % 10 + '0');
	return (count);
}

int	ft_hex(unsigned int n)
{
	int		count;
	char	*lowercase;

	count = 0;
	lowercase = "0123456789abcdef";
	if (n >= 16)
		count += ft_hex(n / 16);
	count += ft_putchar_pf(lowercase[n % 16]);
	return (count);
}

int	ft_hex_up(unsigned int n)
{
	int		count;
	char	*uppercase;

	count = 0;
	uppercase = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_hex_up(n / 16);
	count += ft_putchar_pf(uppercase[n % 16]);
	return (count);
}
