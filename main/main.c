/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/12 02:44:54 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

char	*input_reader(t_env *envp)
{
	char	*buf;
    t_lex	*lex;
	t_base	*base;

	buf = readline("Minihuj$ ");
	if (buf)
	{
		add_history(buf);
		lex = list_creator();
		base = tokenizer(buf, lex, envp);
	}
	return (buf);
}

int	main(void)
{
	char	*line;
	t_env	*envp;

	//rl_catch_signals = 0;
	//gather_signal();
	envp = initialize_list();
	while (TRUE)
	{
		line = input_reader(envp);
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

