/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/07/09 21:07:19 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*input_reader(void)
{
	char	*buf;

	buf = readline("Minihuj$ ");
	if (buf)
	{
		add_history(buf);
	}
	return (buf);
}

int	main(void)
{
	char	*line;

	rl_catch_signals = 0;
	gather_signal();
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
