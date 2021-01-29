/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_bidirectional_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/29 16:20:38 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECTIONNAL_ITERATOR_HPP
#define REVERSE_BIDIRECTIONNAL_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "../templates/type1_or_type2.hpp"
#include "bidirectional_iterator.hpp"

namespace ft
{
	template<typename T, bool B>
	class rev_bidirec_iterator
	{
		public:

			/* -------- ALIASES -------- */
			
			typedef ptrdiff_t		difference_type;
			typedef T			value_type;
			typedef size_t			size_type;
			
			typedef typename chooseConst<B, T&, const T&>::type	reference;
			typedef typename chooseConst<B, T*, const T*>::type		pointer;
			typedef T*	nonConstPointer;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			rev_bidirec_iterator(nonConstPointer val = 0) : _val(val) {}
			rev_bidirec_iterator(const rev_bidirec_iterator<T, false>& copy) { _val = copy.getNonConstPointer(); }
			rev_bidirec_iterator(const ft::bidirec_iterator<T, false>& copy) { _val = copy.getNonConstPointer(); }
			~rev_bidirec_iterator() {}

			nonConstPointer	getNonConstPointer() const		{ return _val; }

			rev_bidirec_iterator& operator=(const rev_bidirec_iterator& assign)
			{
				if (this != &assign)
					_val = assign._val;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*()			{ return (*_val); }
			pointer operator->() const		{ return (_val); }

			rev_bidirec_iterator& operator++()		{ --_val; return (*this); }
			rev_bidirec_iterator operator++(int)		{ rev_bidirec_iterator res(*this); ++(*this); return (res); };
			rev_bidirec_iterator& operator--()		{ ++_val; return (*this); }
			rev_bidirec_iterator operator--(int)		{ rev_bidirec_iterator res(*this); --(*this); return (res); };
			
			bool operator==(const rev_bidirec_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const rev_bidirec_iterator& it) const	{ return (it._val != _val); }

			protected:

				nonConstPointer	_val;
	};
}

#endif