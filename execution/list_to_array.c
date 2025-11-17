/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:35:59 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/10 22:05:41 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_join_free(char *fr_str, char *join_str)
{
	if (!fr_str || !join_str)
		return (NULL);
	join_str = ft_strjoin(fr_str, join_str);
	free(fr_str);
	return (join_str);
}

char	**list_to_arr(t_env *env)
{
	char	**arr;
	char	*temp;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	if (!arr)
		return (NULL);
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		arr[i] = ft_join_free(temp, env->value);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	print_env_arr(t_base *base)
{
	int	i;

	i = 0;
	while (base->evp[i])
	{
		printf("FROM ARRAY:  %s\n", base->evp[i]);
		i++;
	}
}
