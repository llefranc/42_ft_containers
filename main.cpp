/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/11 16:58:13 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "containers/list.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "containers/map.hpp"
#include "templates/stl_like.hpp"

#include "../42_Containator/includes_and_utils/print_type.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

int main()
{

	// std::map<int, char> stx;
	// std::pair<const int, char> pad(1, 'c'); // penser a regler le probleme de la pair
	// stx.insert(pad);

	// std::map<int, char>::const_iterator itendx = stx.end();

	// itendx--;
	// itendx++;
	// --itendx;

	// std::cout << "first = " << (*itendx).first << "\n";
	// std::cout << " and second = " << itendx->second << "\n";

	std::vector<int> vec(1, 0);

{
	ft::map<int, char> x;

	ft::pair<const int, char> pa1(1, 'c'); // penser a regler le probleme de la pair
	ft::pair<const int, char> pa2(2, 'a'); // penser a regler le probleme de la pair
	ft::pair<const int, char> pa3(0, 'p'); // penser a regler le probleme de la pair
	ft::pair<const int, char> pa4(4, 'z'); // penser a regler le probleme de la pair
	x.insert(pa1);
	x.insert(pa2);
	x.insert(pa3);
	x.insert(pa4);

	for (ft::map<int, char>::iterator it = x.begin(); it != x.end(); ++it)
		std::cout << "first = " << it->first << " and second = " << it->second << "\n";
	std::cout << "----------------\n";
	
	for (ft::map<int, char>::iterator it = x.begin(); it != x.end(); it++)
		std::cout << "first = " << it->first << " and second = " << it->second << "\n";
	std::cout << "----------------\n";

	for (ft::map<int, char>::iterator it = --x.end(); it != --x.begin(); --it)
		std::cout << "first = " << it->first << " and second = " << it->second << "\n";
	std::cout << "----------------\n";

	for (ft::map<int, char>::iterator it = --x.end(); it != --x.begin(); it--)
		std::cout << "first = " << it->first << " and second = " << it->second << "\n";
	std::cout << "----------------\n";
}



	return (0);
}