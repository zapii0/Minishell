/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/09/02 17:18:40 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*input_reader(void)
{
	char	*buf;

	buf = readline("minishell$ ");
	if (buf)
	{
		add_history(buf);
	}
	return (buf);
}

int	main(void)
{
	t_env	*env;
	char	*line;

	env = initialize_list();
	while (env)
    {
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
	//rl_catch_signals = 0;
	//gather_signal();
	//while (TRUE)
	//{
	//	line = input_reader();
	//	if (!line)
	//	{
	//		printf("exit (ctrl + d)");
	//		break ;
	//	}
	//}
	return (0);
}
