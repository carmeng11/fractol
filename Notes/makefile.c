///makefile de IA
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -lX11 -lXext -lm

SRC = main.c fractals.c render.c utils.c
OBJ = $(SRC:.c=.o)
NAME = fractol

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

//makefile de la libft
NAME = libft.a
RM = rm -rf
CC = cc
CFLAGS = -Werror -Wall -Wextra
LIB = ar -rcs
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_memcpy.c ft_memset.c ft_strlen.c ft_tolower.c \
	ft_toupper.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_strnstr.c ft_strlcpy.c ft_memmove.c ft_memcmp.c ft_calloc.c ft_strdup.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
