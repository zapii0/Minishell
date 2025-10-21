/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/10/21 06:37:17 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"

char	*input_reader(void)
{
	char	*buf;
    t_lex	*lex;

	buf = readline("Minihuj$ ");
	if (buf)
	{
		add_history(buf);
        list_creator(lex);
        tokenizer(buf, lex);
	}
	return (buf);
}

int	main(void)
{
	char	*line;

	//rl_catch_signals = 0;
	//gather_signal();
	while (TRUE)
	{
		line = input_reader();
		if (!line)
		{
			printf("exit (ctrl + d)");
			break ;
		}
	}
	return (0);
}

// int main(void)
// {
//     char *line = "lolo >>";
//     t_lex *lex;

//     lex = malloc(sizeof(t_lex));
//     if (!lex)
//         return (1);
//     lex->content = NULL;
//     lex->next = NULL;

//     tokenizer(line, lex);

//     t_lex *cur = lex->next; // pomijamy dummy node
//     while (cur)
//     {
//         printf("content: %s\n", cur->content);
//         cur = cur->next;
//     }
//     return (0);
// }

