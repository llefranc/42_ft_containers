/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_random_access_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/20 16:38:50 by llefranc         ###   ########.fr       */
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
	/**
	* ------------------------------------------------------------- *
	* ------------------ FT::REV_RANDOM_ITERATOR ------------------ *
	*
	* - Coplien form:
	* (constructor):		Construct rev_random_iterator
	* (destructor):			Rev_random_iterator destructor
	* operator=:			Assign content
	*
	* - Operators
	* operators:			Operators for rev_random_iterator
	* non-member operators:	Operators for rev_random_iterator
	* ------------------------------------------------------------- *
	*/
	
	/**
	*	@param T	Type of container's elements.
	*	@param B	Boolean to indicate if it's a const or not random iterator.
	*/
	template<typename T, bool B>
	class rev_random_iterator : public rev_bidirec_iterator<T, B>
	{
		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef typename ft::rev_bidirec_iterator<T, B>::difference_type	difference_type;
			typedef typename ft::rev_bidirec_iterator<T, B>::value_type			value_type;
			typedef typename ft::rev_bidirec_iterator<T, B>::size_type			size_type;
			
			typedef typename ft::rev_bidirec_iterator<T, B>::reference			reference;
			typedef typename ft::rev_bidirec_iterator<T, B>::pointer			pointer;
			typedef typename ft::rev_bidirec_iterator<T, B>::nonConstPointer	nonConstPointer;

			typedef typename ft::rev_bidirec_iterator<T, B>						rev_bidirec_iterator;
			

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			/**
			*	Default constructor, creates a rev_random_iterator pointing to val.
			*
			*	@param val	A pointer to a T element. Value initialized if not provided.
			*/
			rev_random_iterator(nonConstPointer val = 0) :
					rev_bidirec_iterator(val) {}

			/**
			*	Copy constructor : creates a const rev_random_iterator pointing to the same T element.
			*	Convert constructor : creates a rev_random_iterator from a const rev_random_iterator,
			*	pointing to the same T element.
			*	
			*	@param copy		The rev_random_iterator that will be copied.
			*/
			rev_random_iterator(const rev_random_iterator<T, false>& copy) :
				rev_bidirec_iterator(copy.getNonCoinstPointer()) {};

			/**
			*	Convert constructor : creates a rev_random_iterator from a const / not const 
			*	random_iterator, pointing to the same T element.
			*	
			*	@param copy		The random_iterator that will be converted.
			*/
			rev_random_iterator(const random_iterator<T, false>& copy) :
				rev_bidirec_iterator(copy.getNonCoinstPointer()) {};

			~rev_random_iterator() {}

			/**
			*	Assign a rev_random_iterator to this rev_random_iterator. Both iterators will point to the
			*	same T element.
			*	
			*	@param x		The rev_random_iterator that will be assigned.
			*/
			rev_random_iterator& operator=(const rev_random_iterator& assign)
			{
				if (this != &assign)
					rev_bidirec_iterator::_val = assign._val;
				return (*this);
			}


			/* ------------------------------------------------------------- */
			/* --------------------- OPERATOR OVERLOADS -------------------- */

			bool operator<(const rev_random_iterator& it) const		{ return (it._val > this->_val); }
			
			bool operator>(const rev_random_iterator& it) const		{ return (it._val < this->_val); }
			
			bool operator<=(const rev_random_iterator& it) const	{ return (it._val >= this->_val); }

			bool operator>=(const rev_random_iterator& it) const	{ return (it._val <= this->_val); }
			
			
			/**
			*	Increment 1 time random_iterator position.
			*/
			rev_random_iterator& operator+=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					--this->_val;
				return (*this);
			}

			/**
			*	Increment nb times random_iterator position.
			*/
			rev_random_iterator operator+(size_type nb) const
			{
				rev_random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					--it._val;
				return (it);
			}
			
			/**
			*	Decrement 1 time random_iterator position.
			*/
			rev_random_iterator& operator-=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					++this->_val;
				return (*this);
			}

			/**
			*	Decrement nb times random_iterator position.
			*/
			rev_random_iterator operator-(size_type nb) const
			{
				rev_random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					++it._val;
				return (it);
			}

			/**
			*	@return		A reference to rev_random_iterator + nb. Undefined behavior if the 
			*				reference returned is out of container's range.
			*/
			reference operator[](size_type nb) const
			{
				value_type* tmp;

				tmp = this->_val;
				for (size_type i = 0; i < nb; i++)
					--tmp;
				return (*tmp);
			}

			/**
			*	@return		The range's lenght between this rev_random_iterator and another one.
			*/
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