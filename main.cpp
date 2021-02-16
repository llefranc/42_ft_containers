/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/16 15:53:51 by llefranc         ###   ########.fr       */
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

	{
		ft::map<int, char> x;

		ft::pair<int, char> pa1(1, 'c'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa2(2, 'a'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa3(0, 'p'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa4(4, 'z'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa5(8, 'z'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa6(-4, 'z'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa7(3, 'z'); // penser a regler le probleme de la pair
		ft::pair<int, char> pa8(5, 'z'); // penser a regler le probleme de la pair
		x.insert(pa1);
		x.insert(pa2);
		x.insert(pa3);
		x.insert(pa4);
		x.insert(pa5);
		x.insert(pa6);
		x.insert(pa7);
		x.insert(pa8);

		std::cout << "\n\n---------------------\n\n";

		ft::pair<int, char> pa9(-6, 'z'); // penser a regler le probleme de la pair

		x.insert(x.begin(), pa9);

		std::cout << x[-6] << "\n";

		

		for (ft::map<int, char>::const_iterator it = x.begin(); it != x.end(); ++it)
			std::cout << "[" << it->first << "][" << it->second << "] | ";

		ft::map<int, char> x2;
			

		for (ft::map<int, char>::const_iterator it = x.begin(); it != x.end(); ++it)
			x2[it->first] = it->second;
		std::cout << "\n-------------------------\n";

		for (ft::map<int, char>::const_iterator it = x2.begin(); it != x2.end(); ++it)
			std::cout << "[" << it->first << "][" << it->second << "] | ";

		// x.clear();

		// x.insert(pa1);

		// for (ft::map<int, char>::const_reverse_iterator it = x.rbegin(); it != x.rend(); ++it)
		// 	std::cout << "[" << it->first << "][" << it->second << "] | ";
		// std::cout << "\n-------------------------\n";


		// std::string s = "salut";

		// std::pair<int, char> p;
		// std::cout << sizeof(p.first) << "et size " << sizeof(p.second) << "\n";
	}
	// std::cout << "\n\n TESTING STD \n";
	// {
	// 	std::map<int, char> x;

	// 	std::pair<int, char> pa1(1, 'c'); // penser a regler le probleme de la pair
	// 	std::pair<int, char> pa2(2, 'a'); // penser a regler le probleme de la pair
	// 	std::pair<int, char> pa3(0, 'p'); // penser a regler le probleme de la pair
	// 	std::pair<int, char> pa4(4, 'z'); // penser a regler le probleme de la pair
	// 	std::pair<int, char> pa5(8, 'z'); // penser a regler le probleme de la pair
	// 	std::pair<int, char> pa6(-4, 'z'); // penser a regler le probleme de la pair
	// 	// std::pair<int, char> pa7(3, 'z'); // penser a regler le probleme de la pair
	// 	// std::pair<int, char> pa8(5, 'z'); // penser a regler le probleme de la pair
	// 	x.insert(pa1);
	// 	x.insert(pa2);
	// 	x.insert(pa3);
	// 	x.insert(pa4);
	// 	x.insert(pa5);
	// 	x.insert(pa6);
	// 	// x.insert(pa7);
	// 	// x.insert(pa8);

	// 	for (std::map<int, char>::const_iterator it = x.begin(); it != x.end(); ++it)
	// 		std::cout << "[" << it->first << "][" << it->second << "] | ";
	// 	std::cout << "\n-------------------------\n";

	// 	for (std::map<int, char>::const_reverse_iterator it = x.rbegin(); it != x.rend(); ++it)
	// 		std::cout << "[" << it->first << "][" << it->second << "] | ";
	// 	std::cout << "\n-------------------------\n";

	// }

	return (0);
}