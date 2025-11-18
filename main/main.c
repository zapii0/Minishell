/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/18 18:16:06 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void	free_end_proccess(t_base *base, t_env *env)
{
	if (base)
		free_base(base);
	base = NULL;
	if (env)
		clear_envs(env);
	rl_clear_history();
}

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
		return (base);
	}
	return (NULL);
}

int	main(void)
{
	t_env	*env;
	t_base	*base;
	char	*line;

	env = initialize_list();
	base = NULL;
	rl_catch_signals = 0;
	gather_signal();
	while (TRUE)
	{
		base = input_reader(env, &line);
		if (!line)
			break ;
		else if (base)
		{
			execution_main(base, &env);
			free(line);
			free_base(base);
		}
		else
			free(line);
	}
	free_end_proccess(base, env);
	return (0);
}
