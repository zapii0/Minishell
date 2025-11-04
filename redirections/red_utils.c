/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:38:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/04 14:42:50 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

int	is_out_red(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(">", str) || !ft_strcmp(">>", str))
		return (1);
	return (0);
}

int	is_in_red(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp("<", str) || !ft_strcmp("<<", str))
		return (1);
	return (0);
}

