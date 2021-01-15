/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/15 17:37:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEST_HPP
#define VECTOR_TEST_HPP

#include "../containers/vector.hpp"
#include "../templates/stl_like.hpp"
#include "print_type.hpp"

void	printTestNumber(int *nb);

template <typename T>
void	testOperatorBracelet(T& vec)
{
	printTestNumber(0);
	std::cout << "operator[]: ";
	
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void	testSize(T& vec)
{
	printTestNumber(0);
	std::cout << "size: ";
	
	std::cout << vec.size() << std::endl;
}

template <typename T>
void	testCapacity(T& vec)
{
	printTestNumber(0);
	std::cout << "capacity: ";
	
	std::cout << vec.capacity() << std::endl;
}

template <typename T>
void	testEmpty(T& vec)
{
	printTestNumber(0);
	std::cout << "empty: ";
	
	std::cout << vec.empty() << std::endl;
}

template <typename T>
void	testIterators(T& vec)
{
	printTestNumber(0);
	std::cout << "iterators: ";
	
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename T>
void	testAt(T& vec)
{
	printTestNumber(0);
	std::cout << "at: ";
	
	for (size_t i = 0; i < vec.size(); ++i)
	{
		try
		{
			std::cout << vec.at(i) << " ";
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}
	}
	
	// Throwing an exception
	try
	{
		std::cout << vec.at(100000) << " ";
	}
	catch (std::out_of_range& e)
	{
		std::cout << e.what();
	}
	
	std::cout << std::endl;
}

template <typename T>
void	testFront(T& vec)
{
	printTestNumber(0);
	std::cout << "front: ";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.front() << std::endl;
}

template <typename T>
void	testBack(T& vec)
{
	printTestNumber(0);
	std::cout << "back: ";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.back() << std::endl;
}

template <typename T>
void	testPushBack(T& vec)
{
	printTestNumber(0);
	std::cout << "push_back: ";
	
	if (vec.size())
		vec.push_back(*vec.begin());
	std::cout << "new elem = " << vec.back();
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb)
{
	std::cout << "\n-------------------------------\n";
	std::cout << "------- TESTING VECTOR " << testNb << " ------\n";
	std::cout << "-------------------------------\n";
	
	std::cout << "\t\tVECTOR TYPE: ";
	print_type<typename T::value_type>();
	
	// Tests for non-const vectors
	testOperatorBracelet(vec);
	testSize(vec);
	testCapacity(vec);
	testEmpty(vec);
	testIterators(vec);
	testAt(vec);
	testFront(vec);
	testBack(vec);
	testPushBack(vec);
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb, bool isConst)
{
	std::cout << "\n-------------------------------\n";
	std::cout << "------- TESTING VECTOR " << testNb << " ------\n";
	std::cout << "-------------------------------\n";
	
	std::cout << "\t\tVECTOR TYPE: ";
	print_type<typename T::value_type>();
	
	// Tests for const vectors
	testOperatorBracelet(vec);
	testSize(vec);
	testCapacity(vec);
	testEmpty(vec);
	testIterators(vec);
	testAt(vec);
	testFront(vec);
	testBack(vec);

	if (!isConst)
		return ;
}

#endif