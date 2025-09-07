/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:04:48 by apieniak          #+#    #+#             */
/*   Updated: 2025/09/06 20:14:49 by apieniak         ###   ########.fr       */
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
# include <stdbool.h>

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

typedef struct s_base
{
	t_data *data;
	int		d_counter;
	char	**evp;
	char	*binary;
	char	*heredoc;
	bool	pipe;
}	t_base;

typedef struct s_data
{
	char	**args;
	char	*flags;
	char	*red_out;
	char	*red_in;
	char	*pipe_out;
	bool	redirection;
}	t_data;

//Intialize t_env structure and paste there all envs | structs.c
t_env	*initialize_list(void);

int	till_equal_sign(char *str);

t_env	*list_arguments(t_env *current, char *env, int eq);

//_____________________________________________________________

// The function where sigaction is structed, and started | signals.c
void	gather_signal(void);
// The function which handles signals | signals.c
void	set_signals(int sig, siginfo_t *info, void *nothing);

//_____________________________________________________________

// The function which read input from the terminal | main .c
char	*input_reader(void);

#endif