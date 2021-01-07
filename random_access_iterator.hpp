/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/07 16:54:01 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "bidirectional_iterator.hpp"

namespace ft
{

	template<typename T, class Alloc = std::allocator<T> >
	class random_iterator : public ft::bidirec_iterator<T, Alloc>
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename ft::bidirec_iterator<T, Alloc>::difference_type difference_type;
			typedef typename ft::bidirec_iterator<T, Alloc>::value_type value_type;
			typedef typename ft::bidirec_iterator<T, Alloc>::reference reference;
			typedef typename ft::bidirec_iterator<T, Alloc>::pointer pointer;
			typedef typename ft::bidirec_iterator<T, Alloc>::size_type size_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename ft::bidirec_iterator<T, Alloc> bidirec_iterator;

			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			random_iterator() : bidirec_iterator() {}
			random_iterator(pointer val) : bidirec_iterator(val) {}
			random_iterator(const random_iterator& copy) : bidirec_iterator(copy) {};
			~random_iterator() {}

			random_iterator& operator=(const random_iterator& assign)
			{
				using bidirec_iterator::operator=;

				this = assign;
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