/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/22 14:11:23 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

#include "bidirectional_iterator.hpp"

// Used in movePtr function
#define ADD 1
#define SUBSTRACT 0

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
				movePtr(this->_val, nb, ADD);
				return (*this);
			}

			/**
			*	Increment nb times random_iterator position.
			*/
			random_iterator operator+(int nb) const
			{
				random_iterator it(*this);
				
				movePtr(it._val, nb, ADD);
				return (it);
			}
			
			/**
			*	Decrement 1 time random_iterator position.
			*/
			random_iterator& operator-=(int nb)
			{
				movePtr(this->_val, nb, SUBSTRACT);
				return (*this);
			}

			/**
			*	Decrement nb times random_iterator position.
			*/
			random_iterator operator-(int nb) const
			{
				random_iterator it(*this);
				
				movePtr(it._val, nb, SUBSTRACT);
				return (it);
			}

			/**
			*	@return		A reference to random_iterator + nb. Undefined behavior if the reference
			*				returned is out of container's range.
			*/
			reference operator[](int nb) const
			{
				value_type* tmp(this->_val);

				movePtr(tmp, nb, ADD);
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

			private:

				/**
				*	Moves random_acces_iterator's pointer. Adapt between addition / substraction
				*	operation. 
				*
				*	@param val	The pointer to move.
				*	@param nb	Number of time the pointer will be increased / decreased.
				*	@param sign	Indicate if it's an addition or a substraction.
				*/
				void movePtr(nonConstPointer& val, long nb, bool sign) const
				{
					int mov;

					// If addtion, mov will be positive. If substraction, negative.
					if (sign == ADD)
						mov = nb > 0 ? mov = 1: mov = -1;
					else
						mov = nb > 0 ? mov = -1: mov = 1;

					if (nb < 0)
						nb *= -1;
					for (; nb > 0; --nb)
						val += mov;
				}
	};

} // namespace ft

#endif