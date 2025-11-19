/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:08 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 17:26:12 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_code(char *arg)
{
	int	exit_status;
	int	num_arg;

	num_arg = ft_atoi(arg);
	if (arg[0] == '-')
	{
		num_arg = num_arg * -1;
		exit_status = 256 - (num_arg % 256);
		return (exit_status);
	}
	else
		return (num_arg % 256);
}

int	is_arg_numeric(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (1);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	commit_exit(t_base *base, t_env *env)
{
	clear_all_allocated(base);
	clear_envs(env);
	clear_base(base);
	rl_clear_history();
}

int	ft_exit(t_base *base, t_env *env)
{
	int	exit_status;

	ft_putendl_fd("exit", 1);
	if (!base->data[base->currentIndex].args[1])
	{
		commit_exit(base, env);
		exit(0);
	}
	if (is_arg_numeric(base->data[base->currentIndex].args[1]))
	{
		commit_exit(base, env);
		exit (2);
	}
	if (base->data[base->currentIndex].args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	exit_status = exit_code(base->data[base->currentIndex].args[1]);
	commit_exit(base, env);
	exit(exit_status);
}
