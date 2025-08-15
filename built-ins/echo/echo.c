/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:17 by apieniak          #+#    #+#             */
/*   Updated: 2025/08/15 19:31:53 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_check(int argc)
{
	if (argc <= 1)
	{
		printf("\n");
		return (1);
	}
	return (0);
}
void parameter_check(int argc, char **argv)
{
	int i;

	i = 2;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if ((i + 1) != argc)
			printf(" ");
		i++;
	}
}

int	main(int argc, char **argv)
{
	int i;

	if (input_check(argc))
		exit(0);
	if (strcmp(argv[1], "-n") == 0)
		parameter_check(argc, argv);
	else
	{
		i = 1;
		while (i < argc)
		{
			printf("%s ", argv[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}
