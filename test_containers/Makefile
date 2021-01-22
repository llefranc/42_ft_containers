# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 11:24:58 by llefranc          #+#    #+#              #
#    Updated: 2021/01/22 15:22:53 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	containers_test
CC			=	clang++
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror -std=c++98

SRCS		=	test_everything.cpp test_all_vectors.cpp

HEADER_CON	=	vector.hpp list.hpp
HEADER_TEM	=	type1_or_type2.hpp stl_like.hpp
HEADER_ITE	=	bidirectional_iterator.hpp random_access_iterator.hpp \
				rev_bidirectional_iterator.hpp rev_random_access_iterator.hpp
HEADER_TEST	=	vector_test.hpp Bob_test.hpp print_type.hpp tester.hpp

PATH_CON	=	../containers/
PATH_TEM	=	../templates/
PATH_ITE	=	../iterators/
				
OBJS		=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJS)	:	$(addprefix $(PATH_CON), $(HEADER_CON)) $(addprefix $(PATH_TEM), $(HEADER_TEM)) \
			$(addprefix $(PATH_ITE), $(HEADER_ITE)) $(HEADER_TEST)

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $<
# for creating .o with flags