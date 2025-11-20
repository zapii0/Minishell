/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:10 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/20 12:47:07 by mzapora          ###   ########.fr       */
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
		while (lex && lex->content && (lex->quoted
				|| ft_strcmp("|", lex->content)))
			lex = lex->next;
		if (!allocate_red_arrays(start, &base->data[current_data]))
			return (NULL);
		fill_redirections(start, &base->data[current_data]);
		if (lex && lex->content && !lex->quoted
			&& !ft_strcmp("|", lex->content))
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
	while (tmp && tmp->content && (tmp->quoted || ft_strcmp("|", tmp->content)))
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
		if (lex && lex->content && !lex->quoted
			&& !ft_strcmp("|", lex->content))
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
	while (tmp && tmp->content && (tmp->quoted || ft_strcmp("|", tmp->content)))
	{
		if (!tmp->quoted && !ft_strcmp("<<", tmp->content))
		{
			if (limiter)
				free(limiter);
			if (tmp->next && tmp->next->content)
				limiter = ft_strdup(tmp->next->content);
			*use_heredoc = true;
		}
		if (!tmp->quoted && !ft_strcmp("<", tmp->content))
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
		while (lex && lex->content && (lex->quoted
				|| ft_strcmp("|", lex->content)))
			lex = lex->next;
		if (lex && lex->content && !lex->quoted
			&& !ft_strcmp("|", lex->content))
			lex = lex->next;
		data_count++;
	}
}

