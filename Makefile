# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/14 11:02:20 by ncolliau          #+#    #+#              #
#    Updated: 2015/01/08 19:19:42 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

OBJ = fdf.o get_next_line.o get_map.o draw.o key_hook.o tools.o tools_bis.o

PATH_INCLUDES = ./includes

FLAGS = -Wall -Wextra -Werror

LIB = -L /usr/X11/lib -lmlx -lXext -lX11 -lm

.PHONY: make, all, $(NAME), libft/libft.a, clean, fclean, re, norme

all : $(NAME)

$(NAME) : $(OBJ) libft/libft.a
			gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a $(LIB)

$(OBJ): %.o: %.c includes/fdf.h includes/get_next_line.h
			gcc $(FLAGS) -I $(PATH_INCLUDES) -c $< -o $@

libft/libft.a :
			make -C libft/

clean :
			@rm -f $(OBJ)
			@echo "clean done"

fclean : clean
			rm -f $(NAME)

re : fclean all

norme :
			norminette $(OBJ:.o=.c) \
			includes/fdf.h includes/get_next_line.h includes/libft.h
			make -C libft/ norme
