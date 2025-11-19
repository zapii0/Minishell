/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:47:29 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 18:26:51 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_export_list(t_base *base, t_env *env)
{
	if (base->data[base->index].args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	while (env)
	{
		printf("declare -x %s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

int	ft_export_wrapper(t_env **env, char *arg, t_base *base)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!arg)
	{
		env_export_list(base, *env);
		return (0);
	}
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
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	start_builtin(char *cmd, t_base *base, t_env **env)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(base->data->args, *env));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(base));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(base, *env));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(base, *env));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export_wrapper(env, base->data->args[1], base));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(*env));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(env, base->data->args[1]));
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(base->data[base->index].args[0], 2);
	ft_putstr_fd("\n", 2);
	return (127);
}
