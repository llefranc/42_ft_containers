/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 17:10:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TESTS_HPP
#define VECTOR_TESTS_HPP

#include "../includes/tester.hpp"

template <typename T>
void	testOperatorBracelet(T& vec)
{
	printTestNumber(0);
	std::cout << "operator[]: \n\t\t\t";
	
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
}

template <typename T>
void	testSize(T& vec)
{
	printTestNumber(0);
	std::cout << "size: \n\t\t\t";
	
	std::cout << vec.size();
}

template <typename T>
void	testCapacity(T& vec)
{
	printTestNumber(0);
	std::cout << "capacity: \n\t\t\t";
	
	std::cout << vec.capacity();
}

template <typename T>
void	testEmpty(T& vec)
{
	printTestNumber(0);
	std::cout << "empty: \n\t\t\t";
	
	std::cout << vec.empty();
}

template <typename T>
void	testIterators(T& vec)
{
	printTestNumber(0);
	std::cout << "iterators: \n";
	
	std::cout << "\t\t\toperator++: ";
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\t++operator: ";
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " | ";

	if (vec.size())
	{
		std::cout << "\n\t\t\toperator--: ";
		for (typename T::const_iterator it = vec.end(); it != vec.begin() - 1; it--)
			if (it != vec.end())
				std::cout << *it << " | ";

		std::cout << "\n\t\t\t--operator: ";
		for (typename T::const_iterator it = vec.end(); it != vec.begin() - 1; --it)
			if (it != vec.end())
				std::cout << *it << " | ";
	}

	std::cout << "\n\t\t\toperator+=: ";
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); it += 1)
		std::cout << *it << " | ";
	
	std::cout << "\n\t\t\toperator+: ";
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); it = it + 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator-=: ";
	for (typename T::const_iterator it = vec.end() - 1; it != vec.begin() - 1; it -= 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator-: ";
	for (typename T::const_iterator it = vec.end() - 1; it != vec.begin() - 1; it = it - 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator[]: ";
	for (ft::pair<size_t, typename T::const_iterator> i(0, vec.begin()); i.first < vec.size(); ++i.first)
		std::cout << i.second[i.first] << " | ";
}

template <typename T>
void	testReverseIterators(T& vec)
{
	printTestNumber(0);
	std::cout << "reverse iterators: \n";
	
	std::cout << "\t\t\t++operator: ";
	for (typename T::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator++: ";
	for (typename T::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << *it << " | ";	

	if (vec.size())
	{
		std::cout << "\n\t\t\toperator--: ";
		for (typename T::const_reverse_iterator it = vec.rend(); it != vec.rbegin() - 1; it--)
			if (it != vec.rend())
				std::cout << *it << " | ";

		std::cout << "\n\t\t\t--operator: ";
		for (typename T::const_reverse_iterator it = vec.rend(); it != vec.rbegin() - 1; --it)
			if (it != vec.rend())
				std::cout << *it << " | ";
	}

	std::cout << "\n\t\t\toperator+=: ";
	for (typename T::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); it += 1)
		std::cout << *it << " | ";
	
	std::cout << "\n\t\t\toperator+: ";
	for (typename T::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); it = it + 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator-=: ";
	for (typename T::const_reverse_iterator it = vec.rend() - 1; it != vec.rbegin() - 1; it -= 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator-: ";
	for (typename T::const_reverse_iterator it = vec.rend() - 1; it != vec.rbegin() - 1; it = it - 1)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator[]: ";
	for (ft::pair<size_t, typename T::const_reverse_iterator> i(0, vec.rbegin()); i.first < vec.size(); ++i.first)
		std::cout << i.second[i.first] << " | ";
}
template <typename T>
void	testAt(T& vec)
{
	printTestNumber(0);
	std::cout << "at: \n\t\t\t";
	
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
	std::cout << "front: \n\t\t\t";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.front();
}

template <typename T>
void	testBack(T& vec)
{
	printTestNumber(0);
	std::cout << "back: \n\t\t\t";
	
	if (vec.size()) // To prevent overflow
		std::cout << vec.back();
}

template <typename T>
void	testPushBack(T& vec)
{
	printTestNumber(0);
	std::cout << "push_back: \n\t\t\t";
	
	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	T tmp = vec;
	tmp.push_back(*x);
	std::cout << "new elem = " << tmp.back();

	std::cout << "\n\t\t\tnew tmp: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testPopBack(T& vec)
{
	printTestNumber(0);
	std::cout << "pop_back: \n\t\t\t";
	
	if (vec.size())
	{
		T tmp = vec;
		tmp.pop_back();
		if (tmp.size()) // To prevent overflow
			std::cout << "new elem = " << tmp.back();

		std::cout << "\n\t\t\tnew tmp: ";
		for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
			std::cout << *it << " | ";
	}
}

template <typename T>
void	testClear(T& vec)
{
	printTestNumber(0);
	std::cout << "clear: \n\t\t\t";
	
	T tmp = vec;
	std::cout << "size before clear: " << tmp.size() << " | ";
	tmp.clear();
	std::cout << "\n\t\t\tsize after clear: " << tmp.size();

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.push_back(*x);
	std::cout << "\n\t\t\tnew vector: ";
	for (typename T::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testSwap(T& vec)
{
	printTestNumber(0);
	std::cout << "swap member and non member: \n\t\t\t";

	T tmp(vec);
	T tmp2(vec);

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.push_back(*x);
	
	std::cout << "size of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size() << "\n";
	tmp2.swap(tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size() << "\n";

	swap(tmp2, tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size();

	delete x;
}

template <typename T>
void	testResize(T& vec)
{
	printTestNumber(0);
	std::cout << "resize: \n\t\t\t";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign vec[0])
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];

	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << tmp.back();
	std::cout << "\n\t\t\tsize of tmp after resize = " << tmp.size();
	
	delete x;
}

/**
*	Test assign with iterators' range.
*/
template <typename T>
void	testAssign1(T& vec)
{
	printTestNumber(0);
	std::cout << "assign1: \n\t\t\t";

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
	std::cout << "\n\t\t\tsize after assign = " << tmp2.size() << "and content is:\n\t\t\t";

	for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testAssign2(T& vec)
{
	printTestNumber(0);
	std::cout << "assign2: \n\t\t\t";

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
	std::cout << "insert1: \n\t\t\t";

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
	std::cout << "insert2: \n\t\t\t";

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
	std::cout << "insert3: \n\t\t\t";

	T tmp = vec;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	tmp.insert(tmp.begin(), vec.begin(), vec.end());
	if (tmp.size())
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
	std::cout << "erase1: \n\t\t\t";

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
	std::cout << "erase2: \n\t\t\t";

	// Erase first elem
	if (vec.size())
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
void	testOperatorEqualNotEqual(T& vec)
{
	printTestNumber(0);
	std::cout << "operator==/!=: \n\t\t\t";

	T tmp = vec;

	std::cout << "tmp == vec (should be true): " << (tmp == vec) << "\n\t\t\t";
	std::cout << "tmp != vec (should be false): " << (tmp != vec) << "\n\t\t\t";
	
	typename T::value_type* x = new typename T::value_type ();
	if (vec.size())
		*x = vec[0];
	
	tmp.push_back(*x);
	std::cout << "tmp == vec (should be false): " << (tmp == vec) << "\n\t\t\t";
	std::cout << "tmp != vec (should be true): " << (tmp != vec) << "\n\t\t\t";

	T tmp2 = tmp;
	tmp.clear();
	std::cout << "tmp == vec (should be false): " << (tmp2 == tmp) << "\n\t\t\t";
	std::cout << "tmp2 != tmp (should be true): " << (tmp2 != tmp) << "\n\t\t\t";

	tmp2.clear();
	std::cout << "tmp == vec (should be true): " << (tmp2 == tmp) << "\n\t\t\t";
	std::cout << "tmp2 != tmp (should be false): " << (tmp2 != tmp);

	delete x;
}

template <typename T>
void	testOperatorLessAndMore(T& vec)
{
	printTestNumber(0);
	std::cout << "operator</>/<=/>=: \n\t\t\t";

	T tmp = vec;
	typename T::value_type* x = new typename T::value_type ();

	std::cout << "tmp < vec: " << (tmp < vec) << "\n\t\t\t";
	std::cout << "tmp > vec: " << (tmp > vec) << "\n\t\t\t";
	std::cout << "tmp <= vec: " << (tmp <= vec) << "\n\t\t\t";
	std::cout << "tmp >= vec: " << (tmp >= vec) << "\n\t\t\t";
	
	if (vec.size())
		*x = vec.front();
	tmp.push_back(*x);
	
	std::cout << "vec < tmp: " << (vec < tmp) << "\n\t\t\t";
	std::cout << "vec > tmp: " << (vec > tmp) << "\n\t\t\t";
	std::cout << "vec <= tmp: " << (vec <= tmp) << "\n\t\t\t";
	std::cout << "vec >= tmp: " << (vec >= tmp) << "\n\t\t\t";

	T tmp2 = tmp;
	if (vec.size())
		*x = vec.back();
	tmp2.push_back(*x);
	
	std::cout << "tmp2 < tmp: " << (tmp2 < tmp) << "\n\t\t\t";
	std::cout << "tmp2 > tmp: " << (tmp2 > tmp) << "\n\t\t\t";
	std::cout << "tmp2 <= tmp: " << (tmp2 <= tmp) << "\n\t\t\t";
	std::cout << "tmp2 >= tmp: " << (tmp2 >= tmp) << "\n\t\t\t";

	tmp.clear();
	std::cout << "tmp2 < tmp: " << (tmp2 < tmp) << "\n\t\t\t";
	std::cout << "tmp2 > tmp: " << (tmp2 > tmp) << "\n\t\t\t";
	std::cout << "tmp2 <= tmp: " << (tmp2 <= tmp) << "\n\t\t\t";
	std::cout << "tmp2 >= tmp: " << (tmp2 >= tmp) << "\n\t\t\t";

	tmp2.clear();
	std::cout << "tmp2 < tmp: " << (tmp2 < tmp) << "\n\t\t\t";
	std::cout << "tmp2 > tmp: " << (tmp2 > tmp) << "\n\t\t\t";
	std::cout << "tmp2 <= tmp: " << (tmp2 <= tmp) << "\n\t\t\t";
	std::cout << "tmp2 >= tmp: " << (tmp2 >= tmp);

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
	
	// Tests for non-const vectors
	testOperatorBracelet(vec);
	testSize(vec);
	testCapacity(vec);
	testEmpty(vec);
	testIterators(vec);
	testReverseIterators(vec);
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
	testOperatorEqualNotEqual(vec);
	testOperatorLessAndMore(vec);
}

template <typename T>
void	executeAllVecTests(T& vec, int testNb, bool isConst)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING CONST VECTOR " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
	std::cout << "\t\tVECTOR TYPE: ";
	print_type<typename T::value_type>();
	
	// Tests for const vectors
	testOperatorBracelet(vec);
	testSize(vec);
	testCapacity(vec);
	testEmpty(vec);
	testIterators(vec);
	testReverseIterators(vec);
	testAt(vec);
	testFront(vec);
	testBack(vec);

	(void)isConst;
}

#endif