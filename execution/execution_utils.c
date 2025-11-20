/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:27:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/20 14:33:45 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_input_redir(t_data *d, t_pipes *pipes)
{
	int	fd;

	if (d->heredoc)
	{
		dup2(pipes->heredoc[0], STDIN_FILENO);
		close(pipes->heredoc[0]);
		return (0);
	}
	if (d->red_in && d->red_in[0])
	{
		fd = open(d->red_in[0], O_RDONLY);
		if (fd == -1)
		{
			perror(d->red_in[0]);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		return (close(fd), 0);
	}
	if (pipes->old_pfd > 0)
	{
		dup2(pipes->old_pfd, STDIN_FILENO);
		return (close(pipes->old_pfd), 0);
	}
	return (0);
}

int	handle_output_redir(t_data *d, t_pipes *pipes, t_base *base)
{
	int	fd;
	int	flags;

	if (d->red_out && d->red_out[0])
	{
		flags = O_WRONLY | O_CREAT;
		if (d->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(d->red_out[0], flags, 0644);
		if (fd == -1)
		{
			perror(d->red_out[0]);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		return (close(fd), 0);
	}
	if (base->index < base->pipes_num)
	{
		dup2(pipes->pfd[1], STDOUT_FILENO);
		return (close(pipes->pfd[1]), 0);
	}
	return (0);
}

void	close_pipe_fds(t_pipes *pipes)
{
	if (pipes->pfd[0] > 0)
		close(pipes->pfd[0]);
	if (pipes->pfd[1] > 0)
		close(pipes->pfd[1]);
	if (pipes->old_pfd > 0)
		close(pipes->old_pfd);
	if (pipes->heredoc[0] > 0)
		close(pipes->heredoc[0]);
}
