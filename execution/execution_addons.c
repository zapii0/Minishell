/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_addons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:43:44 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 17:38:34 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	child_builtins(char *builtin)
{
	if (!builtin)
		return (0);
	if (ft_strcmp(builtin, "unset") == 0 || ft_strcmp(builtin, "exit") == 0
		|| ft_strcmp(builtin, "export") == 0
		|| ft_strcmp(builtin, "cd") == 0)
	{
		return (1);
	}
	return (0);
}

void	ft_print_error(char *cmd, char *path, char *mess, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(mess, 2);
	if (path)
		free(path);
	exit(exit_status);
}

void	exec_vp_paths(char **args, char **envp, t_env *env, char *cmd)
{
	char		*path;
	struct stat	st;

	if (!args || !args[0])
		exit(0);
	path = path_env_valider(env, cmd);
	if (!path)
		ft_print_error(args[0], NULL, "Malloc Error", 1);
	if (access(path, F_OK) == -1 && access(path, X_OK) == -1)
		ft_print_error(args[0], path, ": No such file or directory", 127);
	stat(path, &st);
	if (execve(path, args, envp) == -1)
	{
		if (S_ISDIR(st.st_mode) && ft_strchr(path, '/'))
			ft_print_error(args[0], path, ": Is a directory", 126);
		if (access(path, X_OK) == -1 && ft_strchr(path, '/'))
			ft_print_error(args[0], path, ": Permission denied", 126);
		ft_print_error(args[0], path, ": command not found", 127);
	}
}

void	exec_commands(t_base *base, t_env *env, pid_t *pid, t_pipes *pipes)
{
	char	*cmd;

	if (pid[base->index] == 0)
	{
		redirects(base, pipes);
		if (!base->data[base->index].args
			|| !base->data[base->index].args[0])
			exit(0);
		if (is_builtin(base->data[base->index].args[0]))
			exit(start_builtin(base->data[base->index].args[0], base, &env));
		cmd = base->data[base->index].args[0];
		exec_vp_paths(base->data[base->index].args, base->evp, env, cmd);
		exit(127);
	}
	else
	{
		if (pipes->old_pfd)
			close(pipes->old_pfd);
		close(pipes->pfd[1]);
		pipes->old_pfd = pipes->pfd[0];
	}
}

void	redirects(t_base *base, t_pipes *pipes)
{
	t_data	*d;
	int		res;

	d = &base->data[base->index];
	res = handle_input_redir(d, pipes);
	if (res != 0)
	{
		close_pipe_fds(pipes);
		exit(1);
	}
	res = handle_output_redir(d, pipes, base);
	if (res != 0)
	{
		close_pipe_fds(pipes);
		exit(1);
	}
	close_pipe_fds(pipes);
}
