/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/27 17:06:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "templates/stl_like.hpp"
#include "test_containers/includes/Bob_test.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>

int main()
{
	ft::vector<int> ft;
	ft.push_back(58966);
	ft.push_back(2147483647);

	ft.erase(ft.end(), ft.end());
	
	for (ft::vector<int>::iterator it = ft.begin(); it != ft.end(); ++it)
		std::cout << *it << " | ";
	// ft::vector<int> ft2;
	
	// ft2 = ft;
	// std::cout << *ft.erase(ft.begin()) << "\n";
	// std::cout << *ft2.erase(ft2.begin()) << "\n";

	// ft::vector<int> std;
	// std.push_back(58966);
	// std.push_back(2147483647);
	
	// ft::vector<int> std2;
	
	// std2 = std;
	// std::cout << *std.erase(std.begin()) << "\n";
	// std::cout << *std2.erase(std2.begin()) << "\n";



	return (0);
}


