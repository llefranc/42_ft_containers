/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/22 16:30:13 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "templates/stl_like.hpp"
#include "test_containers/Bob_test.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>

int main()
{
	
	// Bob bob;

	
	std::cout << "\nTEST FT\n";
	const ft::list<int> lis(3, 4);

	for (ft::list<int>::const_iterator it = lis.begin(); it != lis.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n";



	// std::cout << "\nTEST STD\n";
	// std::list<int> ls(1, bob);

	// std::cout <<bob << "\n";
	// std::cout << "\nend main\n";

	return (0);
}