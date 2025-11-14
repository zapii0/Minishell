#ifndef PARSING_H
# define PARSING_H

//		INCLUDES		//

# include <stdbool.h>

//		RETURN STRUCTS		//


typedef struct s_data // MNIEJSZA STURCTURA ZAWIERA FRAGMENT OD POCZATKU DO PIPA ALBO JESLI JEST TO DALEJ TO OD PIPA DO PIPA
{
	char 	**args; // TU BEDZIE CMD I JEJ ARGUMENTY
	char 	**red_out; // MIEJSCE PRZEKIEROWANIA OUTPUTU JESLI JEST
	char 	**red_in;	// MIEJSCE IMPUTU DO CMD JESLI JEST
	char	*heredoc;
	bool	b_heredoc;
	bool 	append;  // INFORMUJE CZY RED_OUT JEST APPENDEM
}	t_data;

typedef struct s_base   // DUZA STRUKTURA 
{ 
	t_data	*data;
	int	d_counter;
}	t_base;


//		LEXER		//

typedef enum types
{
	PIPE,
	ARG,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND,
	QUOTE_ERROR,
	PIPE_ERROR,
	RED_ERROR,
} t_type;

typedef struct s_lex
{
	char			*content;
	enum types		type;
	struct s_lex		*next;
	struct s_lex		*previous;
	
}	t_lex;


//		FUNCTIONS		//

int		ft_isspace(char c);
int		is_limiter(char c);
int		is_delimiter(char c);
int		node_filler(char *line, int i, t_lex *lex);
int		node_pipe(char *line, int i, t_lex *lex);
int		quote_edge_case(char *line, int i, t_lex *lex);
t_lex	*node_creator(t_lex *lex);
int		special_chars(char *line, int i, t_lex *lex);
void	error_exec(int error_code, int mess_code);
void	qoute_error(char *line);
int		syntax_error(t_lex *lex);
int		error_red(t_lex *lex);
void	error_red2(t_lex *lex);
t_lex	*list_creator();
t_base	*tokenizer(char *line, t_lex *lex, t_env *envp);
int	envp_filler(t_lex *lex, t_env *envp);
char	*envp_value_checker(char *line, t_env *envp);
char	*envp_value_swapper(char *line, int *i, t_env *envp);
void	swapper_clean(char *a, char *b, char *c);
char	*get_first(char *line, int i);
char	*get_second(char *line, int *i, t_env *envp);
char	*get_third(char *line, int i);
char	*find_env_value(char *name, t_env *envp);
void	free_single_data(t_data *data);
void	free_base(t_base *base);
void	free_str_array(char **arr); 
t_data	*init_data(void);
void	init_single_data(t_data *data);
t_base	*init_base(int d_counter);
int	pipe_counter(t_lex *lex);
int	is_in_red(char *str);
int	is_out_red(char *str);
t_lex *clean_redirects(t_lex *lex);
t_lex	*clean_two_nodes(t_lex *current, t_lex **head);
t_lex	*red_parser(t_lex *lex, t_base *base);
char	*find_heredoc_limiter(t_lex *lex, bool *use_heredoc);
void	search_heredoc(t_lex *lex, t_base *base);
void	search_append(t_lex *lex, t_base *base);
void	fill_redirections(t_lex *lex, t_data *data);
int	allocate_red_arrays(t_lex *lex, t_data *data);
void	args_filler(t_lex *lex, t_base *base);
void	clean_all(t_base *base, t_lex *lex);
int		quote_remover(t_lex *lex);
char	*quote_remover_helper(char *str);
char	*quote_swapper(char *line, char *src);
#endif
