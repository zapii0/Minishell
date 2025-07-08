/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:05:55 by apieniak          #+#    #+#             */
/*   Updated: 2024/12/20 15:36:39 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t limit)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i] && s1[i] && s2[i]) && i < limit - 1)
		i++;
	if (i < limit)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
