/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzapora <mzapora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:17:32 by mzapora           #+#    #+#             */
/*   Updated: 2025/11/20 17:10:47 by mzapora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

static char	*extract_var_name(char *line, int *i);

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

char	*get_second(char *line, int *i, t_env *envp, t_base *base)
{
	char	*name;
	char	*value;

	(*i)++;
	value = handle_exit_status_exit(line, i, base);
	if (value)
		return (value);
	name = extract_var_name(line, i);
	if (!name)
		return (NULL);
	value = find_env_value(name, envp);
	free(name);
	if (!value)
		return (NULL);
	return (value);
}

static char	*extract_var_name(char *line, int *i)
{
	int		j;
	int		k;
	char	*name;

	j = 0;
	k = 0;
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
	return (name);
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
