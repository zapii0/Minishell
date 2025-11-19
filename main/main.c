/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 16:57:09 by apieniak         ###   ########.fr       */
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
	int		last_exit_status;

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
			last_exit_status = base->exit_status;
			free_base(base);
			free(line);
		}
		else
			free(line);
	}
	free_end_proccess(base, env);
	return (last_exit_status);
}
