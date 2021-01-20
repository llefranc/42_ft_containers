/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/20 17:31:33 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

namespace ft
{
	template <typename T>
	struct Node
	{
		T*		data;
		Node*	prev;
		Node*	next;
	};
	
	
	template <typename T, class Alloc = std::allocator<T> >
	class list
	{
		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef	ptrdiff_t									difference_type;
			typedef	size_t										size_type;

			typedef	T&											reference;
			typedef	const T&									const_reference;
			typedef	T*											pointer;
			typedef	const T*									const_pointer;
			
			// typedef typename ft::list_iterator<T, false>		iterator;
			// typedef typename ft::list_iterator<T, true>		const_iterator;

			// typedef typename ft::rev_list_iterator<T, false>	reverse_iterator;
			// typedef typename ft::rev_list_iterator<T, true>	const_reverse_iterator;

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			explicit list(const value_type& val, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _list(0)
			{
				_list = new Node<T>;
				_ptr = _alloc.allocate(1);
				_ptr = _alloc.construct(_ptr, val);
			}

		private:

			Alloc		_alloc;
			Node<T>*	_list;
			T*			_ptr;
	}; // class list
	
} // namespace ft

#endif