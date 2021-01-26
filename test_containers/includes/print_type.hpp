/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:32:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 14:02:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TYPE
#define PRINT_TYPE

#include <iostream>
#include <string>

#include "Bob_test.hpp"

class Bob;

/**
*	Prints the type of the template parameter.
*/
template <typename T>
inline void print_type() {} // Inline keywork to avoid duplicate symbol error

template <>
inline void print_type<int>() { std::cout << "int\n"; }

template <>
inline void print_type<char>() { std::cout << "char\n"; }

template <>
inline void print_type<Bob>() { std::cout << "Class test\n"; }

template <>
inline void print_type<double*>() { std::cout << "double*\n"; }

template <>
inline void print_type<std::string>() { std::cout << "std::string\n"; }

#endif