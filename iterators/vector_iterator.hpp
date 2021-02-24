/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/24 15:54:34 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../templates/type1_or_type2.hpp"

// Used in movePtr function
#define ADD 1
#define SUBSTRACT 0

namespace ft
{
    template<typename T, bool B>
    class rev_vector_iterator;
        
        
    /**
    * ------------------------------------------------------------- *
    * -------------------- FT::VECTOR_ITERATOR -------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct vector_iterator
    * (destructor):         Vector_iterator destructor
    * operator=:            Assign content
    *
    * - Operators
    * operators:            Operators for vector_iterator
    * non-member operators: Operators for vector_iterator
    * ------------------------------------------------------------- *
    */

    /**
    *   @param T    Type of container's elements.
    *   @param B    Boolean to indicate if it's an iterator / a const iterator.
    */
    template<typename T, bool B>
    class vector_iterator
    {
        public:

            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

            typedef long int                                        difference_type;
            typedef T                                               value_type;
            typedef size_t                                          size_type;
            
            typedef typename chooseConst<B, T&, const T&>::type     reference;
            typedef typename chooseConst<B, T*, const T*>::type     pointer;
            typedef T*                                              elemPtr;
            

			/* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

		private:
		
			elemPtr _val;	// A pointer to an element in the vector array


            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

		public:

            /**
            *   Default constructor, creates a vector_iterator pointing to val.
            *
            *   @param val  A pointer to a T element. Value initialized if not provided.
            */
            vector_iterator(elemPtr val = 0) :
                    _val(val) {}
                    
            /**
            *   Copy constructor : creates a const vector_iterator pointing to the same T element.
            *   Convert constructor : creates a vector_iterator from a const vector_iterator,
            *   pointing to the same T element.
            *   
            *   @param copy     The iterator that will be copied.
            */
            vector_iterator(const vector_iterator<T, false>& copy) { _val = copy.getElemPtr(); }

            ~vector_iterator() {}

            /**
            *   Assign a vector_iterator to this vector_iterator. Both iterators will point to the
            *   same T element.
            *   
            *   @param x        The vector_iterator that will be assigned.
            */
            vector_iterator& operator=(const vector_iterator& assign)
            {
                if (this != &assign)
                    _val = assign._val;
                return (*this);
            }


			/* ------------------------------------------------------------- */
            /* --------------------------- GETTERS ------------------------- */

			/**
			*	@return	A non constant pointer to the actual element that the iterator is 
			*			pointing to.
			*/
			elemPtr getElemPtr() const      { return _val; }


            /* ------------------------------------------------------------- */
            /* --------------------- OPERATOR OVERLOADS -------------------- */

			reference operator*() const         { return (*_val); }
            pointer operator->() const			{ return (_val); }

            vector_iterator& operator++()		{ ++_val; return (*this); }
            vector_iterator& operator--()		{ --_val; return (*this); }
			
            vector_iterator operator++(int)
			{
				vector_iterator res(*this);
				++(*this);
				return (res);
			}
			
            vector_iterator operator--(int)
			{
				vector_iterator res(*this);
				--(*this);
				return (res);
			}
            
            bool operator==(const vector_iterator& it) const	{ return (it._val == _val); }
            bool operator!=(const vector_iterator& it) const	{ return (it._val != _val); }
            bool operator<(const vector_iterator& it) const     { return (it._val > this->_val); }
            bool operator>(const vector_iterator& it) const     { return (it._val < this->_val); }
            bool operator<=(const vector_iterator& it) const    { return (it._val >= this->_val); }
            bool operator>=(const vector_iterator& it) const    { return (it._val <= this->_val); }
            
            /**
            *   Increments 1 time vector_iterator position.
            */
            vector_iterator& operator+=(int nb)
            {
                movePtr(this->_val, nb, ADD);
                return (*this);
            }

            /**
            *   Increments nb times vector_iterator position.
            */
            vector_iterator operator+(int nb) const
            {
                vector_iterator it(*this);
                
                movePtr(it._val, nb, ADD);
                return (it);
            }
            
            /**
            *   Decrements 1 time vector_iterator position.
            */
            vector_iterator& operator-=(int nb)
            {
                movePtr(this->_val, nb, SUBSTRACT);
                return (*this);
            }

            /**
            *   Decrements nb times vector_iterator position.
            */
            vector_iterator operator-(int nb) const
            {
                vector_iterator it(*this);
                
                movePtr(it._val, nb, SUBSTRACT);
                return (it);
            }

            /**
            *   @return     A reference to vector_iterator + nb. Undefined behavior if the reference
            *               returned is out of container's range.
            */
            reference operator[](int nb) const
            {
                value_type* tmp(this->_val);

                movePtr(tmp, nb, ADD);
                return (*tmp);
            }

            /**
            *   @return     The range's lenght between this vector_iterator and another one.
            */
            difference_type operator-(vector_iterator it) const
            {
                return (this->_val - it._val);
            }
            

            /* ------------------------------------------------------------- */
            /* --------------- NON-MEMBER OPERATOR OVERLOADS --------------- */ 
            
            friend vector_iterator operator+(int nb, const vector_iterator& it)
            {
                vector_iterator newIt(it);
                return (newIt += nb);
            }

            friend vector_iterator operator-(int nb, const vector_iterator& it)
            {
                vector_iterator newIt(it);
                return (newIt -= nb);
            }


			/* ------------------------------------------------------------- */
            /* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */

		private:

			/**
			*   Moves random_acces_iterator's pointer. Adapt between addition / substraction
			*   operation. 
			*
			*   @param val  The pointer to move.
			*   @param nb   Number of time the pointer will be increased / decreased.
			*   @param sign Indicate if it's an addition or a substraction.
			*/
			void movePtr(elemPtr& val, long nb, bool sign) const
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
			
    }; // class vector_iterator

} // namespace ft

#endif