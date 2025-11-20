/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:16:06 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/20 12:30:00 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

static void	process_char(char *line, char src_char, char *limiter, int *j);
static int	count_unquoted_len(char *str, int i);

int	quote_remover(t_lex *lex)
{
	char	*old;

	while (lex)
	{
		if (lex->content)
		{
			old = lex->content;
			lex->content = quote_remover_helper(lex->content);
			free(old);
			if (!lex->content)
				return (1);
		}
		lex = lex->next;
	}
	return (0);
}

char	*quote_remover_helper(char *str)
{
	char	*line;
	int		len;

	len = count_unquoted_len(str, 0);
	line = calloc(len + 1, 1);
	if (!line)
		return (NULL);
	line = quote_swapper(line, str);
	return (line);
}

static int	count_unquoted_len(char *str, int i)
{
	char	limiter;
	int		j;

	limiter = '\0';
	j = 0;
	while (str[i])
	{
		if (str[i] == limiter)
		{
			limiter = '\0';
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '"') && limiter == '\0')
		{
			limiter = str[i];
			i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	*quote_swapper(char *line, char *src)
{
	char	limiter;
	int		i;
	int		j;

	limiter = '\0';
	i = 0;
	j = 0;
	while (src[i])
	{
		process_char(line, src[i], &limiter, &j);
		i++;
	}
	return (line);
}

static void	process_char(char *line, char src_char, char *limiter, int *j)
{
	if (*limiter == src_char)
		*limiter = '\0';
	else if (*limiter == '\0' && (src_char == '\'' || src_char == '"'))
		*limiter = src_char;
	else
	{
		line[*j] = src_char;
		(*j)++;
	}
}
