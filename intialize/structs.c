/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:04:38 by apieniak          #+#    #+#             */
/*   Updated: 2025/08/19 19:50:50 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	till_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=');
			break;
		i++;
	}
	return (i);
}

void	intialize_structs(void)
{	
	extern char	**__environ;
	t_env	*env;
	int i;

	env = malloc(sizeof(t_env));
	i = 0;
	while (__environ[i] != NULL)
	{
		env->name = __environ[i];	//NAME + '='
		env->value = __environ[i]; // VALUE
		i++;
		env = env->next;
	}
	
}