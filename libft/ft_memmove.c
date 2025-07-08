/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:44:47 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:37:25 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	char	*desttrans;
	char	*srctrans;
	size_t	i;

	if (src == 0 && dest == 0)
		return (NULL);
	desttrans = (char *)dest;
	srctrans = (char *)src;
	if (desttrans > srctrans)
	{
		while (num-- > 0)
		{
			desttrans[num] = srctrans[num];
		}
	}
	else
	{
		i = 0;
		while (i < num)
		{
			desttrans[i] = srctrans[i];
			i++;
		}
	}
	return (dest);
}
