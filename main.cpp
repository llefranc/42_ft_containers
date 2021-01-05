/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/05 11:48:24 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

#include <iostream>

#include <vector>


int main()
{
	ft::vector<int> vec(5, 100);

	ft::vector<int>::iterator it = vec.begin();
	std::cout << "it = " << *it << "\n";
	*it = 5;
	std::cout << "it = " << *it << "\n";
	// ft::vector<int> vec((unsigned long int)5, nb);
	// std::vector<int> vec(5, 100);
	
	ft::vector<int> vec2;

	return (0);
}