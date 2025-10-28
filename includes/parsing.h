#ifndef PARSING_H
# define PARSING_H

//		INCLUDES		//

# include <stdbool.h>

//		RETURN STRUCTS		//


typedef struct s_data // MNIEJSZA STURCTURA ZAWIERA FRAGMENT OD POCZATKU DO PIPA ALBO JESLI JEST TO DALEJ TO OD PIPA DO PIPA
{
	char **args; // TU BEDZIE CMD I JEJ ARGUMENTY
	char **red_out; // MIEJSCE PRZEKIEROWANIA OUTPUTU JESLI JEST
	char **red_in;	// MIEJSCE IMPUTU DO CMD JESLI JEST
	bool pipe_out; // PIPE OUT NIE WIEM CZY BEDZIE W TAKIEJ FORMIE MYSLE O TYM JESZCZE
	bool append;  // INFORMUJE CZY RED_OUT JEST APPENDEM
	bool redirection; // BOOL CZY JEST RED NIE WIEM CZY TU BEDZIE CHYBA NIE 
}	t_data;

typedef struct s_base   // DUZA STRUKTURA 
{ 
	t_data	*data; // ARRAY NA MNIEJSZE CZESCI COMMANDLINA 
	int	d_counter; // ILOSC MNIEJSZYCH CZESCI
	char	*binary; // PLIKI KTORE TRZEBA SPRAWDZIC CZY ISTNIEJA
	char	*heredoc; // HEREDOC JESLI JEST NULL TO NIE MA JESLI JEST W SRODKU JEST LIMITER
	bool	pipe; // BOOL CZY SA PIPY MOZLIWE ZE BEDZIE POMAGAC PRZY EGZE
// 		BEDZIE TU LISTA NODEOW Z ENVAMI I ICH WARTOSCIAMI 
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

int	ft_isspace(char c);
int	is_limiter(char c);
int	is_delimiter(char c);
int	node_filler(char *line, int i, t_lex *lex);
int	node_pipe(char *line, int i, t_lex *lex);
int	quote_edge_case(char *line, int i, t_lex *lex);
t_lex *node_creator(t_lex *lex);
int	special_chars(char *line, int i, t_lex *lex);
void	tokenizer(char *line, t_lex *lex, t_env *envp);
void	error_exec(int error_code, int mess_code);
void	qoute_error(char *line);
void	syntax_error(t_lex *lex);
void	error_red(t_lex *lex);
void	error_red2(t_lex *lex);
t_lex	*list_creator();
void	tokenizer(char *line, t_lex *lex, t_env *envp);
void	envp_filler(t_lex *lex, t_env *envp);
char	*envp_value_checker(char *line, t_env *envp);
char	*envp_value_swapper(char *line, int *i, t_env *envp);
void	swapper_clean(char *a, char *b, char *c);
char	*get_first(char *line, int i);
char	*get_second(char *line, int *i, t_env *envp);
char	*get_third(char *line, int i);
char	*find_env_value(char *name, t_env *envp);
#endif
