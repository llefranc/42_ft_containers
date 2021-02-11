/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_list_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/11 11:03:03 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_LIST_ITERATOR_HPP
#define REVERSE_LIST_ITERATOR_HPP

#include "../templates/type1_or_type2.hpp"
#include "list_iterator.hpp"

namespace ft
{
	template<typename T, typename Node, bool B>
	class rev_list_iterator
	{
		public:

			/* -------- ALIASES -------- */
			
			typedef long int										difference_type;
			typedef T												value_type;
			typedef size_t											size_type;
			
			typedef typename chooseConst<B, T&, const T&>::type		reference;
			typedef typename chooseConst<B, T*, const T*>::type		pointer;
			typedef Node*											nonConstPointer;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			rev_list_iterator(nonConstPointer node = 0) : _node(node) {}
			rev_list_iterator(const rev_list_iterator<T, Node, false>& copy) { _node = copy.getNonConstPointer(); }
			rev_list_iterator(const list_iterator<T, Node, false>& copy) { _node = copy.getNonConstPointer()->prev; }
			~rev_list_iterator() {}

			nonConstPointer	getNonConstPointer() const		{ return _node; }

			rev_list_iterator& operator=(const rev_list_iterator& assign)
			{
				if (this != &assign)
					_node = assign._node;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*() const			{ return (_node->content); }
			nonConstPointer operator->() const		{ return (_node); }

			rev_list_iterator& operator++()		{ _node = _node->prev; return (*this); }
			rev_list_iterator operator++(int)		{ rev_list_iterator res(*this); ++(*this); return (res); };
			rev_list_iterator& operator--()		{ _node = _node->next; return (*this); }
			rev_list_iterator operator--(int)		{ rev_list_iterator res(*this); --(*this); return (res); };
			
			bool operator==(const rev_list_iterator& it) const	{ return (it._node == _node); }
			bool operator!=(const rev_list_iterator& it) const	{ return (it._node != _node); }

			protected:

				nonConstPointer	_node;
	};
}

#endif