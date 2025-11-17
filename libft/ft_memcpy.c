/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:54:17 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/16 13:46:49 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	size_t			i;
	unsigned char	*cel;
	unsigned char	*skad;

	if (!destination && !source)
		return (NULL);
	cel = (unsigned char *)destination;
	skad = (unsigned char *)source;
	i = 0;
	while (i < num)
	{
		cel[i] = skad[i];
		i++;
	}
	return (destination);
}
