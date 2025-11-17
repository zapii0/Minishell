/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:59 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:57 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int z)
{
	int	i;

	i = 0;
	if (z == 0)
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (unsigned char)z)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
