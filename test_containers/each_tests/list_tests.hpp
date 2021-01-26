/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tests.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 19:48:48 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TESTS_HPP
#define LIST_TESTS_HPP

#include "../includes/tester.hpp"

void	printTestNumber(int *nb);

template <typename T>
void	testSize(T& lis)
{
	printTestNumber(0);
	std::cout << "size: \n\t\t\t";
	
	std::cout << lis.size();
}

template <typename T>
void	testIterators(T& lis)
{
	printTestNumber(0);
	std::cout << "iterators: \n";
	
	std::cout << "\t\t\toperator++: ";
	for (typename T::const_iterator it = lis.begin(); it != lis.end(); it++)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\t++operator: ";
	for (typename T::const_iterator it = lis.begin(); it != lis.end(); ++it)
		std::cout << *it << " | ";

	if (lis.size())
	{
		std::cout << "\n\t\t\toperator--: ";
		for (typename T::const_reverse_iterator it = lis.rend(); it != --lis.rbegin(); it--)
			if (it != lis.rend())
				std::cout << *it << " | ";

		std::cout << "\n\t\t\t--operator: ";
		for (typename T::const_reverse_iterator it = lis.rend(); it != --lis.rbegin(); --it)
			if (it != lis.rend())
				std::cout << *it << " | ";
	}
}

template <typename T>
void	testReverseIterators(T& lis)
{
	printTestNumber(0);
	std::cout << "reverse iterators: \n";
	
	std::cout << "\t\t\t++operator: ";
	for (typename T::const_reverse_iterator it = lis.rbegin(); it != lis.rend(); ++it)
		std::cout << *it << " | ";

	std::cout << "\n\t\t\toperator++: ";
	for (typename T::const_reverse_iterator it = lis.rbegin(); it != lis.rend(); it++)
		std::cout << *it << " | ";	

	if (lis.size())
	{
		std::cout << "\n\t\t\toperator--: ";
		for (typename T::const_reverse_iterator it = lis.rend(); it != --lis.rbegin(); it--)
			if (it != lis.rend())
				std::cout << *it << " | ";

		std::cout << "\n\t\t\t--operator: ";
		for (typename T::const_reverse_iterator it = lis.rend(); it != --lis.rbegin(); --it)
			if (it != lis.rend())
				std::cout << *it << " | ";
	}
}

template <typename T>
void	testFront(T& lis)
{
	printTestNumber(0);
	std::cout << "front: \n\t\t\t";
	
	if (lis.size()) // To prevent overflow
		std::cout << lis.front();
}

template <typename T>
void	testBack(T& lis)
{
	printTestNumber(0);
	std::cout << "back: \n\t\t\t";
	
	if (lis.size()) // To prevent overflow
		std::cout << lis.back();
}

template <typename T>
void	testPushBack(T& lis)
{
	printTestNumber(0);
	std::cout << "push_back: \n\t\t\t";
	
	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	T tmp = lis;
	tmp.push_back(*x);
	std::cout << "new elem = " << tmp.back();

	std::cout << "\n\t\t\tnew tmp: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testPopBack(T& lis)
{
	printTestNumber(0);
	std::cout << "pop_back: \n\t\t\t";
	
	if (lis.size())
	{
		T tmp = lis;
		tmp.pop_back();
		if (tmp.size()) // To prevent overflow
			std::cout << "new elem = " << tmp.back();

		std::cout << "\n\t\t\tnew tmp: ";
		for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
			std::cout << *it << " | ";
	}
}

template <typename T>
void	testSwap(T& lis)
{
	printTestNumber(0);
	std::cout << "swap member and non member: \n\t\t\t";

	T tmp(lis);
	T tmp2(lis);

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	tmp.push_back(*x);
	
	std::cout << "size of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size() << "\n";
	tmp2.swap(tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size() << "\n";

	swap(tmp2, tmp);
	std::cout << "\t\t\tsize of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size();

	delete x;
}

template <typename T>
void	testPushFront(T& lis)
{
	printTestNumber(0);
	std::cout << "push_front: \n\t\t\t";
	
	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	T tmp = lis;
	tmp.push_front(*x);
	std::cout << "new elem = " << tmp.front();

	std::cout << "\n\t\t\tnew tmp: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testPopFront(T& lis)
{
	printTestNumber(0);
	std::cout << "pop_front: \n\t\t\t";
	
	if (lis.size())
	{
		T tmp = lis;
		tmp.pop_front();
		if (tmp.size()) // To prevent overflow
			std::cout << "new elem = " << tmp.front();

		std::cout << "\n\t\t\tnew tmp: ";
		for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
			std::cout << *it << " | ";
	}
}

template <typename T>
void	testEmpty(T& lis)
{
	printTestNumber(0);
	std::cout << "empty: \n\t\t\t";
	
	std::cout << lis.empty();
}

template <typename T>
void	testClear(T& lis)
{
	printTestNumber(0);
	std::cout << "clear: \n\t\t\t";
	
	T tmp = lis;
	std::cout << "size before clear: " << tmp.size() << " | ";
	tmp.clear();
	std::cout << "\n\t\t\tsize after clear: " << tmp.size();

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	tmp.push_back(*x);
	
	std::cout << "\n\t\t\tnew tmp: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";

	delete x;
}

template <typename T>
void	testResize(T& lis)
{
	printTestNumber(0);
	std::cout << "resize: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	tmp.resize(3, *x);
	
	std::cout << "\n\t\t\tnew tmp: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp after resize = " << tmp.size();
	
	delete x;
}

template <typename T>
void	testReverse(T& lis)
{
	printTestNumber(0);
	std::cout << "reverse: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";
	
	std::cout << "\n\t\t\ttmp before: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";

	tmp.reverse();
	
	std::cout << "\n\t\t\tnew list: ";
	for (typename T::const_iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp after resize = " << tmp.size();
}

/**
*	Test assign with iterators' range.
*/
template <typename T>
void	testAssign1(T& lis)
{
	printTestNumber(0);
	std::cout << "assign1: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();

	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << tmp.back();

	T tmp2 = lis;
	tmp2.assign(tmp.begin(), tmp.end());
	std::cout << "\n\t\t\tsize after assign = " << tmp2.size() << " and content is:\n\t\t\t";

	for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
		std::cout << *it << " | ";

	delete x;
}

/**
*	Inserts n elements.
*/
template <typename T>
void	testAssign2(T& lis)
{
	printTestNumber(0);
	std::cout << "assign2: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
		*x = lis.front();
		
	tmp.resize(3, *x);
	std::cout << "\t\t\tnew elem = " << tmp.back();

	T tmp2 = lis;
	tmp2.assign(tmp.size(), tmp.front());
	std::cout << "\n\t\t\tsize after assign = " << tmp2.size() << " and content is:\n\t\t\t";

	for (typename T::iterator it = tmp2.begin(); it != tmp2.end(); ++it)
		std::cout << *it << " | ";
		
	delete x;
}

/**
*	Inserts one element.
*/
template <typename T>
void	testInsert1(T& lis)
{
	printTestNumber(0);
	std::cout << "insert1: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
	{
		*x = lis.front();
		std::cout << "\t\t\treturn value: " << *tmp.insert(++tmp.begin(), *x) << "\n";
	}
	std::cout << "\t\t\treturn value: " << *tmp.insert(tmp.begin(), *x) << "\n";
	std::cout << "\t\t\treturn value: " << *tmp.insert(tmp.end(), *x) << "\n";
	
	std::cout << "\t\t\tnew list: ";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();

	delete x;
}

template <typename T>
void	testInsert2(T& lis)
{
	printTestNumber(0);
	std::cout << "insert2: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	// Allows to value initialize (case size is 0, we can't assign lis.front())
	typename T::value_type* x = new typename T::value_type ();
	if (lis.size())
	{
		*x = lis.front();
		tmp.insert(++tmp.begin(), 5, *x);
	}
	tmp.insert(tmp.begin(), 5, *x);
	tmp.insert(tmp.end(), 5, *x);
	
	std::cout << "\t\t\tnew list: ";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();

	delete x;
}

/**
*	Inserts an iterators' range of elements.
*/
template <typename T>
void	testInsert3(T& lis)
{
	printTestNumber(0);
	std::cout << "insert3: \n\t\t\t";

	T tmp = lis;
	std::cout << "size of tmp = " << tmp.size() << "\n";

	tmp.insert(tmp.begin(), lis.begin(), lis.end());
	if (tmp.size())
		tmp.insert(++tmp.begin(), lis.begin(), lis.end());
	tmp.insert(tmp.end(), lis.begin(), lis.end());
	tmp.insert(tmp.end(), lis.begin(), lis.begin());
	
	std::cout << "\t\t\tnew list: ";
	for (typename T::iterator it = tmp.begin(); it != tmp.end(); ++it)
		std::cout << *it << " | ";
	std::cout << "\n\t\t\tsize of tmp = " << tmp.size();
}


template <typename T>
void	executeAllListTests(T& lis, int testNb)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING LIST " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
	std::cout << "\t\tLIST TYPE: ";
	print_type<typename T::value_type>();
	
	// Tests for non-const lists
	testSize(lis);
	testIterators(lis);
	testReverseIterators(lis);
	testFront(lis);
	testBack(lis);
	testPushBack(lis);
	testPopBack(lis);
	testSwap(lis);
	testEmpty(lis);
	testPushFront(lis);
	testPopFront(lis);
	testClear(lis);
	testResize(lis);
	testReverse(lis);
	testAssign1(lis);
	testAssign2(lis);
	testInsert1(lis);
	testInsert2(lis);
	testInsert3(lis);
}

template <typename T>
void	executeAllListTests(T& lis, int testNb, bool isConst)
{
	std::cout << "\n\n--------------------------------\n";
	std::cout << "------\tTESTING CONST LIST " << testNb << " ------\n";
	std::cout << "--------------------------------\n";
	
	std::cout << "\t\tLIST TYPE: ";
	print_type<typename T::value_type>();
	
	// Tests for const lists
	testSize(lis);
	testIterators(lis);
	testReverseIterators(lis);
	testFront(lis);
	testBack(lis);
	testEmpty(lis);

	(void)isConst;
}

#endif