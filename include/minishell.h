/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:04:48 by apieniak          #+#    #+#             */
/*   Updated: 2025/11/19 17:24:25 by apieniak         ###   ########.fr       */
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
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>

//extern char **__environ;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipes
{
	int	pfd[2];
	int	old_pfd;
	int	heredoc[2];
}	t_pipes;

typedef struct s_data
{
	char	**args; // cmd i args
	char	**red_out; // miejsce do przekierowania output
	char	**red_in; // miejsce input do cmd jesli jest
	char	*heredoc; // heredoc, jezeloi NULL to nie ma dlimitera
	bool	append; // INFORMUJE CZY RED_OUT JEST APPENDEM
	bool	b_heredoc;
}	t_data;

typedef struct s_base
{
	t_data	*data; // Array na mniejsze czesci cmdline
	int		d_counter; // Ilosc mniejszych czesci
	int		exit_status; // exit status programu
	int		pipes_num; // number of pipes in input
	int		currentIndex; // execution index
	char	**evp; // Lista wszystkich env
}	t_base;

//==============================================================
//Intialize t_env structure and paste there all envs | structs.c
t_env	*initialize_list(void);

int		till_equal_sign(char *str);

t_env	*list_arguments(t_env *current, char *env, int eq);

//==============================================================

//builtins

//PRINT WORKING DIRECTORY
int		ft_pwd(t_env *env);

//==============================================================

//PRINT ALL AVAILABLE ENVIROMENTALS
int		ft_env(t_base *base, t_env *env);

//==============================================================

//FIND CORRECT ENV IN LINKED LIST
int		ft_find_env(char *str, t_env *env);

//SYS PROGRAM OR BUILTIN?
int		is_builtin(char *cmd);

int		start_builtin(char *cmd, t_base *base, t_env **env);

void	ft_env_replace(t_env *env, char *name, char *new_value);

void	ft_env_add_back(t_env **env, char *name, char *value);

int		ft_export(t_env **env, char *new_envar, char *new_value);

int		ft_exit(t_base *base, t_env *env);

void	free_string_array(char **arr);

void	clear_data_element(t_data *data);

void	clear_all_allocated(t_base *base);

int		ft_echo(t_base *base);

int		ft_cd(char **args, t_env *env);

char	*save_env_value(char *str, t_env *env);

void	new_old_path(t_env *env);

int		change_dir(t_env *env, int has_args);

void	update_pwd(t_env *env);

void	ft_free_env_node(t_env *node);

void	ft_remove_env(t_env **env, char *env_name);

int		ft_unset(t_env **env, char *env_name);

char	*path_env_valider(t_env *env, char *cmd);

//==============================================================

//redirects/cline_delim.c

void	heredoc_limiter(t_base *base, t_pipes *pipes);

//==============================================================

//utils/utils.c

//returns enviromental linked-list size
int		env_list_size(t_env *env);

//freeing envs
void	clear_envs(t_env *env);

//freeing base struct
void	clear_base(t_base *base);

//freeing cmds in args
void	clear_cmds(t_base *base);

//==============================================================

//utils

int		ft_strcmp(const char *s1, const char *s2);

//==============================================================

//execution/list_to_array.c

//joins first string with seocnd one, then frees 2nd string
char	*ft_join_free(char *fr_str, char *join_str);

//converts envs in linked list to 2D array
char	**list_to_arr(t_env *env);

void	print_env_arr(t_base *base);

//==============================================================

//execution/execution_addons.c

int		child_builtins(char *builtin);

void	exec_commands(t_base *base, t_env *env, pid_t *pid, t_pipes *pipes);

void	ft_print_error(char *cmd, char *path, char *mess, int exit_status);

void	exec_vp_paths(char **args, char **envp, t_env *env, char *cmd);

void	redirects(t_base *base, t_pipes *pipes);

int		handle_input_redir(t_data *d, t_pipes *pipes);

int		handle_output_redir(t_data *d, t_pipes *pipes, t_base *base);

void	close_pipe_fds(t_pipes *pipes);

//==============================================================

//execution/execution_main.c

//main function of execution
void	execution_main(t_base *base, t_env **env);

//==============================================================

//execution/path_finder.c

//joins two paths into single one
char	*path_joiner(const char *path1, const char *path2);

//checks if the given path is valid
char	*check_valid_path(const char *dir_name, const char *file_name);

//==============================================================

//_____________________________________________________________

// The function where sigaction is structed, and started | signals.c
void	gather_signal(void);
// The function which handles signals | signals.c
void	set_signals(int sig, siginfo_t *info, void *nothing);

//_____________________________________________________________

// The function which read input from the terminal | main .c
t_base	*input_reader(t_env *envp, char **line);

#endif