/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:36:43 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:51 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	char	*con;

	if (!s1 || !s2)
		return (NULL);
	con = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!con)
		return (NULL);
	j = 0;
	while (*s1)
	{
		con[j] = *s1;
		s1++;
		j++;
	}
	while (*s2)
	{
		con[j] = *s2;
		s2++;
		j++;
	}
	con[j] = '\0';
	return (con);
}
