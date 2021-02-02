/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/01 20:23:35 by lucaslefran      ###   ########.fr       */
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
		
		int tab[5] = {58966, 2147483647, 256, -2147483648, 0};

		for (int i = 0; i < 5; i++)
			x2.push_back(tab[i]);
		// x2.push_back(100);
		
		std::cout << "\nx2: avant: ";
		for(std::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";

		x2.sort();

		std::cout << "\nx2: apres: ";
		for(std::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}

	{
		ft::list<int> x2;
		
		int tab[5] = {58966, 2147483647, 256, -2147483648, 0};

		for (int i = 0; i < 5; i++)
			x2.push_back(tab[i]);
		// x2.push_back(100);
		
		std::cout << "\nx2: avant: ";
		for(ft::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";

		x2.sort();

		std::cout << "\nx2: apres: ";
		for(ft::list<int>::iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << *it << " | ";
		std::cout << "\nsize of x2 = " << x2.size() << "\n";
	}
	
	// {
	// 	ft::list<int> *x = new ft::list<int> ();
	// 	// ft::list<int> *x = new ft::list<int> ();

	// 	for (int i = 0; i < 4; ++i)
	// 		x->push_back(i);

	// 	ft::list<int>::iterator a = x->begin();
	// 	ft::list<int>::iterator b = --(--x->end());

	// 	std::cout << "avatn swap: ";
	// 	for(ft::list<int>::iterator it = x->begin(); it != x->end(); ++it)
	// 		std::cout << *it << " | ";
	// 	std::cout << "\n";

	// 	x->swap2Nodes(b.getNonConstPointer(), a.getNonConstPointer());
	// 	// x->swap2Nodes(a.getNonConstPointer(), b.getNonConstPointer());
		
	// 	std::cout << "apres swap: ";
	// 	for(ft::list<int>::iterator it = x->begin(); it != x->end(); ++it)
	// 		std::cout << *it << " | ";
	// 	std::cout << "\n";
	// }
	return (0);
}