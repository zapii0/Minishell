/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/20 00:00:15 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

static int	process_line_tokens(char *line, t_lex *lex)
{
	int	i;
	int	res;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_limiter(line[i]))
		{
			res = node_filler(line, i, lex);
			if (res == -1)
				return (-1);
			i = res;
		}
	}
	return (0);
}

t_base	*tokenizer(char *line, t_lex *lex, t_env *envp, int last_exit)
{
	int		i;
	t_base	*base;
	t_lex	*lex_head;

	if (!envp)
		return (NULL);
	lex_head = lex;
	qoute_error(line);
	i = process_line_tokens(line, lex_head);
	if (i == -1)
		return (clean_all(NULL, lex_head), NULL);
	if (syntax_error(lex_head))
		return (clean_all(NULL, lex_head), NULL);
	base = init_base(pipe_counter(lex_head->next));
	if (!base)
		return (clean_all(NULL, lex_head), NULL);
	base->exit_status = last_exit;
	if (lex_head->next && envp_filler(lex_head->next, envp, base) == -1)
		return (clean_all(base, lex_head), NULL);
	if (lex_head->next)
		lex_head->next->previous = NULL;
	quote_remover(lex);
	lex = red_parser(lex_head->next, base);
	if (!lex)
		return (clean_all(base, lex_head), NULL);
	clean_all(NULL, lex_head);
	clean_all(NULL, lex);
	return (base);
}
