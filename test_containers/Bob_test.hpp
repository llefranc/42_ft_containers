/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bob_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:43:13 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/18 14:33:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOB_TEST_HPP
#define BOB_TEST_HPP

#include <iostream>

class Bob
{
	public:
	Bob() {}
	Bob(const Bob& copy) { (void)copy; }
	~Bob() {}
	Bob& operator=(const Bob& assign) { (void)assign; return *this; }
	// Bob() { std::cout << "Class test constructed\n"; }
	// Bob(const Bob& copy) { (void)copy; std::cout << "Class test copied\n"; }
	// ~Bob() { std::cout << "Class test destructed\n"; }
	// Bob& operator=(const Bob& assign) { (void)assign; std::cout << "Class test assigned\n"; return *this; }
};

std::ostream& operator<<(std::ostream& flux, const Bob& print)
{
	(void)print;
	flux << "Class test printing";
	return (flux);
}

#endif