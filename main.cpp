/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:24:20 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/12 18:11:45 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include "templates/stl_like.hpp"

#include <iostream>

#include <vector>

int main()
{
	/* ------------------------ VECTORS TEST ------------------------ */
	
	// int* ptr1 = new int[5]();
	// int* ptr2 = new int[5]();
	// std::vector<int> vectest1(ptr1, ptr2);

	// for (std::vector<int>::iterator it = vectest1.begin(); it != vectest1.end(); it++)
	// 	std::cout << *it << " ";

	// std::vector<int*> vectest;

	// vectest.push_back(new int[5]);
	// vectest[0][2] = 5;

	// std::cout << vectest[0][2] << std::endl;

	// std::vector<int> vvv(5, 0);
	// _size < 2^capacity ?
	
	// for (int i = 0; i < 50; i++)
	// {
	// 	std::cout << "vvv capa: " << vvv.capacity() << "\n";
	// 	vvv.push_back(1);
	// }

	int nbb = 5;
	ft::enable_if<ft::random_iterator<int, true> >::type* ptr = &nbb;

	*ptr =3;
	std::cout << *ptr << "\n";
	ft::vector<int> vec(5, 100);

	// int *ptr1 = new int [5];
	// int *ptr2 = ptr1 + 1;
	// std::vector<int> tt2(ptr1, ptr2);
	// for (std::vector<int>::iterator it = tt2.begin(); it != tt2.end(); it++)
	// 	std::cout << *it << " ";
	// std::cout << "\n";


	ft::vector<int> tt(vec.begin(), vec.end());

	for (ft::vector<int>::iterator it = tt.begin(); it != tt.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";

	/* ------------------------ VECTOR ITERATORS TEST ------------------------ */
	
	// // std::cout << ft::is_int<char>


	// ft::vector<int>::iterator it = vec.begin();
	// ft::vector<int>::iterator it2 = vec.begin();
	// ft::vector<int>::iterator it3 = it2;
	// ft::vector<int>::iterator it4;

	// ft::vector<int>::const_iterator it5 = vec.begin();
	// ft::vector<int>::const_iterator it6;
	// it6 = it5;
	// ft::vector<int>::const_iterator it7 = it5;
	// ft::vector<int>::const_iterator it8 = it3;


	// // const iterator can't be transformed into iterators
	// // ft::vector<int>::iterator it9 = it5;

	// ///////////////////////////////////////////////////////////////////
	// // std::vector<int> vec(5, 100);

	// // std::vector<int>::iterator it = vec.begin();
	// // std::vector<int>::iterator it2 = vec.begin();
	// // std::vector<int>::iterator it3 = it2;
	// // std::vector<int>::iterator it4;


	// // std::vector<int>::const_iterator it5 = vec.begin();
	// // std::vector<int>::const_iterator it6;
	// // it6 = it5;
	// // std::vector<int>::const_iterator it7 = it5;
	// // std::vector<int>::const_iterator it8 = it3;

	// // const iterator can't be transformed into iterators
	// // std::vector<int>::iterator it9 = it5;
	

	// std::cout << "const it = " << *it5 << "\n";

	// for (; it5 != vec.end(); ++it5)
	// 	std::cout << *it5 << " | ";
	// std::cout << std::endl;

	// for (; it7 != vec.end(); ++it7)
	// 	std::cout << *it7 << " | ";
	// std::cout << std::endl;

	// for (; it8 != vec.end(); ++it8)
	// 	std::cout << *it8 << " | ";
	// std::cout << std::endl;

	// // const cannot be assigned
	// // *it7 = 3;


	// it4 = it2;
	// *it = 6;
	// std::cout << "it = " << *it << "\n";
	// *it = 5;
	// std::cout << "it = " << *it << "\n";
	// std::cout << "it = " << *it2 << "\n";
	// std::cout << "it = " << *it3 << "\n";
	// std::cout << "it = " << *it4 << "\n";

	// if (it4 == it2)
	// 	std::cout << "same address (it4 == it2)\n";
	// if (it3 != it2)
	// 	std::cout << "not same address (it3 != it2)\n";
	// else
	// {
	// 	std::cout << "same address (it3 == it2)\n";
	// }

	// ++it4;
	// *it3 = 3;
	// std::cout << "*it4 = " << *it4 << " et *it3 = " << *it3 << "\n";

	// if (it4 > it3)
	// 	std::cout << "sup >\n";
	// else
	// {
	// 	std::cout << "inf >\n";
	// }

	// if (it4 < it3)
	// 	std::cout << "sup <\n";
	// else
	// {
	// 	std::cout << "inf <\n";
	// }

	// if (it4 >= it3)
	// 	std::cout << "sup >=\n";
	// else
	// {
	// 	std::cout << "inf >=\n";
	// }

	// if (it4 <= it3)
	// 	std::cout << "sup <=\n";
	// else
	// {
	// 	std::cout << "inf >=\n";
	// }

	// if (it2 >= it3)
	// 	std::cout << "sup >=\n";
	// else
	// {
	// 	std::cout << "inf >=\n";
	// }

	// if (it2 <= it3)
	// 	std::cout << "sup <=\n";
	// else
	// {
	// 	std::cout << "inf <=\n";
	// }

	// *it2 = 100;
	// std::cout << "opeartor++ = " << *it2++ << "\n";
	// *it3 = 200;
	// std::cout << "opeartor++ = " << *it3 << "\n";
	// std::cout << "opeartor++ = " << *++it3 << "\n";

	// std::cout << "opeartor++ = " << *it2-- << "\n";
	// std::cout << "opeartor++ = " << *it3 << "\n";
	// std::cout << "opeartor-- = " << *--it3 << "\n";

	// std::cout << "vecsize = " << vec.size() << "\n";
	// for (unsigned long i = 0; i < vec.size(); i++)
	// {
	// 	std::cout << *it2 << " | ";
	// 	it2++;
	// }
	// std::cout << std::endl;
	// it2 = vec.begin();

	// for (unsigned long i = 0; i < vec.size(); i++)
	// 	*it2++ = i;
	// std::cout << std::endl;
	// it2 = vec.begin();

	// it2 = vec.begin();
	// for (unsigned long i = 0; i < vec.size(); i++)
	// 	std::cout << *it2++ << " | ";
	// std::cout << std::endl;

	// ft::vector<int> vec2;
	// it2 = vec.begin();
	// it2 += 2;
	// std::cout << "it2 = " << *it2 << "\n";
	// std::cout << "it2 = " << *(it2 + 2) << "\n";

	// it2 -= 1;
	// std::cout << "it2 = " << *it2 << "\n";
	// it2 += 3;
	// std::cout << "it2 = " << *(it2 - 2) << "\n";

	// it2 = vec.begin();
	// std::cout << "it2[4] = " << it2[4] << "\n";
	// it3 = it2;
	// it3 += 4;
	// std::cout << "myvector has " << (it3-it2) << " elements.\n";

	// it3 = vec.begin() + 1;
	// std::cout << "it3 = " << *it3 << "\n";

	// it4 = it3 - 1;
	// std::cout << "it4 = " << *it4 << "\n";

	return (0);
}