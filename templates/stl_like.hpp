/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_like.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/12 17:03:45 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_LIKE_HPP
#define STL_LIKE_HPP

#include "../iterators/random_access_iterator.hpp"

namespace ft
{
	/* ----------------------------- STD::PAIR ----------------------------- */
	
	template <typename T1, typename T2>
	class pair
	{
		public:

			pair() : first(), second() {};
			pair(const T1& a, const T2& b) : first(a), second(b) {};
			pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {};
			~pair() {};
		
			pair& operator=(const pair<T1, T2>& assign)
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return (*this);
			}

			T1 first;
			T2 second;
	};


	/* --------------------------- STD::ENABLE_IF -------------------------- */

	template <typename T>
	struct enable_if {};

	template <typename T>
	struct enable_if<ft::random_iterator<T, true> > { typedef int type; };
	
	template <typename T>
	struct enable_if<ft::random_iterator<T, false> > { typedef int type; };

	/* ----------------------------- IS_ITERATOR ---------------------------- */
	// template <typename T>
	// struct is_int
	// {
	// 	char	take_type(int& x);
	// 	double	take_type(...);

	// 	T		type;
	// 	// bool	value = (sizeof(char) == sizeof(take_type(type)));
	// 	bool	value;
	// };

	// template <>
	// struct is_int<T> { value = (sizeof(char) == sizeof(take_type(type))); }

	// template <typename T>
	// struct is_int { typedef 0 value; };
	
	// template <>
	// struct is_int<int> { typedef 1 value; };
} // namespace ft

#endif