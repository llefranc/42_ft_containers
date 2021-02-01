/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/01 16:57:41 by llefranc         ###   ########.fr       */
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
		std::list<int> x2;

		for (int i = 20; i > 0; i -= 2)
		{	x2.push_back(i);
			x2.push_back(i);}
		x2.push_back(100);

		x2.sort();

		std::cout << "\nx2: ";
		for(std::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}

	{
		ft::list<int> x2;

		for (int i = 20; i > 0; i -= 2)
		{	x2.push_back(i);
			x2.push_back(i);}
		x2.push_back(100);

		x2.sort();

		std::cout << "\nx2: ";
		for(ft::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}
	return (0);
}