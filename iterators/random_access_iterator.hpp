/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/12 16:10:15 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "bidirectional_iterator.hpp"

namespace ft
{

	template<typename T, bool B, class Alloc = std::allocator<T> >
	class random_iterator : public ft::bidirec_iterator<T, B, Alloc>
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename ft::bidirec_iterator<T, B, Alloc>::difference_type difference_type;
			typedef typename ft::bidirec_iterator<T, B, Alloc>::value_type value_type;
			typedef typename ft::bidirec_iterator<T, B, Alloc>::size_type size_type;
			
			typedef typename ft::bidirec_iterator<T, B, Alloc>::reference reference;
			typedef typename ft::bidirec_iterator<T, B, Alloc>::pointer pointer;
			typedef typename ft::bidirec_iterator<T, B, Alloc>::nonConstPointer nonConstPointer;

			typedef typename ft::bidirec_iterator<T, B, Alloc> bidirec_iterator;
			

			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			random_iterator() : bidirec_iterator() {}
			random_iterator(pointer val) : bidirec_iterator(val) {}
			random_iterator(const random_iterator<T, false, Alloc>& copy) : bidirec_iterator(copy) {};
			~random_iterator() {}

			random_iterator& operator=(const random_iterator& assign)
			{
				if (this != &assign)
					bidirec_iterator::_val = assign._val;
				return (*this);
			}

			bool operator<(const random_iterator& it) const		{ return (it._val > this->_val); }
			bool operator>(const random_iterator& it) const		{ return (it._val < this->_val); }
			bool operator<=(const random_iterator& it) const	{ return (it._val >= this->_val); }
			bool operator>=(const random_iterator& it) const	{ return (it._val <= this->_val); }
			
			random_iterator& operator+=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					++this->_val;
				return (*this);
			}

			random_iterator operator+(size_type nb) const
			{
				random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					++it._val;
				return (it);
			}
			
			random_iterator& operator-=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					--this->_val;
				return (*this);
			}

			random_iterator operator-(size_type nb) const
			{
				random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					--it._val;
				return (it);
			}

			reference operator[](size_type nb) const
			{
				value_type* tmp;

				tmp = this->_val;
				for (size_type i = 0; i < nb; i++)
					++tmp;
				return (*tmp);
			}

			difference_type operator-(random_iterator it) const
			{
				return (this->_val - it._val);
			}
			

			/* -------- FRIEND OPERATORS -------- */		
			
			friend random_iterator operator+(size_type nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt += nb);
			}

			friend random_iterator operator-(size_type nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt -= nb);
			}
	};

} // namespace ft

#endif