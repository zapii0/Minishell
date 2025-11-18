/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cline_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:55:42 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/18 17:51:29 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_limiter(t_base *base, t_pipes *pipes)
{
	char	*str;

	if (pipe(pipes->heredoc) == -1)
	{
		perror("");
		return ;
	}
	while (TRUE)
	{
		str = readline("heredoc> ");
		if (str && ft_strcmp(base->data[base->currentIndex].heredoc, str) == 0)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, pipes->heredoc[1]);
		free(str);
	}
	close(pipes->heredoc[1]);
}
