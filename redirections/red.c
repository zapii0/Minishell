/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:10 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/04 15:46:53 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


void	red_parser(t_lex *lex, t_base *base, int in, int out)
{
	int	current_data;
	t_lex	*start;

	current_data = 0;
	while (lex && current_data < base->d_counter)
	{
		in = 0;
		out = 0;
		start = lex;
		while (lex && lex->content && (ft_strcmp("|", lex->content))) 
		{
		if (lex->content && (is_in_red(lex->content)))
			in++;
		if (lex->content && (is_out_red(lex->content)))
			out++;
		lex = lex->next;
		}
		base->data[current_data].red_in = calloc(in + 1, sizeof(char *));
		base->data[current_data].red_out = calloc(out + 1, sizeof(char *));
		if (!base->data[current_data].red_in || !base->data[current_data].red_out)
			return ;
		fill_redirections(start, &base->data[current_data]);
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		current_data++;
	}
}
