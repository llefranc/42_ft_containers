/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:27 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 16:56:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST1
#define TEST1

#include <memory>

#include "test2.hpp"

namespace ft
{
	// template<typename T, bool B, class Alloc = std::allocator<T> >
	// template<typename T, bool B>
	// class random_iterator;

	template<typename T, bool B>
	class rev_random_iterator
	{
		rev_random_iterator(random_iterator<T,B>&) {};
	};
}

#endif