/* ************************************************************************** */
/*                                                                          */
/*                                                      :::   ::::::::   */
/*   rev_list_iterator.hpp                            :+:     :+:   :+:   */
/*                                                  +:+ +:+      +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+      */
/*                                              +#+#+#+#+#+   +#+          */
/*   Created: 2021/01/07 15:06:15 by llefranc         #+#   #+#          */
/*   Updated: 2021/02/23 12:16:41 by lucaslefran      ###   ########.fr    */
/*                                                                          */
/* ************************************************************************** */

#ifndef REVERSE_LIST_ITERATOR_HPP
#define REVERSE_LIST_ITERATOR_HPP

#include "../templates/type1_or_type2.hpp"
#include "list_iterator.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------- FT::REV_LIST_ITERATOR ------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct rev_list_iterator
    * (destructor):         Rev_list_iterator destructor
    * operator=:            Assign content
    *
    * - Operators
    * operators:            Operators for rev_list_iterator
    * non-member operators: Operators for rev_list_iterator
    * ------------------------------------------------------------- *
    */
        
    /**
    *   @param T    Type of container's elements.
    *   @param Node The structure used as nodes in the list.
    *   @param B    Boolean to indicate if it's an iterator / a const iterator.
    */
    template<typename T, typename Node, bool B>
    class rev_list_iterator
    {
            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */
            
        public:
            
            typedef long int                                        difference_type;
            typedef T                                               value_type;
            typedef size_t                                          size_type;
            
            typedef std::bidirectional_iterator_tag                 iterator_category;
            typedef typename chooseConst<B, T&, const T&>::type     reference;
            typedef typename chooseConst<B, T*, const T*>::type     pointer;
            typedef Node*                                           nodePtr;


            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

        private:

                nodePtr _node;  // A pointer to a node in the list


            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:
        
            /**
            *   Default constructor, creates a rev_list_iterator pointing to a node.
            *
            *   @param node  A pointer to node containing a T element. Value initialized if not provided.
            */
            rev_list_iterator(nodePtr node = 0) : _node(node) {}
            
            /**
            *   Copy constructor : creates a const rev_list_iterator pointing to the same node.
            *   Convert constructor : creates a rev_list_iterator from a const rev_list_iterator,
            *   pointing to the same node.
            *   
            *   @param copy  The iterator that will be copied.
            */
            rev_list_iterator(const rev_list_iterator<T, Node, false>& copy) { _node = copy.getNode(); }
            
            /**
            *   Convert constructor : creates a rev_list_iterator from a const / not const 
            *   list_iterator, pointing to the previous T element. This is necessary so 
            *   begin() == rend(), and end == rbegin().
            *   
            *   @param copy  The list_iterator that will be converted.
            */
            rev_list_iterator(const list_iterator<T, Node, false>& copy) { _node = copy.getNode()->prev; }
            
            ~rev_list_iterator() {}

            /**
            *   Assigns a rev_list_iterator to this rev_list_iterator. Both iterators will point to the
            *   same node.
            *   
            *   @param x        The rev_list_iterator that will be assigned.
            */
            rev_list_iterator& operator=(const rev_list_iterator& assign)
            {
                if (this != &assign)
                    _node = assign._node;
                return (*this);
            }
            

            /* ------------------------------------------------------------- */
            /* --------------------------- GETTERS ------------------------- */

            /**
            *   @return A non constant pointer to the actual node that the iterator is 
            *           pointing to.
            */
            nodePtr getNode() const   { return _node; }

            
            /* ------------------------------------------------------------- */
            /* ---------------------- OPERATOR OVERLOADS ------------------- */

            reference operator*() const             { return (_node->content); }
            pointer operator->() const              { return (&_node->content); }

            rev_list_iterator& operator++()         { _node = _node->prev; return (*this); }
            rev_list_iterator operator++(int)       { rev_list_iterator res(*this); ++(*this); return (res); };
            rev_list_iterator& operator--()         { _node = _node->next; return (*this); }
            rev_list_iterator operator--(int)       { rev_list_iterator res(*this); --(*this); return (res); };
            

            /* ------------------------------------------------------------- */
            /* --------------- NON-MEMBER OPERATOR OVERLOADS --------------- */ 
            
            bool operator==(const rev_list_iterator& it) const  { return (it._node == _node); }
            bool operator!=(const rev_list_iterator& it) const  { return (it._node != _node); }

    }; // class rev_list_iterator

} // namespace ft

#endif