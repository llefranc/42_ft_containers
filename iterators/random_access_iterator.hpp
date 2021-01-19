/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 17:21:13 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "bidirectional_iterator.hpp"

namespace ft
{
	template<typename T, bool B>
	class rev_random_iterator;
	
	template<typename T, bool B>
	class random_iterator : public bidirec_iterator<T, B>
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename ft::bidirec_iterator<T, B>::difference_type difference_type;
			typedef typename ft::bidirec_iterator<T, B>::value_type value_type;
			typedef typename ft::bidirec_iterator<T, B>::size_type size_type;
			
			typedef typename ft::bidirec_iterator<T, B>::reference reference;
			typedef typename ft::bidirec_iterator<T, B>::pointer pointer;
			typedef typename ft::bidirec_iterator<T, B>::nonConstPointer nonConstPointer;

			typedef typename ft::bidirec_iterator<T, B> bidirec_iterator;
			

			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			random_iterator(nonConstPointer val = 0) : bidirec_iterator(val) {}
			random_iterator(const random_iterator<T, false>& copy) : bidirec_iterator(copy.getNonCoinstPointer()) {};
			random_iterator(const rev_random_iterator<T, false>& copy) : bidirec_iterator(copy.getNonCoinstPointer()) {};
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