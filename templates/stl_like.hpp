/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_like.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/12 15:15:33 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_LIKE_HPP
#define STL_LIKE_HPP

#include "../iterators/random_access_iterator.hpp"

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------- FT::PAIR -------------------------- *
	*
	* Coplien form:
	* (constructor):		Construct pair
	* (destructor):			Pair destructor
	* operator=:			Assign content
	*
	* Public member variables:
	* T1:					First pair's member variable.
	* T2:					Second pair's member variable.
	* ------------------------------------------------------------- *
	*/

	template <typename T1, typename T2>
	class pair
	{
		public:
			
			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */
			
			/**
			*	Default constructor, value initialized first and second.
			*/
			pair() : first(), second() {};
			
			/**
			*	Initialization constructor.
			*
			*	@param a	Will initialize first.
			*	@param b	Will initialize second.
			*/
			pair(const T1& a, const T2& b) : first(a), second(b) {};
			
			/**
			*	Copy constructor, creates a pair with the same member variables.
			*
			*	@param copy		The pair that will be copied.
			*/
			// pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {};
			
			/**
			*	Copy constructor, creates a pair with the same member variables.
			*
			*	@param copy		The pair that will be copied.
			*/
			template <typename U, typename V>
			pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

			~pair() {};
		
			/**
			*	Assigns a pair to this pair.
			*	
			*	@param assign	The pair that will be assigned.
			*/
			pair& operator=(const pair& assign)
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return (*this);
			}


			/* ------------------------------------------------------------- */
			/* ------------------ PUBLIC MEMBER VARIABLES ------------------ */
			
			T1 first;
			T2 second;
	};


	/* --------------------------- STD::ENABLE_IF -------------------------- */

	/**
	*	Typedef an int into type only if B is true.
	*/

	template <bool B>
	struct enable_if {};

	template <>
	struct enable_if<true> { typedef int type; };
	
	
	/* --------------------------- STD::IS_INTEGRAL -------------------------- */

	/**
	*	Value will be true if T is an integral, false otherwise.
	*/
	template <typename T>
	struct is_integral { static const bool value = false; };

	template <>
	struct is_integral<bool> { static const bool value = true; };
	
	template <>
	struct is_integral<char> { static const bool value = true; };

	template <>
	struct is_integral<short> { static const bool value = true; };

	template <>
	struct is_integral<int> { static const bool value = true; };

	template <>
	struct is_integral<long> { static const bool value = true; };

	template <>
	struct is_integral<long long> { static const bool value = true; };

	template <>
	struct is_integral<unsigned char> { static const bool value = true; };

	template <>
	struct is_integral<unsigned short> { static const bool value = true; };

	template <>
	struct is_integral<unsigned int> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long> { static const bool value = true; };

	template <>
	struct is_integral<unsigned long long> { static const bool value = true; };

} // namespace ft

#endif