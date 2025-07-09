/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:04:48 by apieniak          #+#    #+#             */
/*   Updated: 2025/07/09 21:05:40 by apieniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define _POSIX_C_SOURCE 200809L

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// The function where sigaction is structed, and started
void	gather_signal(void);
// The function which handles signals
void	set_signals(int sig, siginfo_t *info, void *nothing);
// The function which read input from the terminal
char	*input_reader(void);

#endif