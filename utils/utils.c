/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:08:19 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/10 22:42:50 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_envs(t_env *env)
{
	t_env	*buff;

	if (!env)
		return ;
	while (env)
	{
		buff = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = buff;
	}
	env = 0;
}

void	clear_cmds(t_base *base)
{
	int	i;
	int	j;

	if (!base || !base->data)
		return ;
	j = 0;
	while (j < base->pipes_num + 1)
	{
		if (base->data[j].args)
		{
			i = 0;
			while (base->data[j].args[i])
			{
				free(base->data[j].args[i]);
				base->data[j].args[i] = NULL;
				i++;
			}
			free(base->data[j].args);
			base->data[j].args = NULL;
		}
		j++;
	}
}

void	clear_base(t_base *base)
{
	if (!base)
		return ;
	if (base->data)
	{
		free(base->data);
		base->data = NULL;
	}
	free(base);
}
