/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:07:01 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:37:23 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*conv;

	conv = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		conv[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
