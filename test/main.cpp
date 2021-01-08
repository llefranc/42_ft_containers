/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:53:26 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/08 15:17:41 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "template.hpp"

const int*	func(const int* ptr)
{
	return (ptr);
}

class bob
{
	public:
	bob(int& nb) {ptr = &nb;}

	const int& operator*() const
	{
		return (*ptr);
	}

	int& operator++() {return *(++ptr);}


	private:
		int *ptr;
};

#include <vector>


int main()
{
	// put<float, 0>();

	// Random<> random;

	// random.printSize();
	// Random<char> rand;
	// rand.printSize();

	// std::cout <<"\n--------\n";
	// Test<int, std::string, Random> test(5, 3);

	// test.printU();
	// test.printV();

	int nb = 5;

	bob billy(nb);
	
	++billy;
	// *billy = 2;
	// ptr2 = func(ptr);
	
	std::vector<int> vec(5, 100);

	std::vector<int>::const_iterator it = vec.begin();
	*it = 5;
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " | ";
	std::cout << "\n";


	return (0);
}