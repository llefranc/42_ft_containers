/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:32:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/16 12:36:58 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TYPE
#define PRINT_TYPE

#include <iostream>
#include <string>

#include "Bob_test.hpp"

template <typename T>
void print_type() {}

template <>
void print_type<int>() { std::cout << "int\n"; }

template <>
void print_type<char>() { std::cout << "char\n"; }

template <>
void print_type<Bob>() { std::cout << "Class test\n"; }

template <>
void print_type<double*>() { std::cout << "double*\n"; }

template <>
void print_type<std::string>() { std::cout << "std::string\n"; }

#endif