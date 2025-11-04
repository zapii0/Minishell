/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:10 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/04 17:38:28 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


void	red_parser(t_lex *lex, t_base *base)
{
	int	current_data;
	t_lex	*start;

	current_data = 0;
	search_heredoc(lex, base); // do zrobiernia 
	while (lex && current_data < base->d_counter)
	{
		start = lex;
		while (lex && lex->content && (ft_strcmp("|", lex->content)))
			lex = lex->next;
		if (!allocate_red_arrays(start, &base->data[current_data]))
			return ;
		fill_redirections(start, &base->data[current_data]);
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		current_data++;
	}
	clean_redirects(lex); // do zrobienia
}

void	search_heredoc(t_lex *lex, t_base *base)
{
	
}

void	clean_redirects(t_lex *lex)
{
	
}

void	fill_redirections(t_lex *lex, t_data *data)
{
	int index_in;
	int	index_out;

	index_in = 0;
	index_out = 0;
	while (lex && lex->content && ft_strcmp("|", lex->content))
	{
		if (is_in_red(lex->content))
		{
			lex = lex->next;
			data->red_in[index_in] = ft_strdup(lex->content);
			index_in++;
		}
		else if (is_out_red(lex->content))
		{
			lex = lex->next;
			data->red_out[index_out] = ft_strdup(lex->content);
			index_out++;
		}
		else 
			lex = lex->next;
	}
}

int	allocate_red_arrays(t_lex *lex, t_data *data)
{
	int		in;
	int		out;
	t_lex	*temp;

	in = 0;
	out = 0;
	temp = lex;
	while (temp && temp->content && ft_strcmp("|", temp->content))
	{
		if (is_in_red(temp->content))
			in++;
		if (is_out_red(temp->content))
			out++;
		temp = temp->next;
	}
	data->red_in = calloc(in + 1, sizeof(char *));
	data->red_out = calloc(out + 1, sizeof(char *));
	if (!data->red_in || !data->red_out)
		return (0);
	return (1);
}

