/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:22:07 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/17 21:27:34 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->name);
	free(node->value);
	free(node);
}

void	ft_remove_env(t_env **env, char *env_name)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->name, env_name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			ft_free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_env **env, char *env_name)
{
	if (!env_name)
		return (1);
	if (!ft_find_env(env_name, *env))
	{
		printf("minishell: could not find a file with this name");
		return (1);
	}
	ft_remove_env(env, env_name);
	return (0);
}
