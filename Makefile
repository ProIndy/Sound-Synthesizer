# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:52 by ijaaskel          #+#    #+#              #
#    Updated: 2023/02/23 14:56:54 by ijaaskel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minisynth

SRC			=	minisynth.c

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

LIBFT		=	-Llibft/ -lft

UNAME		:=	$(shell uname -s)
ifeq ($(UNAME), Darwin)

FRAMEWORKS	=	-framework IOKit 	\
				-framework Cocoa	\
				-framework OpenGL	\
				`pkg-config --libs --cflags raylib`

INCLUDES	=	-I./include/ -I./libft/includes/

endif

ifeq ($(UNAME), Linux)

FRAMEWORKS	=	-Lraylib/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

INCLUDES	=	-I./raylib/src/ -I./libft/includes/

endif

HDR			=	minisynth.h

all:			$(NAME)

$(NAME):
	@make -C libft/
	@$(CC) $(FLAGS) $(SRC) $(INCLUDES) $(LIBFT) $(FRAMEWORKS) -o $(NAME)

clean:
	@make -C libft/ clean

fclean:			clean
	@make -C libft/ fclean
	@rm -vf $(NAME)

re:				fclean all

rec:			re
	@make clean

.PHONY: all clean flcean re rec
