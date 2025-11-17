/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:08 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/16 10:08:43 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_all_allocated(t_base *base)
{
	int	i;

	i = 0;
	if (!base)
		return ;
	while (i < base->pipes_num)
	{
		if (base->data[i].args)
			clear_cmds(base);
		if (base->data[i].red_in)
			free(base->data[i].red_in);
		if (base->data[i].red_out)
			free(base->data[i].red_out);
	}
}

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
	if (arg[i] != '-' || arg[i] != '+')
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (0);
	}
	i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_base *base, t_env *env)
{
	int	exit_status;

	if (base->data[base->currentIndex].args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (!is_arg_numeric(base->data[base->currentIndex].args[1]))
		return (1);
	exit_status = exit_code(ft_atoi(base->data[base->currentIndex].args[1]));
	clear_all_allocated(base);
	clear_envs(env);
	clear_base(base);
	rl_clear_history();
	exit(exit_status);
}
