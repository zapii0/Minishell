/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:11:48 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:35:55 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_nums(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*string_num;
	unsigned int	length;
	unsigned int	number;

	length = ft_count_nums(n);
	string_num = (char *)malloc((length + 1) * sizeof(char));
	if (string_num == NULL)
		return (NULL);
	ft_bzero(string_num, length + 1);
	if (n < 0)
		number = (unsigned int)-n;
	else
		number = (unsigned int)n;
	if (number == 0)
		string_num [0] = '0';
	while (number != 0)
	{
		string_num[length - 1] = (number % 10) + '0';
		number /= 10;
		length--;
	}
	if (n < 0)
		string_num[0] = '-';
	return (string_num);
}
