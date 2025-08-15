/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:04:48 by apieniak          #+#    #+#             */
/*   Updated: 2025/08/15 19:56:29 by apieniak         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>

extern char **__environ;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_pipes
{
	int pfd[2];
	int old_pfd[2];
} t_pipes;

typedef struct s_data
{
	
} t_data;

// The function where sigaction is structed, and started
void	gather_signal(void);
// The function which handles signals
void	set_signals(int sig, siginfo_t *info, void *nothing);
// The function which read input from the terminal
char	*input_reader(void);

#endif