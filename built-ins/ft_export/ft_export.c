/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:22:24 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/10 22:30:30 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	list_add_back(t_env **env, char *env_name, char *env_value)
//{
//	if (!env || !env_name || !env_value)
//		return ;
//}

int	ft_find_env(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strcmp(str, env->name) == 0)
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	ft_env_replace(t_env *env, char *name, char *new_value)
{
	while (env)
	{
		if (strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

void	ft_env_add_back(t_env **env, char *name, char *value)
{
	t_env	*new_elem;
	t_env	*tmp;

	if (!env || !name || !value)
		return ;
	new_elem = malloc(sizeof(t_env));
	if (!new_elem)
		return ;
	new_elem->name = strdup(name);
	new_elem->value = strdup(value);
	new_elem->next = NULL;
	if (!*env)
	{
		*env = new_elem;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem;
}

int	ft_export(t_env **env, char *new_envar, char *new_value)
{
	if (ft_find_env(new_envar, *env))
	{
		ft_env_replace(*env, new_envar, new_value);
		return (0);
	}
	else
	{
		ft_env_add_back(env, new_envar, new_value);
		return (0);
	}
	return (1);
}
