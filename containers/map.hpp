/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/04 10:51:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

#include "../templates/stl_like.hpp"

namespace ft
{
	
	template < class Key,                                  		 	// map::key_type
			class T,                           	       			    // map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >   // map::allocator_type
	> class map
	{
		public:

			typedef Key												key_type
			typedef Compare											key_compare;
			typedef	Alloc											allocator_type;
			typedef	T												mapped_type;
			
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef	long int										difference_type;
			typedef	size_t											size_type;

			typedef	T&												reference;
			typedef	const T&										const_reference;
			typedef	T*												pointer;
			typedef	const T*										const_pointer;
			
			// typedef typename ft::map_iterator<T, Node, false>		iterator;
			// typedef typename ft::map_iterator<T, Node, true>		const_iterator;

			// typedef typename ft::rev_map_iterator<T, Node, false>	reverse_iterator;
			// typedef typename ft::rev_map_iterator<T, Node, true>	const_reverse_iterator;

	};
} // namespace ft


#endif