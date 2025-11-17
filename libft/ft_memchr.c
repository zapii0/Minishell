/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:27:31 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/16 14:24:33 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*conv;

	i = 0;
	conv = (unsigned char *)ptr;
	while (i < num)
	{
		if (conv[i] == (unsigned char)value)
			return (&conv[i]);
		i++;
	}
	return (NULL);
}
