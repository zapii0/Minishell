/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:47:29 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/17 20:33:24 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export_wrapper(t_env **env, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!arg)
		return (1);
	equal_sign = strchr(arg, '=');
	if (!equal_sign)
		return (0);
	name = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (1);
	}
	ft_export(env, name, value);
	free(name);
	free(value);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	is_builtin(char *cmd)
{
	if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	start_builtin(char *cmd, t_base *base, t_env **env)
{
	if (strcmp(cmd, "cd") == 0)
		return (ft_cd(base->data->args, *env));
	else if (strcmp(cmd, "echo") == 0)
		return (ft_echo(base));
	else if (strcmp(cmd, "env") == 0)
		return (ft_env(base, *env));
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (ft_export_wrapper(env, base->data->args[1]));
	else if (strcmp(cmd, "pwd") == 0)
		return (ft_pwd(*env));
	else if (strcmp(cmd, "unset") == 0)
		return (ft_unset(env, base->data->args[1]));
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(base->data[base->currentIndex].args[0], 2);
	ft_putstr_fd("\n", 2);
	return (127);
}
