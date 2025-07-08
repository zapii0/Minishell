/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:04:39 by apieniak          #+#    #+#             */
/*   Updated: 2025/02/27 19:36:52 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_udec(unsigned int num)
{
	int	count;

	count = 0;
	if (num >= 10)
		count += ft_udec(num / 10);
	count += ft_putchar_pf(num % 10 + '0');
	return (count);
}

void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_pf(num + '0');
		else
			ft_putchar_pf(num - 10 + 'a');
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	if (ptr == 0)
	{
		print_length += write(1, "(nil)", 5);
		return (print_length);
	}
	print_length += write(1, "0x", 2);
	if (ptr != 0)
	{
		ft_put_ptr(ptr);
		while (ptr != 0)
		{
			print_length++;
			ptr = ptr / 16;
		}
	}
	return (print_length);
}
