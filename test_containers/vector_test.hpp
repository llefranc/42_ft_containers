/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/16 22:22:26 by lucaslefran      ###   ########.fr       */
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
}

template <typename T>
void	testSize(T& vec)
{
	printTestNumber(0);
	std::cout << "size: ";
	
	std::cout << vec.size();
}

template <typename T>
void	testCapacity(T& vec)
{
	printTestNumber(0);
	std::cout << "capacity: ";
	
	std::cout << vec.capacity();
}

template <typename T>
void	testEmpty(T& vec)
{
	printTestNumber(0);
	std::cout << "empty: ";
	
	std::cout << vec.empty();
}

template <typename T>
void	testIterators(T& vec)
{
	printTestNumber(0);
	std::cout << "iterators: ";
	
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
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
}

template <typename T>
void	testFront(T& vec)
{
	printTestNumber(0);
	std::cout << "front: ";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.front();
}

template <typename T>
void	testBack(T& vec)
{
	printTestNumber(0);
	std::cout << "back: ";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.back();
}

template <typename T>
void	testPushBack(T& vec)
{
	printTestNumber(0);
	std::cout << "push_back: ";
	
	if (vec.size())
	{
		typename T::value_type x(vec[0]);
		vec.push_back(x);
		std::cout << "new elem = " << vec.back();
	}
}

template <typename T>
void	testPopBack(T& vec)
{
	printTestNumber(0);
	std::cout << "pop_back: ";
	
	if (vec.size())
	{
		vec.pop_back();
		std::cout << "new elem = " << vec.back();
	}
}

template <typename T>
void	testClear(T& vec)
{
	printTestNumber(0);
	std::cout << "clear: ";
	
	std::cout << "size before clear: " << vec.size() << " | ";
	vec.clear();
	std::cout << "size after clear: " << vec.size();
}

template <typename T>
void	testSwap(T& vec)
{
	printTestNumber(0);
	std::cout << "swap: ";

	T tmp(vec);
	if (vec.size())
	{
		typename T::value_type x = vec[0];
		tmp.push_back(x);
	}
	std::cout << "size of tmp = " << tmp.size() << " and size of vec = " << vec.size() << "\n";
	vec.swap(tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of vec = " << vec.size();
}

template <typename T>
void	testResize(T& vec)
{
	printTestNumber(0);
	std::cout << "resize: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	if (tmp.size())
	{
		typename T::value_type x = vec[0];
		tmp.resize(3, x);
		std::cout << "new elem = " << vec.back();
	}
	else
		tmp.resize(3);

	std::cout << "\t\t\tsize of tmp after resize = " << tmp.size();
}

template <typename T>
void	testAssign(T& vec)
{
	printTestNumber(0);
	std::cout << "assign: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	if (tmp.size())
	{
		typename T::value_type x = vec[0];
		tmp.resize(3, x);
		std::cout << "\t\t\tnew elem = " << vec.back();
	}
	else
		tmp.resize(3);

	T tmp2 = vec;
	tmp2.assign(tmp.begin(), tmp.end());
	std::cout << "\t\t\tsize after assign = " << tmp2.size() << "and content is:\n\t\t\t";

	for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
		std::cout << *it << " | ";
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING VECTOR " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
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
	testPopBack(vec);
	testSwap(vec);
	testResize(vec);
	testAssign(vec);
	testClear(vec);
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb, bool isConst)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING VECTOR " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
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