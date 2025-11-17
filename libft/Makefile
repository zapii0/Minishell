NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
         ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
         ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
         ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
         ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
         ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		 get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c \
		 ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_listsize_bonus.c ft_lstlast_bonus.c \
         ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
         ft_lstmap_bonus.c

OBJECTS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -c -I$(PRINTF)

PRINTF = ft_printf

AR = ar rcs

RM = rm -f

all: $(NAME)
	mv $(NAME) ft_printf/
	@make -C ft_printf/
	mv ft_printf/libft.a .

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	@make clean -C $(PRINTF)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(PRINTF)
	$(RM) a.out

re: fclean all

.PHONY: all, clean, fclean, re