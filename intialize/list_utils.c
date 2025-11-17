/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:58:45 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/10 22:40:18 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	list_find_print(char *str, t_env *env)
{
	while (env != NULL)
	{
		if (strcmp(str, env->name) == 0)
		{
			printf("%s=%s\n", env->name, env->value);
			break ;
		}
		env = env->next;
	}
}
