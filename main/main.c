/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/07/08 14:21:03 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	input_reader(void)
{
	char	*buf;

	buf = readline("Minihuj$ ");
	if (buf)
	{
		add_history(buf);
		parser();
	}
}

int	main(void)
{
	char	*line;

	while (TRUE)
	{
		input_reader();
	}
}
