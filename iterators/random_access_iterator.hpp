/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/21 16:42:30 by llefranc         ###   ########.fr       */
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
	
	
	/**
	* ------------------------------------------------------------- *
	* -------------------- FT::RANDOM_ITERATOR -------------------- *
	*
	* - Coplien form:
	* (constructor):		Construct random_iterator
	* (destructor):			Random_iterator destructor
	* operator=:			Assign content
	*
	* - Operators
	* operators:			Operators for random_iterator
	* non-member operators:	Operators for random_iterator
	* ------------------------------------------------------------- *
	*/

	/**
	*	@param T	Type of container's elements.
	*	@param B	Boolean to indicate if it's a const or not random iterator.
	*/
	template<typename T, bool B>
	class random_iterator : public bidirec_iterator<T, B>
	{
		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef typename ft::bidirec_iterator<T, B>::difference_type	difference_type;
			typedef typename ft::bidirec_iterator<T, B>::value_type			value_type;
			typedef typename ft::bidirec_iterator<T, B>::size_type			size_type;
			
			typedef typename ft::bidirec_iterator<T, B>::reference			reference;
			typedef typename ft::bidirec_iterator<T, B>::pointer			pointer;
			typedef typename ft::bidirec_iterator<T, B>::nonConstPointer	nonConstPointer;

			typedef typename ft::bidirec_iterator<T, B>						bidirec_iterator;
			

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			/**
			*	Default constructor, creates a random_iterator pointing to val.
			*
			*	@param val	A pointer to a T element. Value initialized if not provided.
			*/
			random_iterator(nonConstPointer val = 0) :
					bidirec_iterator(val) {}
					
			/**
			*	Copy constructor : creates a const random_iterator pointing to the same T element.
			*	Convert constructor : creates a random_iterator from a const random_iterator,
			*	pointing to the same T element.
			*	
			*	@param copy		The iterator that will be copied.
			*/
			random_iterator(const random_iterator<T, false>& copy) :
					bidirec_iterator(copy.getNonCoinstPointer()) {};

			~random_iterator() {}

			/**
			*	Assign a random_iterator to this random_iterator. Both iterators will point to the
			*	same T element.
			*	
			*	@param x		The random_iterator that will be assigned.
			*/
			random_iterator& operator=(const random_iterator& assign)
			{
				if (this != &assign)
					bidirec_iterator::_val = assign._val;
				return (*this);
			}


			/* ------------------------------------------------------------- */
			/* --------------------- OPERATOR OVERLOADS -------------------- */


			bool operator<(const random_iterator& it) const		{ return (it._val > this->_val); }
			
			bool operator>(const random_iterator& it) const		{ return (it._val < this->_val); }
			
			bool operator<=(const random_iterator& it) const	{ return (it._val >= this->_val); }

			bool operator>=(const random_iterator& it) const	{ return (it._val <= this->_val); }
			
			/**
			*	Increment 1 time random_iterator position.
			*/
			random_iterator& operator+=(int nb)
			{
				if (nb > 0)
					for (int i = 0; i < nb; ++i)
						++this->_val;
				else
					for (int i = 0; i > nb; --i)
						--this->_val;

				return (*this);
			}

			/**
			*	Increment nb times random_iterator position.
			*/
			random_iterator operator+(int nb) const
			{
				random_iterator it(*this);
				
				if (nb > 0)
					for (int i = 0; i < nb; ++i)
						++it._val;
				else
					for (int i = 0; i > nb; --i)
						--it._val;
						
				return (it);
			}
			
			/**
			*	Decrement 1 time random_iterator position.
			*/
			random_iterator& operator-=(int nb)
			{
				if (nb > 0)
					for (int i = 0; i < nb; ++i)
						--this->_val;
				else
					for (int i = 0; i > nb; --i)
						++this->_val;

				return (*this);
			}

			/**
			*	Decrement nb times random_iterator position.
			*/
			random_iterator operator-(int nb) const
			{
				random_iterator it(*this);
				
				if (nb > 0)
					for (int i = 0; i < nb; ++i)
						--it._val;
				else
					for (int i = 0; i > nb; --i)
						++it._val;

				return (it);
			}

			/**
			*	@return		A reference to random_iterator + nb. Undefined behavior if the reference
			*				returned is out of container's range.
			*/
			reference operator[](int nb) const
			{
				value_type* tmp;

				tmp = this->_val;

				if (nb > 0)
					for (int i = 0; i < nb; ++i)
						++tmp;
				else
					for (int i = 0; i > nb; --i)
						--tmp;
				
				return (*tmp);
			}

			/**
			*	@return		The range's lenght between this random_iterator and another one.
			*/
			difference_type operator-(random_iterator it) const
			{
				return (this->_val - it._val);
			}
			

			/* ------------------------------------------------------------- */
			/* --------------- NON-MEMBER OPERATOR OVERLOADS --------------- */	
			
			friend random_iterator operator+(int nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt += nb);
			}

			friend random_iterator operator-(int nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt -= nb);
			}
	};

} // namespace ft

#endif