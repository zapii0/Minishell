/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:26:33 by apieniak          #+#    #+#             */
/*   Updated: 2025/07/08 14:07:46 by apieniak         ###   ########.fr       */
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
		free(buf);
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
