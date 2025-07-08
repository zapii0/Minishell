/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:18:10 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:26 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ret;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && check_set((char)*s1, set))
		s1++;
	if (!*s1)
		return (ft_strdup(""));
	len = ft_strlen((char *)s1);
	while (len >= 0 && check_set(s1[len - 1], set))
		len--;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, (char *)s1, len + 1);
	return (ret);
}
