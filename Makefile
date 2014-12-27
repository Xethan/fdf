# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/14 11:02:20 by ncolliau          #+#    #+#              #
#    Updated: 2014/12/27 15:05:59 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c get_next_line.c get_map.c

OBJ = $(SRC:.c=.o)

PATH_INCLUDES = ./includes

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, make_libft, clean, fclean, re, norme

all : make_libft $(NAME)

$(NAME) : $(SRC)
			gcc $(FLAGS) -I $(PATH_INCLUDES) -c $(SRC) \
			-L /usr/X11/lib -lmlx -lXext -lX11 -lm
			gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a \
			-L /usr/X11/lib -lmlx -lXext -lX11 -lm

make_libft :
			make -C libft/

clean :
			@rm -f $(OBJ)
			@echo "clean done"
			make -C libft/ clean

fclean : clean
			rm -f $(NAME)
			rm -f libft/libft.a

re : fclean all

norme :
			norminette $(SRC) \
			includes/fdf.h includes/get_next_line.h includes/libft.h
			make -C libft/ norme