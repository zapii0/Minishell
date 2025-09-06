/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:55:42 by apieniak          #+#    #+#             */
/*   Updated: 2025/09/06 19:08:01 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_for_dlimit(char *str)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(str);
	while (str[i] != '\0' && str[i + 2] != '\0')
	{
		//if (len < i + 2)
			//return (0);
		if ((str[i] == '<' && str[i + 1] == '<') &&
			(str[i - 1] == 32 && str[i + 2] == 32))
			return (1);
		i++;
	}
	return (0);
}
