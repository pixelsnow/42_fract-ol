# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 20:54:01 by vvagapov          #+#    #+#              #
#    Updated: 2023/06/02 21:10:12 by vvagapov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = fractol.c \

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/libft.a
LIBFTDIR = libft

FLAGS = -Wall -Wextra -Werror
INC = -I /usr/local/include
LMX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	cc $(INC) $(SRC) $(LMX) -o $(NAME)

%.o: %.c
	cc -c $(FLAGS) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re