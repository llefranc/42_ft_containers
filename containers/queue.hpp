/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:16:45 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/03 12:53:46 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------ FT::QUEUE -------------------------- *
	*
	* - Coplien form:
	* (constructor):		Construct queue
	* (destructor):			Destruct queue
	* operator=:			Assign content
	*
	* - Member functions:
	* empty:				Test whether container is empty
	* size:					Return size
	* front:				Access next element
	* back:					Access last element
	* push:					Insert element
	* pop:					Remove next element
	*
	* - Non-member function overloads:
	* relational operators:	Relational operators for queue
	* ------------------------------------------------------------- *
	*/

	template <class T, class Container = std::deque<T> >
	class queue
	{
				public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
			
			
			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */
			
			/**
			*	Constructs a queue container adaptor object. It keeps internally a container object 
			*	as data, which is a copy of the ctnr argument passed to the constructor.
			*
			*	@param ctnr	The container object to store as data. If no container is pass as argument,
			*				ctnr calls the default constructor and will be empty.
			*/
			explicit queue (const container_type& ctnr = container_type()) :
					_ctnr(ctnr) {}
			
			/**
			*	Copy constructor, creates a queue with the same container object.
			*	
			*	@param x		The queue that will be copied.
			*/
			queue(const queue& x) :
					_ctnr(x._ctnr) {}
				
			/**
			*	This is the destructor of the container object stored as data that 
			*	cleans all the ressources.
			*/
			~queue() {}
		
			/**
			*	Assigns a queue to this queue. Calls the copy constructor to do the
			*	assignment(copy and swap idiom).
			*	
			*	@param x		The queue that will be assigned.
			*/
			queue& operator=(const queue& x)
			{
				queue tmp(x);
				swap(_ctnr, tmp._ctnr);
				return *this;
			}

			/* ------------------------------------------------------------- */
			/* ----------------- MEMBER FUNCTION OVERLOADS ----------------- */

			/**
			*	
			*	Calls member function empty of the underlying container object, which returns 
			*	true if the container is empty.
			*/
			bool empty() const					{ return _ctnr.empty(); }
			
			/**
			*	
			*	Calls member function size of the underlying container object, which returns 
			*	container' size.
			*/
			size_type size() const				{ return _ctnr.size(); }
			
			/**
			*	Calls member function front of the underlying container object, which returns a 
			*	reference to the next element in the queue. The next element is the "oldest" element 
			*	in the queue and the same element that is popped out from the queue when queue::pop is called.
			*/
			value_type& front()					{ return _ctnr.front(); }

			/**
			*	Calls member function front of the underlying container object, which returns a const
			*	reference to the next element in the queue. The next element is the "oldest" element 
			*	in the queue and the same element that is popped out from the queue when queue::pop is called.
			*/
			const value_type& front() const		{ return _ctnr.front(); }
			
			/**
			*	Calls member function back of the underlying container object, which returns a 
			*	reference to the newest element in the queue (latest element pushed in the queue).
			*/
			value_type& back()					{ return _ctnr.back(); }

			/**
			*	Calls member function back of the underlying container object, which returns a const 
			*	reference to the newest element in the queue (latest element pushed in the queue).
			*/
			const value_type& back() const		{ return _ctnr.back(); }
			
			/**
			*	Calls member function push_back of the underlying container object, which inserts 
			*	a new element at the end of the queue. Size is increased by one.
			*
			*	@param val	Content of the new element will be initialized to a copy of val.
			*/
			void push (const value_type& val)	{ _ctnr.push_back(val); }
			
			/**
			*	Calls member function pop_front of the underlying container object, which removes 
			*	the oldest element of the queue, reducing his size by one. This calls the removed 
			*	element's destructor.
			*/
			void pop()							{ _ctnr.pop_front(); }


			/* ------------------------------------------------------------- */
			/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
			
			/**
			*	Performs the appropriate comparison operation between lhs and rhs.
			*	Each of these operator overloads calls the same operator on the underlying container objects.
			*/

			friend bool operator==(const queue& lhs, const queue& rhs)	{ return lhs._ctnr == rhs._ctnr; }
			friend bool operator!=(const queue& lhs, const queue& rhs)	{ return lhs._ctnr != rhs._ctnr; }
			friend bool operator<(const queue& lhs, const queue& rhs)	{ return lhs._ctnr < rhs._ctnr; }
			friend bool operator<=(const queue& lhs, const queue& rhs)	{ return lhs._ctnr <= rhs._ctnr; }
			friend bool operator>(const queue& lhs, const queue& rhs)	{ return lhs._ctnr > rhs._ctnr; }
			friend bool operator>=(const queue& lhs, const queue& rhs)	{ return lhs._ctnr >= rhs._ctnr; }

			
		private:

			container_type	_ctnr;	// Underlying container object (either a list or a deque) 
									// where the elements are stored.

			/**
			*	Swaps two variables.
			*
			*	@param a		Will be swap with b.
			*	@param b		Will be swap with a.
			*/
			template <typename U>
			void swap(U& a, U& b)
			{
				U tmp(a);
				a = b;
				b = tmp;
			}

	}; // class queue
	
} // namespace ft

#endif