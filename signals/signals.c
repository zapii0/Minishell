/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:54 by apieniak          #+#    #+#             */
/*   Updated: 2025/07/09 21:01:39 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(int sig, siginfo_t *info, void *nothing)
{
	(void)nothing;
	(void)info;
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	gather_signal(void)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_sigaction = set_signals;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &sig_act, NULL);
	sigaction(SIGINT, &sig_act, NULL);
}