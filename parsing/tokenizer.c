/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:26:30 by mzapora           #+#    #+#             */
/*   Updated: 2025/10/28 23:18:33 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"


void	tokenizer(char *line, t_lex *lex, t_env *envp)
{
	int	i;

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
    // t_lex *cur = lex->next;
    // while (cur)
    // {
    //     printf("content: %s\n", cur->content);
    //     cur = cur->next;
    // }
	return ;
}
