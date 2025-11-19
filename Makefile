# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apieniak <apieniak@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 16:30:00 by apieniak          #+#    #+#              #
#    Updated: 2025/11/19 17:25:12 by apieniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = main built-ins built-ins/cd built-ins/exit built-ins/ft_echo built-ins/ft_env \
 built-ins/ft_export built-ins/ft_pwd built-ins/unset utils/utils.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	main/main.c \
	intialize/structs.c \
	intialize/init.c \
	execution/execution_main.c \
	built-ins/ft_env/ft_env.c \
	built-ins/ft_export/ft_export.c \
	built-ins/ft_pwd/ft_pwd.c \
	built-ins/ft_echo/ft_echo.c \
	built-ins/builtins.c \
	built-ins/ft_cd/ft_cd.c \
	built-ins/ft_exit/ft_exit.c \
	built-ins/ft_unset/ft_unset.c \
	built-ins/ft_exit/ft_clear_allocated.c \
	intialize/list_utils.c \
	execution/execution_addons.c \
	execution/execution_utils.c \
	redirects/cline_delim.c \
	execution/path_finder.c \
	execution/list_to_array.c \
	signals/signals.c \
	utils/utils.c \
	parsing/tokenizer.c \
	parsing/utils.c \
	parsing/utils2.c \
	parsing/utils3.c \
	errors/error.c \
	envp/envp.c \
	envp/envp_utils.c \
	redirections/red.c \
	redirections/red_utils.c \
	clean/clean_structs.c \
	


OBJ = $(SRC:.c=.o)

INCLUDE = -Iinclude -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(INCLUDE) -lreadline


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
