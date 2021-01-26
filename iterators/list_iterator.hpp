/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 17:29:16 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "../templates/type1_or_type2.hpp"

namespace ft
{

	template<typename T, typename Node, bool B>
	class rev_list_iterator;
	
	template<typename T, typename Node, bool B>
	class list_iterator
	{
		public:

			/* -------- ALIASES -------- */

			typedef ptrdiff_t		difference_type;
			typedef T				value_type;
			typedef size_t			size_type;
			
			typedef typename chooseConst<B, T&, const T&>::type		reference;
			typedef typename chooseConst<B, T*, const T*>::type		pointer;
			typedef Node*											nonConstPointer;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			list_iterator(nonConstPointer node = 0) : _node(node) {}
			list_iterator(const list_iterator<T, Node, false>& copy) { _node = copy.getNonCoinstPointer(); }
			~list_iterator() {}

			nonConstPointer	getNonCoinstPointer() const		{ return _node; }

			list_iterator& operator=(const list_iterator& assign)
			{
				if (this != &assign)
					_node = assign._node;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*()			{ return (_node->content); }
			nonConstPointer operator->() const		{ return (_node); }

			list_iterator& operator++()			{ _node = _node->next; return (*this); }
			list_iterator operator++(int)		{ list_iterator res(*this); ++(*this); return (res); };
			list_iterator& operator--()			{ _node = _node->prev; return (*this); }
			list_iterator operator--(int)		{ list_iterator res(*this); --(*this); return (res); };
			
			bool operator==(const list_iterator& it) const	{ return (it._node == _node); }
			bool operator!=(const list_iterator& it) const	{ return (it._node != _node); }

			protected:

				nonConstPointer	_node;
	};
}

#endif