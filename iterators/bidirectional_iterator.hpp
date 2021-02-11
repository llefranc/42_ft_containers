/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/11 11:03:16 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include "../templates/type1_or_type2.hpp"

namespace ft
{
	template<typename T, bool B>
	class rev_bidirec_iterator;
	
	template<typename T, bool B>
	class bidirec_iterator
	{
		public:

			/* -------- ALIASES -------- */

			typedef long int										difference_type;
			typedef T												value_type;
			typedef size_t											size_type;
			
			typedef typename chooseConst<B, T&, const T&>::type		reference;
			typedef typename chooseConst<B, T*, const T*>::type		pointer;
			typedef T*												nonConstPointer;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			bidirec_iterator(nonConstPointer val = 0) : _val(val) {}

			// A COMMENTER
			bidirec_iterator(const bidirec_iterator<T, false>& copy) { _val = copy.getNonConstPointer(); }
			bidirec_iterator(const rev_bidirec_iterator<T, false>& copy) { _val = copy.getNonConstPointer(); }
			~bidirec_iterator() {}

			nonConstPointer	getNonConstPointer() const		{ return _val; }

			bidirec_iterator& operator=(const bidirec_iterator& assign)
			{
				if (this != &assign)
					_val = assign._val;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*() const			{ return (*_val); }
			pointer operator->() const		{ return (_val); }

			bidirec_iterator& operator++()		{ ++_val; return (*this); }
			bidirec_iterator operator++(int)		{ bidirec_iterator res(*this); ++(*this); return (res); };
			bidirec_iterator& operator--()		{ --_val; return (*this); }
			bidirec_iterator operator--(int)		{ bidirec_iterator res(*this); --(*this); return (res); };
			
			bool operator==(const bidirec_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const bidirec_iterator& it) const	{ return (it._val != _val); }

			protected:

				nonConstPointer	_val;
	};
}

#endif