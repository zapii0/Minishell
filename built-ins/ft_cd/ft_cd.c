/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:22 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/10 22:32:25 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(t_env *env)
{
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
		return ;
	if (!ft_find_env("PWD", env))
		ft_env_add_back(&env, "PWD", cwd);
	else
		ft_env_replace(env, "PWD", cwd);
}

char	*save_env_value(char *str, t_env *env)
{
	while (env != NULL)
	{
		if (strcmp(str, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	new_old_path(t_env *env)
{
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
		return ;
	if (!ft_find_env("OLDPWD", env))
		ft_env_add_back(&env, "OLDPWD", cwd);
	else
		ft_env_replace(env, "OLDPWD", cwd);
}

int	change_dir(t_env *env, int has_args)
{
	int		is_changed;
	char	*new_path;

	if (has_args == 0)
	{
		new_path = save_env_value("HOME", env);
		if (!new_path)
			printf("minishell: cd: HOME not set");
		if (!new_path)
			return (1);
	}
	else if (has_args == 1)
	{
		new_path = save_env_value("OLDPWD", env);
		if (!new_path)
			printf("minishell: cd: OLDPWD not set");
		if (!new_path)
			return (1);
	}
	is_changed = chdir(new_path);
	if (is_changed == 0)
		new_old_path(env);
	if (is_changed == 0)
		update_pwd(env);
	return (is_changed);
}

int	ft_cd(char **args, t_env *env)
{
	int	cd_value;

	if (!args[1])
	{
		cd_value = change_dir(env, 0);
		return (cd_value);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		cd_value = change_dir(env, 1);
		return (cd_value);
	}
	else
	{
		cd_value = chdir(args[1]);
		if (cd_value == 0)
			update_pwd(env);
		else
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
	}
	return (cd_value);
}
