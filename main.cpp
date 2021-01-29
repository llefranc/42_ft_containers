/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/29 16:49:16 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "templates/stl_like.hpp"
#include "test_containers/includes/Bob_test.hpp"

#include "../42_Containator/includes_and_utils/print_type.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>

int main()
{
	{
		std::list<int> x;

		for (int i = 0; i < 10; ++i)
			x.push_back(i);

		std::list<int> x2;

		// x2.push_back(20);
		for (int i = 0; i < 20; i += 2)
		{	x2.push_back(i);
			x2.push_back(i);}
		
		// std::cout << "-------- STD\nx2: ";
		// for(std::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
		// 	std::cout << *it << " | ";
		// std::cout << "\nsize of x2 = " << x2.size() << "\n";		

		x.merge(x2);

		std::cout << "\nx: ";
		for(std::list<int>::iterator it = x.begin(); it != x.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x = " << x.size() << "\n";

		std::cout << "\nx2: ";
		for(std::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}

	{
		ft::list<int> x;

		for (int i = 0; i < 10; ++i)
			x.push_back(i);

		ft::list<int> x2;

		x2.push_back(20);
		for (int i = 0; i < 20; i += 2)
		{	x2.push_back(i);
			x2.push_back(i);}
		
		// std::cout << "-------- FT\nx2: ";
		// for(ft::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
		// 	std::cout << *it << " | ";
		// std::cout << "\nsize of x2 = " << x2.size() << "\n";


		x.merge(x2);

		std::cout << "\nx: ";
		for(ft::list<int>::iterator it = x.begin(); it != x.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x = " << x.size() << "\n";

		std::cout << "\nx2: ";
		for(ft::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}
	return (0);
}