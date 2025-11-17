/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/16 09:10:27 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

t_base	*input_reader(t_env *envp, char **line)
{
	t_lex	*lex;
	t_base	*base;

	*line = readline("minishell$ ");
	if (*line)
	{
		add_history(*line);
		lex = list_creator();
		base = tokenizer(*line, lex, envp);
	}
	return (base);
}

int	main(void)
{
	t_env	*env;
	t_base	*base;
	char	*line;

	env = initialize_list();
	rl_catch_signals = 0;
	gather_signal();
	while (TRUE)
	{
		base = input_reader(env, &line);
		if (!line)
		{
			printf("exit (ctrl + d)");
			break ;
		}
		else if (base)
		{
			execution_main(base, &env);
			free(line);
		}
		else
			free(line);
	}
	clear_envs(env);
	rl_clear_history();
	return (0);
}
