/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_random_access_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 17:10:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_RANDOM_ACCESS_ITERATOR_HPP
#define REV_RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "rev_bidirectional_iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	template<typename T, bool B>
	class rev_random_iterator : public rev_bidirec_iterator<T, B>
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename ft::rev_bidirec_iterator<T, B>::difference_type	difference_type;
			typedef typename ft::rev_bidirec_iterator<T, B>::value_type		value_type;
			typedef typename ft::rev_bidirec_iterator<T, B>::size_type		size_type;
			
			typedef typename ft::rev_bidirec_iterator<T, B>::reference		reference;
			typedef typename ft::rev_bidirec_iterator<T, B>::pointer			pointer;
			typedef typename ft::rev_bidirec_iterator<T, B>::nonConstPointer nonConstPointer;

			typedef typename ft::rev_bidirec_iterator<T, B>					rev_bidirec_iterator;
			

			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			rev_random_iterator(nonConstPointer val = 0) : rev_bidirec_iterator(val) {}
			rev_random_iterator(const rev_random_iterator<T, false>& copy) : rev_bidirec_iterator(copy.getNonCoinstPointer()) {};
			rev_random_iterator(const random_iterator<T, false>& copy) : rev_bidirec_iterator(copy.getNonCoinstPointer()) {};
			~rev_random_iterator() {}

			rev_random_iterator& operator=(const rev_random_iterator& assign)
			{
				if (this != &assign)
					rev_bidirec_iterator::_val = assign._val;
				return (*this);
			}

			bool operator<(const rev_random_iterator& it) const		{ return (it._val > this->_val); }
			bool operator>(const rev_random_iterator& it) const		{ return (it._val < this->_val); }
			bool operator<=(const rev_random_iterator& it) const	{ return (it._val >= this->_val); }
			bool operator>=(const rev_random_iterator& it) const	{ return (it._val <= this->_val); }
			
			rev_random_iterator& operator+=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					++this->_val;
				return (*this);
			}

			rev_random_iterator operator+(size_type nb) const
			{
				rev_random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					++it._val;
				return (it);
			}
			
			rev_random_iterator& operator-=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					--this->_val;
				return (*this);
			}

			rev_random_iterator operator-(size_type nb) const
			{
				rev_random_iterator it(*this);
				
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

			difference_type operator-(rev_random_iterator it) const
			{
				return (this->_val - it._val);
			}
			

			/* -------- FRIEND OPERATORS -------- */		
			
			friend rev_random_iterator operator+(size_type nb, const rev_random_iterator& it)
			{
				rev_random_iterator newIt(it);
				return (newIt += nb);
			}

			friend rev_random_iterator operator-(size_type nb, const rev_random_iterator& it)
			{
				rev_random_iterator newIt(it);
				return (newIt -= nb);
			}
	};

} // namespace ft

#endif