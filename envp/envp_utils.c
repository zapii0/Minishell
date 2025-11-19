/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:17:32 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/19 17:37:19 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void	swapper_clean(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}

char	*get_first(char *line, int i)
{
	char	*str;
	int		j;

	j = i;
	if (j == 0)
		return (ft_strdup(""));
	str = calloc(j + 1, 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_second(char *line, int *i, t_env *envp)
{
	int		j;
	int		k;
	char	*name;
	char	*value;

	j = 0;
	k = 0;
	(*i)++;
	while (ft_isalnum(line[(*i) + j]) || line[(*i) + j] == '_')
		j++;
	name = calloc(j + 1, 1);
	if (!name)
		return (NULL);
	while (k < j)
	{
		name[k] = line[k + (*i)];
		k++;
	}
	name[k] = '\0';
	*i += j;
	value = find_env_value(name, envp);
	free(name);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_third(char *line, int i)
{
	char	*str;
	int		j;

	j = 0;
	while (line[i + j])
		j++;
	if (j == 0)
		return (ft_strdup(""));
	str = calloc(j + 1, 1);
	if (!str)
		return (NULL);
	j = 0;
	while (line[i + j])
	{
		str[j] = line[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*find_env_value(char *name, t_env *envp)
{
	char	*value;

	while (envp)
	{
		if (!ft_strcmp(name, envp->name))
		{
			value = ft_strdup(envp->value);
			if (!value)
				return (NULL);
			return (value);
		}
		envp = envp->next;
	}
	return (ft_strdup(""));
}
