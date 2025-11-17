/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:17 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/11 19:48:39 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	input_check(int argc)
{
	if (argc <= 1)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

void	parameter_check(int argc, char **argv)
{
	int	i;

	i = 2;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if ((i + 1) != argc)
			printf(" ");
		i++;
	}
}

int	ft_echo(t_base *base)
{
	int	i;
	int	argc;

	argc = count_args(base->data->args);
	if (ft_strcmp(base->data->args[0], "echo") != 0)
	{
		printf("%s: command not found\n", base->data->args[1]);
		return (1);
	}
	if (input_check(argc))
		return (1);
	if (argc > 1 && ft_strcmp(base->data->args[1], "-n") == 0)
		parameter_check(argc, base->data->args);
	else
	{
		i = 1;
		while (i < argc)
		{
			printf("%s", base->data->args[i]);
			if (i + 1 < argc)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
