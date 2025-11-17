/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:30:18 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:36 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (n == 0)
	{
		if (search[0] == '\0')
			return ((char *)str);
		return (NULL);
	}
	if (search[0] == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == search[j] && search[j] != 0 && (i + j) < n)
			j++;
		if (search[j] == 0)
		{
			str += i;
			return ((char *)str);
		}
		i++;
	}
	return (NULL);
}
