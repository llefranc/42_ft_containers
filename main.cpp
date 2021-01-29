/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/29 15:21:12 by llefranc         ###   ########.fr       */
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
	ft::list<int> x(1, 97);

	for (int i = 98; i < 105; ++i)
		x.push_back(i);

	x.push_front(102);

	x.remove_if(predicateTest<int>);

	for (ft::list<int>::iterator it = x.begin(); it != x.end(); ++it)
		std::cout << *it << " | ";
	
	return (0);
}