/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 13:12:39 by llefranc         ###   ########.fr       */
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
	
	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	vec.push_back(*x);
	std::cout << "new elem = " << vec.back();

	delete x;
}

template <typename T>
void	testPopBack(T& vec)
{
	printTestNumber(0);
	std::cout << "pop_back: ";
	
	if (vec.size())
	{
		vec.pop_back();
		if (vec.size()) // To prevent overflow
			std::cout << "new elem = " << vec.back();
	}
}

template <typename T>
void	testClear(T& vec)
{
	printTestNumber(0);
	std::cout << "clear: ";
	
	T tmp = vec;
	std::cout << "size before clear: " << tmp.size() << " | ";
	tmp.clear();
	std::cout << "size after clear: " << tmp.size();

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.push_back(*x);
	std::cout << "new elem pushed after clear: " << tmp.back();

	delete x;
}

template <typename T>
void	testSwap(T& vec)
{
	printTestNumber(0);
	std::cout << "swap: ";

	T tmp(vec);

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.push_back(*x);
	
	std::cout << "size of tmp = " << tmp.size() << " and size of vec = " << vec.size() << "\n";
	vec.swap(tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of vec = " << vec.size();

	delete x;
}

template <typename T>
void	testResize(T& vec)
{
	printTestNumber(0);
	std::cout << "resize: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << vec.back();
	std::cout << "\t\t\tsize of tmp after resize = " << tmp.size();
	
	delete x;
}

template <typename T>
void	testAssign1(T& vec)
{
	printTestNumber(0);
	std::cout << "assign1: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << tmp.back();

	T tmp2 = vec;
	tmp2.assign(tmp.begin(), tmp.end());
	std::cout << "\t\t\tsize after assign = " << tmp2.size() << "and content is:\n\t\t\t";

	if (vec.size())
		for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
			std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testAssign2(T& vec)
{
	printTestNumber(0);
	std::cout << "assign2: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];
		
	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << tmp.back();

	T tmp2 = vec;
	tmp2.assign(tmp.size(), tmp.front());
	std::cout << "\t\t\tsize after assign = " << tmp2.size() << "and content is:\n\t\t\t";

	for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
		std::cout << *it << " | ";
		
	delete x;
}

template <typename T>
void	testInsert1(T& vec)
{
	printTestNumber(0);
	std::cout << "insert1: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
	{
		*x = vec.front();
		std::cout << "\t\t\treturn value: " << *tmp.insert(tmp.begin() + 1, *x) << "\n";
	}
	std::cout << "\t\t\treturn value: " << *tmp.insert(tmp.begin(), *x) << "\n";
	std::cout << "\t\t\treturn value: " << *tmp.insert(tmp.end(), *x) << "\n";
	
	std::cout << "\t\t\t";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();

	delete x;
}

template <typename T>
void	testInsert2(T& vec)
{
	printTestNumber(0);
	std::cout << "insert2: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
	{
		*x = vec.front();
		tmp.insert(tmp.begin() + 1, 5, *x);
	}
	tmp.insert(tmp.begin(), 5, *x);
	tmp.insert(tmp.end(), 5, *x);
	
	std::cout << "\t\t\t";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();

	delete x;
}

template <typename T>
void	testInsert3(T& vec)
{
	printTestNumber(0);
	std::cout << "insert3: ";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	tmp.insert(tmp.begin(), vec.begin(), vec.end());
	tmp.insert(tmp.begin() + 1, vec.begin(), vec.end());
	tmp.insert(tmp.end(), vec.begin(), vec.end());
	tmp.insert(tmp.end(), vec.begin(), vec.begin());
	
	std::cout << "\t\t\t";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();
}

template <typename T>
void	testErase1(T& vec)
{
	printTestNumber(0);
	std::cout << "erase1: ";

	// Erase everything
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.begin(), tmp.end());
		if (tmp.size())
			std::cout << "new elem after erase: " << *iter << "\n\t\t\t";

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";
	}

	// Erase nothing
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.end(), tmp.end());
		
		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "\n\t\t\tsize of tmp = " << tmp.size();

		iter = tmp.erase(tmp.begin(), tmp.begin());
		if (tmp.size())
			std::cout << "\n\t\t\tnew elem after erase: " << *iter << "\n\t\t\t";
	}
	
	// Erase last elem
	if (vec.size())
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.end() - 1, tmp.end());

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "\n\t\t\tsize of tmp = " << tmp.size() << "\n\t\t\t";
	}

	// Erase everything except first elem
	if (vec.size())
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.begin() + 1, tmp.end());

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "\n\t\t\tsize of tmp = " << tmp.size();
	}
}

template <typename T>
void	testErase2(T& vec)
{
	printTestNumber(0);
	std::cout << "erase2: ";

	// Erase first elem
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.begin());
		if (tmp.size())
			std::cout << "new elem after erase: " << *iter << "\n\t\t\t";

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";
	}

	// Erase last elem
	if (vec.size())
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.end() - 1);

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "\n\t\t\tsize of tmp = " << tmp.size() << "\n\t\t\t";
	}

	// Erase one elem
	if (vec.size() > 1)
	{
		T tmp = vec;
		std::cout << "size of tmp = " << tmp.size() << "\n\t\t\t";

		typename T::iterator iter = tmp.erase(tmp.begin() + 1);

		for (typename T::iterator it = tmp.begin(); it != iter; ++it)
			std::cout << *it << " | ";
		std::cout << "\n\t\t\tsize of tmp = " << tmp.size();
	}
}

template <typename T>
void	testOperatorEqual(T& vec)
{
	printTestNumber(0);
	std::cout << "operator=: ";

	T tmp = vec;

	std::cout << "tmp == vec (should be true): " << (tmp == vec) << "\n\t\t\t";
	
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];
	
	tmp.push_back(*x);
	std::cout << "tmp == vec (should be false): " << (tmp == vec) << "\n\t\t\t";

	delete x;
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING VECTOR " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
	std::cout << "\t\tVECTOR TYPE: ";
	print_type<typename T::value_type>();
	
	(void)vec;

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
	testAssign1(vec);
	testAssign2(vec);
	testInsert1(vec);
	testInsert2(vec);
	testInsert3(vec);
	testErase1(vec);
	testErase2(vec);
	testClear(vec);
	testOperatorEqual(vec);
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
	// testOperatorEqual(vec);
	
	if (!isConst)
		return ;
}

#endif