/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/24 16:58:56 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------ FT::STACK -------------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct stack
    * (destructor):         Destruct stack
    * operator=:            Assign content
    *
    * - Member functions:
    * empty:                Test whether container is empty
    * size:                 Return size
    * top:                  Access next element
    * push:                 Insert element
    * pop:                  Remove top element
    *
    * - Non-member function overloads:
    * relational operators: Relational operators for stack
    * ------------------------------------------------------------- *
    */

    /**
    *   @param T            Type of container's elements.
    *   @param Container    Container object used internally to store T elements.
    */
    template <class T, class Container = ft::list<T> >
    class stack
    {
            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

        public:

            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
            
            
            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

        private:

            container_type  _ctnr;  // Underlying container object (either a vector, a list or a
                                    // deque) where the elements are stored.
            
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */
            
        public:
            
            /**
            *   Constructs a stack container adaptor object. It keeps internally a container object 
            *   as data, which is a copy of the ctnr argument passed to the constructor.
            *
            *   @param ctnr The container object to store as data. If no container is pass as argument,
            *               ctnr calls the default constructor and will be empty.
            */
            explicit stack (const container_type& ctnr = container_type()) :
                    _ctnr(ctnr) {}
            
            /**
            *   Copy constructor, creates a stack with the same container object.
            *   
            *   @param x        The stack that will be copied.
            */
            stack(const stack& x) :
                    _ctnr(x._ctnr) {}
                
            /**
            *   This is the destructor of the container object stored as data that 
            *   cleans all the ressources.
            */
            ~stack() {}
        
            /**
            *   Assigns a stack to this stack. Calls the copy constructor to do the
            *   assignment(copy and swap idiom).
            *   
            *   @param x        The stack that will be assigned.
            */
            stack& operator=(const stack& x)
            {
                stack tmp(x);
                swap(_ctnr, tmp._ctnr);
                return *this;
            }
            

            /* ------------------------------------------------------------- */
            /* ----------------- MEMBER FUNCTION OVERLOADS ----------------- */

            /**
            *   
            *   Calls member function empty of the underlying container object, which returns 
            *   true if the container is empty.
            */
            bool empty() const                  { return _ctnr.empty(); }
            
            /**
            *   
            *   Calls member function size of the underlying container object, which returns 
            *   container' size.
            */
            size_type size() const              { return _ctnr.size(); }
            
            /**
            *   Calls member function back of the underlying container object, which returns a 
            *   reference to the top element in the stack. Since stacks are last-in first-out 
            *   containers, the top element is the last element inserted into the stack.
            */
            value_type& top()                   { return _ctnr.back(); }

            /**
            *   Calls member function back of the underlying container object, which returns a 
            *   const reference to the top element in the stack. Since stacks are last-in 
            *   first-out containers, the top element is the last element inserted into the stack.
            */
            const value_type& top() const       { return _ctnr.back(); }
            
            /**
            *   Calls member function push_back of the underlying container object, which inserts 
            *   a new element at the top of the stack. Size is increased by one.
            *
            *   @param val  Content of the new element will be initialized to a copy of val.
            */
            void push (const value_type& val)   { _ctnr.push_back(val); }
            
            /**
            *   Calls member function pop_back of the underlying container object, which removes 
            *   the element on top of the stack (latest element inserted), reducing his size by one.
            *   This calls the removed element's destructor.
            */
            void pop()                          { _ctnr.pop_back(); }


            /* ------------------------------------------------------------- */
            /* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
            
            /**
            *   Performs the appropriate comparison operation between lhs and rhs.
            *   Each of these operator overloads calls the same operator on the underlying container objects.
            */

            friend bool operator==(const stack& lhs, const stack& rhs)  { return lhs._ctnr == rhs._ctnr; }
            friend bool operator!=(const stack& lhs, const stack& rhs)  { return lhs._ctnr != rhs._ctnr; }
            friend bool operator<(const stack& lhs, const stack& rhs)   { return lhs._ctnr < rhs._ctnr; }
            friend bool operator<=(const stack& lhs, const stack& rhs)  { return lhs._ctnr <= rhs._ctnr; }
            friend bool operator>(const stack& lhs, const stack& rhs)   { return lhs._ctnr > rhs._ctnr; }
            friend bool operator>=(const stack& lhs, const stack& rhs)  { return lhs._ctnr >= rhs._ctnr; }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */

        private:
        
            /**
            *   Swaps two variables.
            *
            *   @param a        Will be swap with b.
            *   @param b        Will be swap with a.
            */
            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp(a);
                a = b;
                b = tmp;
            }

    }; // class stack
        
} // namespace ft

#endif