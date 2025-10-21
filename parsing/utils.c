/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:48:54 by mzapora           #+#    #+#             */
/*   Updated: 2025/10/21 06:40:28 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"

static int	get_quote_span(char *line, int i)
{
	char	lim;
	int		count;
	int		j;
	int		flag;

	lim = 0;
	count = 0;
	j = 0;
	flag = 0;
	while (line[i + j] && !flag)
	{
		if ((line[i + j] == '\'' || line[i + j] == '"') && count == 0)
		{
			lim = line[i + j];
			count = 1;
			j++;
		}
		if (count == 1 && line[i + j] == lim)
		{
			count = 0;
			if (line[i + j + 1] == '\0' || is_delimiter(line[i + j + 1]))
				flag = 1;
		}
		j++;
	}
	return (j);
}

int	quote_edge_case(char *line, int i, t_lex *lex)
{
	int		j;
	int		k;

	j = get_quote_span(line, i);
	lex = node_creator(lex);
	if (!lex)
		return (-1);
	lex->content = calloc(j + 1, sizeof(char));
	if (!lex->content)
		return (-1);
	k = 0;
	while (k < j)
	{
		lex->content[k] = line[i + k];
		k++;
	}
	lex->content[j] = '\0';
	return (i + j);
}


int	node_filler(char *line, int i, t_lex *lex)
{
	int	j;
	
	j = 0;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (special_chars(line, i, lex));
	
	while (line[i + j] && !is_delimiter(line[i + j]))
	{
		if (line[i + j] == 39 || line[i + j] == '"')
			return (quote_edge_case(line, i, lex));
		j++;
	}
	lex = node_creator(lex);
	lex->content = calloc(j + 1, 1);
	if (!lex->content)
		return (-1);
	j = 0;
	while (line[i] && !is_delimiter(line[i]))
	{
		lex->content[j] = line[i];
		i++;
		j++;
	}
	return (i);
}

int	node_pipe(char *line, int i, t_lex *lex)
{
		lex = node_creator(lex);
		if (!lex)
			return (-1);
		lex->content = calloc(2, 1);
		lex->content[0] = line[i];
		return (i + 1);
}

int	special_chars(char *line, int i, t_lex *lex)
{
	if (line[i] == '|')
		return (node_pipe(line, i, lex));
	if (line[i] == '<' || line[i] == '>')
	{
		if (line[i + 1] && (line[i + 1] == '>' || line[i + 1] == '<'))
		{
			lex = node_creator(lex);
			if (!lex)
				return (-1);
			lex->content = calloc(3, 1);
			lex->content[0] = line[i];
			lex->content[1] = line[i + 1];
			return (i + 2);
		}
		lex = node_creator(lex);
		if (!lex)
			return (-1);
		lex->content = calloc(2, 1);
		lex->content[0] = line[i];
		return (i + 1);
	}
	return (i);
}
