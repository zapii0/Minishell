/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:22:00 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/17 20:39:52 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_wait(pid_t *pid, int pipes)
{
	int	i;
	int	status;
	int	last_code;

	i = 0;
	last_code = 0;
	while (i <= pipes)
	{
		if (waitpid(pid[i], &status, 0) != -1)
		{
			if (WIFEXITED(status))
				last_code = WEXITSTATUS(status);
			else
				last_code = 1;
		}
		i++;
	}
	return (last_code);
}

int	start_execution(t_base *base, t_env **env, pid_t *pid, t_pipes *pipes)
{
	if (base->pipes_num <= 1 && (base->data[base->currentIndex].args[0] && child_builtins(base->data[base->currentIndex].args[0])))
	{
		base->exit_status = start_builtin(base->data[base->currentIndex].args[0], base, env);
		printf("\n WESZŁO JAPIDIDI \n");
		return (0);
	}
	if (base->data[base->currentIndex].heredoc)
		heredoc_limiter(base, pipes);
	if (pipe(pipes->pfd) == -1)
	{
		perror("");
		return (1);
	}
	pid[base->currentIndex] = fork();
	if (pid[base->currentIndex] == -1)
	{
		perror("");
		close(pipes->pfd[0]);
		close(pipes->pfd[1]);
		if (pipes->old_pfd)
			close(pipes->old_pfd);
		return (1);
	}
	exec_commands(base, *env, pid, pipes);
	return (0);
}

void	execution_main(t_base *base, t_env **env)
{
	pid_t	*pid;
	t_pipes	pipes;
	int		i;

	base->pipes_num = base->d_counter - 1;
	ft_memset(&pipes, 0, sizeof(t_pipes));
	base->evp = list_to_arr(*env);
	pid = ft_calloc(base->pipes_num + 1, sizeof(pid_t));
	if (!pid)
		return ;
	i = 0;
	while (i <= base->pipes_num)
	{
		base->currentIndex = i;
		if (start_execution(base, env, pid, &pipes) != 0)
		{
			free(pid);
			clear_cmds(base);
			return ;
		}
		i++;
	}
	if (!(base->pipes_num < 1 && child_builtins(base->data[0].args[0])))
		base->exit_status = process_wait(pid, base->pipes_num);
	//clear_cmds(base);
	base->currentIndex = 0;
	free(pid);
	if (base->evp)
	{
		i = 0;
		while (base->evp[i])
		{
			free(base->evp[i]);
			i++;
		}
		free(base->evp);
		base->evp = NULL;
	}
}
