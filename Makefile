# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/14 11:02:20 by ncolliau          #+#    #+#              #
#    Updated: 2014/12/14 12:33:36 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c get_next_line.c get_map.c handle_line_list.c

OBJ = $(SRC:.c=.o)

PATH_INCLUDES = ./includes

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, make_libft, clean, fclean, re, norme

all : make_libft $(NAME)

$(NAME) : $(SRC)
			gcc $(FLAGS) -I $(PATH_INCLUDES) -c $(SRC) -L /usr/X11/lib -lmlx -lXext -lX11
			gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -L /usr/X11/lib -lmlx -lXext -lX11

make_libft :
			make -C libft/
			make -C libft/ clean

clean :
			@rm -f $(OBJ)
			@echo "clean done"

fclean : clean
			rm -f $(NAME)

re : fclean all

norme :
			norminette $(SRC)
			make -C libft/ norme