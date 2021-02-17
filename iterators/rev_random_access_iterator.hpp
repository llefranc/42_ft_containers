/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_random_access_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/17 10:49:40 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_RANDOM_ACCESS_ITERATOR_HPP
#define REV_RANDOM_ACCESS_ITERATOR_HPP

#include "rev_bidirectional_iterator.hpp"
#include "random_access_iterator.hpp"
#include "../templates/stl_like.hpp"

// Used in movePtr function
#define ADD 1
#define SUBSTRACT 0

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------ FT::REV_RANDOM_ITERATOR ------------------ *
    *
    * - Coplien form:
    * (constructor):        Construct rev_random_iterator
    * (destructor):         Rev_random_iterator destructor
    * operator=:            Assign content
    *
    * - Operators
    * operators:            Operators for rev_random_iterator
    * non-member operators: Operators for rev_random_iterator
    * ------------------------------------------------------------- *
    */
        
    /**
    *   @param T    Type of container's elements.
    *   @param B    Boolean to indicate if it's a const or not random iterator.
    */
    template<typename T, bool B>
    class rev_random_iterator : public rev_bidirec_iterator<T, B>
    {
        public:

            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

            typedef typename ft::rev_bidirec_iterator<T, B>::difference_type    difference_type;
            typedef typename ft::rev_bidirec_iterator<T, B>::value_type         value_type;
            typedef typename ft::rev_bidirec_iterator<T, B>::size_type          size_type;
            
            typedef typename ft::rev_bidirec_iterator<T, B>::reference          reference;
            typedef typename ft::rev_bidirec_iterator<T, B>::pointer            pointer;
            typedef typename ft::rev_bidirec_iterator<T, B>::nonConstPointer    nonConstPointer;

            typedef typename ft::rev_bidirec_iterator<T, B>                     rev_bidirec_iterator;
            

            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

            /**
            *   Default constructor, creates a rev_random_iterator pointing to val.
            *
            *   @param val  A pointer to a T element. Value initialized if not provided.
            */
            rev_random_iterator(nonConstPointer val = 0) :
                    rev_bidirec_iterator(val) {}

            /**
            *   Copy constructor : creates a const rev_random_iterator pointing to the same T element.
            *   Convert constructor : creates a rev_random_iterator from a const rev_random_iterator,
            *   pointing to the same T element.
            *   
            *   @param copy     The rev_random_iterator that will be copied.
            */
            rev_random_iterator(const rev_random_iterator<T, false>& copy) :
                rev_bidirec_iterator(copy.getNonConstPointer()) {}

            /**
            *   Convert constructor : creates a rev_random_iterator from a const / not const 
            *   random_iterator, pointing to the previous T element. This is necessary so 
            *   begin() == rend(), and end == rbegin().
            *   
            *   @param copy     The random_iterator that will be converted.
            */
            explicit rev_random_iterator(const random_iterator<T, false>& copy) :
                rev_bidirec_iterator(copy.getNonConstPointer() - 1) {}

            ~rev_random_iterator() {}

            /**
            *   Assign a rev_random_iterator to this rev_random_iterator. Both iterators will point to the
            *   same T element.
            *   
            *   @param x        The rev_random_iterator that will be assigned.
            */
            rev_random_iterator& operator=(const rev_random_iterator& assign)
            {
                if (this != &assign)
                    rev_bidirec_iterator::_val = assign._val;
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* --------------------- OPERATOR OVERLOADS -------------------- */

            bool operator<(const rev_random_iterator& it) const     { return (it._val > this->_val); }
            
            bool operator>(const rev_random_iterator& it) const     { return (it._val < this->_val); }
            
            bool operator<=(const rev_random_iterator& it) const    { return (it._val >= this->_val); }

            bool operator>=(const rev_random_iterator& it) const    { return (it._val <= this->_val); }
            
            
            /**
            *   Increment 1 time random_iterator position.
            */
            rev_random_iterator& operator+=(int nb)
            {
                movePtr(this->_val, nb, ADD);
                return (*this);
            }

            /**
            *   Increment nb times random_iterator position.
            */
            rev_random_iterator operator+(int nb) const
            {
                rev_random_iterator it(*this);
                        
                movePtr(it._val, nb, ADD);
                return (it);
            }
            
            /**
            *   Decrement 1 time random_iterator position.
            */
            rev_random_iterator& operator-=(int nb)
            {                       
                movePtr(this->_val, nb, SUBSTRACT);
                return (*this);
            }

            /**
            *   Decrement nb times random_iterator position.
            */
            rev_random_iterator operator-(int nb) const
            {
                rev_random_iterator it(*this);
                
                movePtr(it._val, nb, SUBSTRACT);
                return (it);
            }

            /**
            *   @return     A reference to rev_random_iterator + nb. Undefined behavior if the 
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
            *   @return     The range's lenght between this rev_random_iterator and another one.
            */
            difference_type operator-(rev_random_iterator it) const
            {
                return (it._val - this->_val);
            }
            

            /* -------- FRIEND OPERATORS -------- */        
            
            friend rev_random_iterator operator+(int nb, const rev_random_iterator& it)
            {
                rev_random_iterator newIt(it);
                return (newIt += nb);
            }

            friend rev_random_iterator operator-(int nb, const rev_random_iterator& it)
            {
                rev_random_iterator newIt(it);
                return (newIt -= nb);
            }

            private:

                /**
                *   Moves rev_random_acces_iterator's pointer. Adapt between addition / substraction
                *   operation. 
                *
                *   @param val  The pointer to move.
                *   @param nb   Number of time the pointer will be increased / decreased.
                *   @param sign Indicate if it's an addition or a substraction.
                */
                void movePtr(nonConstPointer& val, long nb, bool sign) const
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
    };

} // namespace ft

#endif