/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 14:55:26 by llefranc         ###   ########.fr       */
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
	std::vector<int> v;
	std::vector<char> v1;
	std::vector<std::string> v2;

	std::list<int> l;
	std::list<char> l1;
	std::list<std::string> l2;

	std::cout << v.max_size() /8 << "\t| " << v1.max_size() << "\t| " << v2.max_size()/2 << " \n";
	std::cout << l.max_size() << "\t| " << l1.max_size() << "\t| " << l2.max_size() << " \n";

	return (0);
}


