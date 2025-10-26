NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

PARSING =  tokenizer.c utils.c utils2.c
ERRORS = error.c
MAIN = main.c

SRC = $(addprefix parsing/, $(PARSING)) \
		$(addprefix errors/, $(ERRORS)) \
		$(addprefix main/, $(MAIN))

OBJ_FILES   = $(SRC:.c=.o)

# Jeśli jesteś na Linuxie — odkomentuj poniższą linię:
# READLINE_FLAGS = -lreadline -lncurses
# Jeśli na macOS, wystarczy:
READLINE_FLAGS = -lreadline

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
