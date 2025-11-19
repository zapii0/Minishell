/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 22:53:18 by apieniak         ###   ########.fr       */
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

t_base	*input_reader(t_env *envp, char **line, int last_exit)
{
	t_lex	*lex;
	t_base	*base;

	*line = readline("minishell$ ");
	if (*line)
	{
		add_history(*line);
		lex = list_creator();
		base = tokenizer(*line, lex, envp, last_exit);
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

	last_exit_status = 0;
	env = initialize_list();
	base = NULL;
	gather_signal();
	while (TRUE)
	{
		base = input_reader(env, &line, last_exit_status);
		if (!line)
			break ;
		else if (base)
		{
			gather_signal_exec();
			base->exit_status = last_exit_status;
			execution_main(base, &env);
			gather_signal();
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
