/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:16:06 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/14 14:16:19 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

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
	char	limiter;
	int		i;
	int		j;

	limiter = '\0';
	i = 0;
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
	line = calloc(j + 1, 1);
	if (!line)
		return (NULL);
	line = quote_swapper(line, str);
	return (line);
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
		if (limiter == src[i])
		{
			limiter = '\0';
			i++;
		}
		else if (limiter == '\0' && (src[i] == '\'' || src[i] == '"'))
		{
			limiter = src[i];
			i++;
		}
		else
		{
			line[j] = src[i];
			i++;
			j++;
		}
	}
	return (line);
}
