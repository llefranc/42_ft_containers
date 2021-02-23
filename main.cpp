/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/22 12:27:50 by lucaslefran      ###   ########.fr       */
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

struct ok
{
	int a;
	int b;
};

int main()
{
	{
		std::list<std::pair<int, char> > v;

		v.push_back(std::pair<int, char>(1, 'c'));
		v.push_back(std::pair<int, char>(2, 'a'));
		// std::vector<int> x(1, 1);
		std::list<std::pair<int, char> >::iterator it = v.begin();

		std::cout << it->first;
	}
	
	{
		ft::list<ft::pair<int, char> > v;

		v.push_back(ft::pair<int, char>(1, 'c'));
		v.push_back(ft::pair<int, char>(2, 'a'));
		// ft::vector<int> x(1, 1);
		ft::list<ft::pair<int, char> >::iterator it = v.begin();

		std::cout << it->first;
	}
	return (0);
}