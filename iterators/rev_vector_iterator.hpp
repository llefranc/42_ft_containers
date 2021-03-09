/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_vector_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/09 13:29:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_VECTOR_ITERATOR_HPP
#define REV_VECTOR_ITERATOR_HPP

#include "vector_iterator.hpp"
#include "../templates/stl_like.hpp"

// Used in movePtr function
#define ADD 1
#define SUBSTRACT 0

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------ FT::REV_VECTOR_ITERATOR ------------------ *
    *
    * - Coplien form:
    * (constructor):        Construct rev_vector_iterator
    * (destructor):         Rev_vector_iterator destructor
    * operator=:            Assign content
    *
    * - Operators
    * operators:            Operators for rev_vector_iterator
    * non-member operators: Operators for rev_vector_iterator
    * ------------------------------------------------------------- *
    */
        
    /**
    *   @param T    Type of container's elements.
    *   @param B    Boolean to indicate if it's a const or not vector iterator.
    */
    template<typename T, bool B>
    class rev_vector_iterator
    {
        public:

            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

            typedef long int                                        difference_type;
            typedef T                                               value_type;
            typedef size_t                                          size_type;
            
            typedef std::random_access_iterator_tag                 iterator_category;
            typedef typename chooseConst<B, T&, const T&>::type     reference;
            typedef typename chooseConst<B, T*, const T*>::type     pointer;
            typedef T*                                              elemPtr;
            
            
            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

        private:

            elemPtr _val;   // A pointer to an element in the vector array


            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public: 

            /**
            *   Default constructor, creates a rev_vector_iterator pointing to val.
            *
            *   @param val  A pointer to a T element. Value initialized if not provided.
            */
            rev_vector_iterator(elemPtr val = 0) : _val(val) {}

            /**
            *   Copy constructor : creates a const rev_vector_iterator pointing to the same T element.
            *   Convert constructor : creates a rev_vector_iterator from a const rev_vector_iterator,
            *   pointing to the same T element.
            *   
            *   @param copy     The rev_vector_iterator that will be copied.
            */
            rev_vector_iterator(const rev_vector_iterator<T, false>& copy) { _val = copy.getElemPtr(); }

            /**
            *   Convert constructor : creates a rev_vector_iterator from a const / not const 
            *   vector_iterator, pointing to the previous T element. This is necessary so 
            *   begin() == rend(), and end == rbegin().
            *   
            *   @param copy     The vector_iterator that will be converted.
            */
            explicit rev_vector_iterator(const vector_iterator<T, false>& copy) { _val = copy.getElemPtr() - 1; }

            ~rev_vector_iterator() {}

            /**
            *   Assign a rev_vector_iterator to this rev_vector_iterator. Both iterators will point to the
            *   same T element.
            *   
            *   @param x        The rev_vector_iterator that will be assigned.
            */
            rev_vector_iterator& operator=(const rev_vector_iterator& assign)
            {
                if (this != &assign)
                    _val = assign._val;
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* --------------------------- GETTERS ------------------------- */

            /**
            *   @return A non constant pointer to the actual element that the iterator is 
            *           pointing to.
            */
            elemPtr getElemPtr() const      { return _val; }


            /* ------------------------------------------------------------- */
            /* --------------------- OPERATOR OVERLOADS -------------------- */

            reference operator*() const             { return (*_val); }
            pointer operator->() const              { return (_val); }

            rev_vector_iterator& operator++()       { --_val; return (*this); }
            rev_vector_iterator& operator--()       { ++_val; return (*this); }
            
            rev_vector_iterator operator++(int)
            {
                rev_vector_iterator res(*this);
                ++(*this);
                return (res);
            }
            
            rev_vector_iterator operator--(int)
            {
                rev_vector_iterator res(*this);
                --(*this);
                return (res);
            }
            
            bool operator==(const rev_vector_iterator& it) const    { return (it._val == _val); }
            bool operator!=(const rev_vector_iterator& it) const    { return (it._val != _val); }
            bool operator<(const rev_vector_iterator& it) const     { return (it._val > this->_val); }
            bool operator>(const rev_vector_iterator& it) const     { return (it._val < this->_val); }
            bool operator<=(const rev_vector_iterator& it) const    { return (it._val >= this->_val); }
            bool operator>=(const rev_vector_iterator& it) const    { return (it._val <= this->_val); }
            
            /**
            *   Increment 1 time vector_iterator position.
            */
            rev_vector_iterator& operator+=(int nb)
            {
                movePtr(this->_val, nb, ADD);
                return (*this);
            }

            /**
            *   Increment nb times vector_iterator position.
            */
            rev_vector_iterator operator+(int nb) const
            {
                rev_vector_iterator it(*this);
                        
                movePtr(it._val, nb, ADD);
                return (it);
            }
            
            /**
            *   Decrement 1 time vector_iterator position.
            */
            rev_vector_iterator& operator-=(int nb)
            {                       
                movePtr(this->_val, nb, SUBSTRACT);
                return (*this);
            }

            /**
            *   Decrement nb times vector_iterator position.
            */
            rev_vector_iterator operator-(int nb) const
            {
                rev_vector_iterator it(*this);
                
                movePtr(it._val, nb, SUBSTRACT);
                return (it);
            }

            /**
            *   @return     A reference to rev_vector_iterator + nb. Undefined behavior if the 
            *               reference returned is out of container's range.
            */
            reference operator[](int nb) const
            {
                value_type* tmp(this->_val);

                movePtr(tmp, nb, ADD);
                return (*tmp);
            }

            /**
            *   Do a difference between 2 reverse iterators (in the opposite way than normal 
            *   iterators, so that it1 - it2 == rev_it1 - rev_it2).
            *
            *   @return     The range's lenght between this rev_vector_iterator and another one.
            */
            difference_type operator-(rev_vector_iterator it) const
            {
                return (it._val - this->_val);
            }
            

            /* ------------------------------------------------------------- */
            /* ---------------------- FRIEND OPERATORS --------------------- */
            
            friend rev_vector_iterator operator+(int nb, const rev_vector_iterator& it)
            {
                rev_vector_iterator newIt(it);
                return (newIt += nb);
            }

            friend rev_vector_iterator operator-(int nb, const rev_vector_iterator& it)
            {
                rev_vector_iterator newIt(it);
                return (newIt -= nb);
            }


            /* ------------------------------------------------------------- */
            /* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
            
        private:

            /**
            *   Moves rev_vector_acces_iterator's pointer. Adapt between addition / substraction
            *   operation. 
            *
            *   @param val  The pointer to move.
            *   @param nb   Number of time the pointer will be increased / decreased.
            *   @param sign Indicate if it's an addition or a substraction.
            */
            void movePtr(elemPtr& val, long nb, bool sign) const
            {
                int mov;

                // If addtion, mov will be negative. If substraction, positive.
                if (sign == ADD)
                    mov = nb > 0 ? mov = -1: mov = 1;
                else
                    mov = nb > 0 ? mov = 1: mov = -1;

                if (nb < 0)
                    nb *= -1;
                for (; nb > 0; --nb)
                    val += mov;
            }
            
    }; // class rev_vector_iterator

} // namespace ft

#endif