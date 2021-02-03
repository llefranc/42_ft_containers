/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/03 10:35:37 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "templates/stl_like.hpp"
#include "test_containers/includes/Bob_test.hpp"

#include "../42_Containator/includes_and_utils/print_type.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>
#include <stack>
#include <queue>

int main()
{
	{
		std::stack<int> s;
		std::stack<int> s2;

		s2 = s;

		std::cout << s.empty();
		std::cout << s2.empty();
	}
	
	{
		ft::stack<int> s;
		ft::stack<int> s2;

		s2 = s;

		std::cout << s.empty();
		std::cout << s2.empty();
	}

	{
		std::queue<int> s;
		std::queue<int> s2;

		s2 = s;

		std::cout << s.empty();
		std::cout << s2.empty();
	}
	
	{
		ft::queue<int> s;
		ft::queue<int> s2;

		s2 = s;

		std::cout << s.empty();
		std::cout << s2.empty();
	}

	return (0);
}