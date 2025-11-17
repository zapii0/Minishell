/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 06:38:17 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/17 20:51:54 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int	ft_isspace(char c)
{
	if ((c <= 13 && c >= 7) || c == ' ')
		return (1);
	return (0);
}

int	is_limiter(char c)
{
	if (!ft_isspace(c) || c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (ft_isspace(c) || c == '|' || c == '<' || c == '>' || c == '\n')
		return (1);
	return (0);
}

t_lex	*list_creator(void)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (!lex)
		return (NULL);
	lex->content = NULL;
	lex->next = NULL;
	return (lex);
}

t_lex	*node_creator(t_lex *lex)
{
	t_lex	*new;

	new = malloc(sizeof(t_lex));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->next = NULL;
	new->previous = lex;
	while (lex->next)
		lex = lex->next;
	lex->next = new;
	return (new);
}
