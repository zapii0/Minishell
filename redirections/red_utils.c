/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:38:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/05 19:42:54 by mzapora          ###   ########.fr       */
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
	if (!ft_strcmp("<", str))
		return (1);
	return (0);
}

void	search_append(t_lex *lex, t_base *base)
{
	bool	append;
	int		data_counter;

	data_counter = 0;
	while (lex && data_counter < base->d_counter)
	{
		append = false;
		while (lex && lex->content && ft_strcmp("|", lex->content))
		{
			if (!ft_strcmp(">>", lex->content))
				append = true;
			if (!ft_strcmp(">", lex->content))
				append = false;
			lex = lex->next;
		}
		base->data[data_counter].append = append;
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		data_counter++;
	}
}
