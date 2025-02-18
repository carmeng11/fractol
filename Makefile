# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 19:58:37 by cagomez-          #+#    #+#              #
#    Updated: 2025/02/18 19:13:21 by cagomez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
MLX_DIR = ./minilibx-linux
LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext 

SRCS = src/main.c src/events.c src/init.c src/math_utils.c src/render.c src/string_utils.c
OBJS = $(SRCS:.c=.o)

all:  $(NAME)


$(NAME): $(OBJS)

	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean

	rm -f $(NAME)

re: fclean all
