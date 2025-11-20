/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:27:58 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/20 16:24:09 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_input_files(char **red_in)
{
	int	fd;
	int	i;
	int	last_fd;

	i = 0;
	last_fd = -1;
	while (red_in[i])
	{
		fd = open(red_in[i], O_RDONLY);
		if (fd == -1)
			return (perror(red_in[i]), -1);
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		i++;
	}
	return (last_fd);
}

static int	handle_both_inputs(t_data *d, t_pipes *pipes)
{
	int	fd;

	if (d->b_heredoc)
	{
		dup2(pipes->heredoc[0], STDIN_FILENO);
		close(pipes->heredoc[0]);
		return (0);
	}
	fd = open_input_files(d->red_in);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_input_redir(t_data *d, t_pipes *pipes)
{
	int	fd;

	if (d->heredoc && d->red_in && d->red_in[0])
		return (handle_both_inputs(d, pipes));
	if (d->red_in && d->red_in[0])
	{
		fd = open_input_files(d->red_in);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (0);
	}
	if (d->heredoc)
	{
		dup2(pipes->heredoc[0], STDIN_FILENO);
		close(pipes->heredoc[0]);
		return (0);
	}
	if (pipes->old_pfd > 0)
		return (dup2(pipes->old_pfd, STDIN_FILENO), close(pipes->old_pfd), 0);
	return (0);
}

static int	open_output_files(char **red_out, bool append)
{
	int	fd;
	int	flags;
	int	i;
	int	last_fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	i = 0;
	last_fd = -1;
	while (red_out[i])
	{
		fd = open(red_out[i], flags, 0644);
		if (fd == -1)
			return (perror(red_out[i]), -1);
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		i++;
	}
	return (last_fd);
}

int	handle_output_redir(t_data *d, t_pipes *pipes, t_base *base)
{
	int	fd;

	if (d->red_out && d->red_out[0])
	{
		fd = open_output_files(d->red_out, d->append);
		if (fd == -1)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (0);
	}
	if (base->index < base->pipes_num)
		return (dup2(pipes->pfd[1], STDOUT_FILENO), close(pipes->pfd[1]), 0);
	return (0);
}
