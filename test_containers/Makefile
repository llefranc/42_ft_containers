# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 11:24:58 by llefranc          #+#    #+#              #
#    Updated: 2021/01/26 14:00:38 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	containers_test
CC			=	clang++
FLAGS		=	-g -fsanitize=address -Wall -Wextra -Werror -std=c++98

SRCS		=	test_everything.cpp each_tests/vector_defs.cpp each_tests/list_defs.cpp

HEADER_CON	=	vector.hpp list.hpp
PATH_CON	=	../containers/

HEADER_TEM	=	type1_or_type2.hpp stl_like.hpp
PATH_TEM	=	../templates/

HEADER_ITE	=	bidirectional_iterator.hpp random_access_iterator.hpp \
				rev_bidirectional_iterator.hpp rev_random_access_iterator.hpp \
				list_iterator.hpp rev_list_iterator.hpp
PATH_ITE	=	../iterators/
				
HEADER_INC	=	Bob_test.hpp print_type.hpp tester.hpp
PATH_INC	=	includes/

HEADER_TEST	=	vector_tests.hpp list_tests.hpp
PATH_TEST	=	each_tests/


				
OBJS		=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJS)	:	$(addprefix $(PATH_CON), $(HEADER_CON)) $(addprefix $(PATH_TEM), $(HEADER_TEM)) \
			$(addprefix $(PATH_ITE), $(HEADER_ITE)) $(addprefix $(PATH_TEST), $(HEADER_TEST)) \
			$(addprefix $(PATH_INC), $(HEADER_INC))

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.cpp
			$(CC) $(FLAGS) -o $@ -c $<
# for creating .o with flags