/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/04 15:44:04 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


t_base	tokenizer(char *line, t_lex *lex, t_env *envp)
{
	int		i;
	t_base	*base;

	if (!envp)
		return ;
	i = 0;
	qoute_error(line);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_limiter(line[i]))
			i = node_filler(line, i, lex);
	}
	syntax_error(lex);
	envp_filler(lex, envp);
	base = init_base(pipe_counter(lex));
	if (!base)
		return (free_base(base), NULL);
	red_parser(lex, base, 0 , 0);
	return (base);
}

    // t_lex *cur = lex->next;
    // while (cur)
    // {
    //     printf("content: %s\n", cur->content);
    //     cur = cur->next;
    // }
	