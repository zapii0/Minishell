/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:50:46 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:23 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*s2;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	str_len = ft_strlen(s + start);
	if (str_len < len)
		len = str_len;
	s2 = (char *)malloc(len + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, len + 1);
	return (s2);
}
