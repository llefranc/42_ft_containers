# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 11:24:58 by llefranc          #+#    #+#              #
#    Updated: 2021/01/04 14:16:23 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	containers
CC			=	clang++
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror -std=c++98

SRCS		=	main.cpp 
HEADER		=	Vector.hpp
				
OBJS		=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJS)	:	$(HEADER)

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $<
# for creating .o with flags