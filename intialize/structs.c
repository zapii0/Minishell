/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:04:38 by apieniak          #+#    #+#             */
/*   Updated: 2025/08/28 18:06:10 by apieniak         ###   ########.fr       */
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

t_env	*initialize_list(void)
{	
	extern char	**__environ;
	t_env	*current;
	t_env	*first;
	int	eq;
	int i;
	i = 0;
	while (__environ[i] != NULL)
	{
		eq = till_equal_sign(__environ[i]);
		if (!first)
		{
			first = malloc(sizeof(t_env));
			first->name = strndup(__environ[i], eq); //NAME
			first->value = strdup(__environ[i] + eq + 1); // VALUE
			first->next = NULL;
			current = first;
		}
		else

		i++;
	}
	return (first);
}


//t_env	*initialize_structs(void)
//{	
//	extern char	**__environ;
//	t_env	*env_list;
//	int eq;
//	int i;

//	env_list = malloc(sizeof(t_env));
//	if (!env_list)
//		return (NULL);
//	i = 0;
//	while (__environ[i] != NULL)
//	{
//		eq = till_equal_sign(__environ[i]);
//		env_list->name = strndup(__environ[i], eq);	//NAME
//		env_list->value = strdup(__environ[i] + eq + 1); // VALUE
//		i++;
//		env_list->next = malloc(sizeof(t_env));
//		env_list = env_list->next;
//	}
//	if (__environ[i] == NULL)
//	{
//		env_list = NULL;
//	}
	
//	return (env_list);
//}
