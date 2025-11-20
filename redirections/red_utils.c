/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:38:50 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/20 12:47:16 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

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
		while (lex && lex->content
			&& (lex->quoted || ft_strcmp("|", lex->content)))
		{
			if (!lex->quoted && !ft_strcmp(">>", lex->content))
				append = true;
			if (!lex->quoted && !ft_strcmp(">", lex->content))
				append = false;
			lex = lex->next;
		}
		base->data[data_counter].append = append;
		if (lex && lex->content && !lex->quoted
			&& !ft_strcmp("|", lex->content))
			lex = lex->next;
		data_counter++;
	}
}

void	fill_redirections(t_lex *lex, t_data *data)
{
	int	index_in;
	int	index_out;

	index_in = 0;
	index_out = 0;
	while (lex && lex->content && (lex->quoted || ft_strcmp("|", lex->content)))
	{
		if (!lex->quoted && is_in_red(lex->content))
		{
			lex = lex->next;
			if (lex && lex->content)
				data->red_in[index_in++] = ft_strdup(lex->content);
		}
		else if (!lex->quoted && is_out_red(lex->content))
		{
			lex = lex->next;
			if (lex && lex->content)
				data->red_out[index_out++] = ft_strdup(lex->content);
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
