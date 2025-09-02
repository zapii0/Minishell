/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:04:38 by apieniak          #+#    #+#             */
/*   Updated: 2025/09/02 17:40:09 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	till_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

t_env	*initialize_list(void)
{
	extern char	**__environ;
	t_env		*current;
	t_env		*first;
	int			eq;
	int			i;

	i = 0;
	while (__environ[i] != NULL)
	{
		eq = till_equal_sign(__environ[i]);
		if (!first)
		{
			first = malloc(sizeof(t_env));
			first->name = strndup(__environ[i], eq);
			first->value = strdup(__environ[i] + eq + 1);
			first->next = NULL;
			current = first;
		}
		else
			current = list_arguments(current, __environ[i], eq);
		i++;
	}
	return (first);
}

t_env	*list_arguments(t_env *current, char *env, int eq)
{
	current->next = malloc(sizeof(t_env));
	if (!current->next)
		return (NULL);
	current = current->next;
	current->name = strndup(env, eq);
	current->value = strdup(env + eq + 1);
	current->next = NULL;
	return (current);
}
