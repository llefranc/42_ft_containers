# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 11:24:58 by llefranc          #+#    #+#              #
#    Updated: 2021/04/07 19:39:08 by lucaslefran      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cont.out
CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98

SRCS		=	main.cpp

HEADER_CON	=	vector.hpp list.hpp stack.hpp queue.hpp map.hpp
HEADER_TEM	=	type1_or_type2.hpp stl_like.hpp
HEADER_ITE	=	vector_iterator.hpp rev_vector_iterator.hpp \
				list_iterator.hpp rev_list_iterator.hpp map_iterator.hpp rev_map_iterator.hpp

PATH_CON	=	containers/
PATH_TEM	=	templates/
PATH_ITE	=	iterators/
				
OBJS		=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			@$(CC) -o $(NAME) $(FLAGS) $(OBJS)
			@echo "\n\n\033[32;1m----- Ft_containers succesfully built -----\033[0;0m\n"

$(OBJS)	:	$(addprefix $(PATH_CON), $(HEADER_CON)) $(addprefix $(PATH_TEM), $(HEADER_TEM)) \
			$(addprefix $(PATH_ITE), $(HEADER_ITE))

clean	:	
				@rm -rf $(OBJS)
				@printf "\033[31;1mObjects removed\n\033[0;0m"

fclean	:	clean
				@rm -rf $(NAME)
				@printf "\033[31;1mExecutable removed\n\033[0;0m"

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.cpp
			@$(CC) $(FLAGS) -o $@ -c $<
			@printf "\033[32;1mCompilation of $(NAME):\033[0;0m $(notdir $<)                             \r"
# for creating .o with flags