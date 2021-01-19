/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:27 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 16:57:01 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST2
#define TEST2

#include <memory>

namespace ft
{
	template<typename T, bool B, class Alloc = std>
	class rev_random_iterator;
	
	template<typename T, bool B>
	class random_iterator
	{

		random_iterator(rev_random_iterator<T,B>&) {};
	};
}

#endif