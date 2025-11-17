/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:10 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/17 20:46:47 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

t_lex	*red_parser(t_lex *lex, t_base *base)
{
	int		current_data;
	t_lex	*start;
	t_lex	*head;

	head = lex;
	current_data = 0;
	search_heredoc(lex, base);
	search_append(lex, base);
	while (lex && current_data < base->d_counter)
	{
		start = lex;
		while (lex && lex->content && (ft_strcmp("|", lex->content)))
			lex = lex->next;
		if (!allocate_red_arrays(start, &base->data[current_data]))
			return (NULL);
		fill_redirections(start, &base->data[current_data]);
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		current_data++;
	}
	head = clean_redirects(head);
	args_filler(head, base);
	return (head);
}

static int	count_tok(t_lex *lex)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	tmp = lex;
	while (tmp && tmp->content && ft_strcmp("|", tmp->content))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	args_filler(t_lex *lex, t_base *base)
{
	int	seg;
	int	count;
	int	j;

	seg = 0;
	while (lex && seg < base->d_counter)
	{
		count = count_tok(lex);
		base->data[seg].args = ft_calloc(count + 1, sizeof(char *));
		if (!base->data[seg].args)
			return ;
		j = 0;
		while (j < count && lex && lex->content)
		{
			base->data[seg].args[j] = ft_strdup(lex->content);
			j++;
			lex = lex->next;
		}
		base->data[seg].args[j] = NULL;
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		seg++;
	}
}

char	*find_heredoc_limiter(t_lex *lex, bool *use_heredoc)
{
	char	*limiter;
	t_lex	*tmp;

	limiter = NULL;
	*use_heredoc = false;
	tmp = lex;
	while (tmp && tmp->content && ft_strcmp("|", tmp->content))
	{
		if (!ft_strcmp("<<", tmp->content))
		{
			if (limiter)
				free(limiter);
			if (tmp->next && tmp->next->content)
				limiter = ft_strdup(tmp->next->content);
			*use_heredoc = true;
		}
		if (!ft_strcmp("<", tmp->content))
			*use_heredoc = false;
		tmp = tmp->next;
	}
	return (limiter);
}

void	search_heredoc(t_lex *lex, t_base *base)
{
	int		data_count;
	char	*limiter;
	bool	use_heredoc;

	data_count = 0;
	while (lex && data_count < base->d_counter)
	{
		limiter = find_heredoc_limiter(lex, &use_heredoc);
		base->data[data_count].heredoc = limiter;
		base->data[data_count].b_heredoc = use_heredoc;
		while (lex && lex->content && ft_strcmp("|", lex->content))
			lex = lex->next;
		if (lex && lex->content && !ft_strcmp("|", lex->content))
			lex = lex->next;
		data_count++;
	}
}

void	fill_redirections(t_lex *lex, t_data *data)
{
	int	index_in;
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
