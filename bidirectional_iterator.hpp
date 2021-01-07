/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/07 16:54:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include <iterator>
#include <memory>

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class bidirec_iterator
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::size_type size_type;
			typedef std::bidirectional_iterator_tag iterator_category;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			bidirec_iterator() : _val() {}
			bidirec_iterator(pointer val) : _val(val) {}
			bidirec_iterator(const bidirec_iterator& copy) : _val(copy._val) {};
			~bidirec_iterator() {}

			bidirec_iterator& operator=(const bidirec_iterator& assign)
			{
				if (this != &assign)
					_val = assign._val;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*()			{ return (*_val); }
			pointer operator->() const		{ return (_val); }
			

			bidirec_iterator& operator++()		{ ++_val; return (*this); }
			bidirec_iterator operator++(int)		{ bidirec_iterator res(*this); ++(*this); return (res); };
			bidirec_iterator& operator--()		{ --_val; return (*this); }
			bidirec_iterator operator--(int)		{ bidirec_iterator res(*this); --(*this); return (res); };
			
			bool operator==(const bidirec_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const bidirec_iterator& it) const	{ return (it._val != _val); }

			protected:

				value_type*	_val;
	};
}

#endif