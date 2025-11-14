NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

PARSING	= tokenizer.c utils.c utils2.c utils3.c
ERRORS		= error.c
MAIN		= main.c
INTIALIZE	= structs.c init.c
ENVP		= envp.c envp_utils.c
REDIRS		= red.c red_utils.c
CLEAN		= clean_structs.c

SRC = \
	$(addprefix parsing/, $(PARSING)) \
	$(addprefix errors/, $(ERRORS)) \
	$(addprefix main/, $(MAIN)) \
	$(addprefix intialize/, $(INTIALIZE)) \
	$(addprefix envp/, $(ENVP)) \
	$(addprefix redirections/, $(REDIRS)) \
	$(addprefix clean/, $(CLEAN))

OBJ_FILES   = $(SRC:.c=.o)


READLINE_FLAGS = -lreadline -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
