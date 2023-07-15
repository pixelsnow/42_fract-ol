# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 20:54:01 by vvagapov          #+#    #+#              #
#    Updated: 2023/07/15 15:32:26 by vvagapov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = fractol.c \
	atof.c \
	colors.c \
	controls_keyboard.c \
	controls_mouse.c \
	fractals.c \
	graphic_utils.c \
	input.c \
	utils.c \
	validation.c

OBJ = $(SRC:%.c=%.o)

HEADER = fractol.h

LIBFT = libft/libft.a
LIBFTDIR = libft

FLAGS = -Wall -Wextra -Werror
INC = -I /usr/local/include
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc $(INC) $(SRC) $(MLX) -o $(NAME)

%.o: %.c
	cc -c $(FLAGS) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re