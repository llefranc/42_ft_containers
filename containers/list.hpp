/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/17 10:48:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

#include "../iterators/list_iterator.hpp"
#include "../iterators/rev_list_iterator.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::LIST -------------------------- *
    *
    * - Coplien form:           
    * (constructor):        Construct list
    * (destructor)          Destruct list
    * operator=             Assign list
    *
    * - Iterators:
    * begin                 Return iterator to beginning
    * end                   Return iterator to end
    * rbegin                Return reverse iterator to reverse beginning
    * rend                  Return reverse iterator to reverse end
    *
    * - Capacity:
    * empty                 Test whether container is empty
    * size                  Return size
    * max_size              Return maximum size
    *
    * - Element access:
    * front                 Access first element
    * back                  Access last element
    *
    * - Modifiers:
    * assign                Assign new content to container
    * push_front            Insert element at beginning
    * pop_front             Delete first element
    * push_back             Add element at the end
    * pop_back              Delete last element
    * insert                Insert elements
    * erase                 Erase elements
    * swap                  Swap content
    * resize                Change size
    * clear                 Clear content
    *
    * - Operations:
    * splice                Transfer elements from list to list
    * remove                Remove elements with specific value
    * remove_if             Remove elements fulfilling condition
    * unique                Remove duplicate values
    * merge                 Merge sorted lists
    * sort                  Sort elements in container
    * reverse               Reverse the order of elements
    *
    * - Non-member function overloads
    * relational operators: Relational operators for list
    * swap:                 Exchanges contents of two lists
    * ------------------------------------------------------------- *
    */

    template <typename T, class Alloc = std::allocator<T> >
    class list
    {
        private:

            struct Node
            {
                T       content;
                Node*   prev;
                Node*   next;
            };          
        
        
        public:

            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

            typedef T                                               value_type;
            typedef Alloc                                           allocator_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;

            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            
            typedef typename ft::list_iterator<T, Node, false>      iterator;
            typedef typename ft::list_iterator<T, Node, true>       const_iterator;

            typedef typename ft::rev_list_iterator<T, Node, false>  reverse_iterator;
            typedef typename ft::rev_list_iterator<T, Node, true>   const_reverse_iterator;


            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

            /**
            *   Default constructor, creates a list with a size of 0. Initalizes an end node
            *   pointing to itself.
            *
            *   @param alloc    The template param used for the allocation.
            */
            explicit list (const allocator_type& alloc = allocator_type()) :
                    _size(0), _allocT(alloc)
            {
                newEndNode();
            }
            
            /**
            *   Fill constructor, creates a list with a size of n and initializes the 
            *   values.
            *
            *   @param n        The number of elements that will be created.
            *   @param val      The value used for initialization (value initialized by default).
            *   @param alloc    The template param used for the allocation.
            */
            explicit list (size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type()) :
                    _size(0), _allocT(alloc)
            {
                newEndNode();

                while (_size < n)
                    push_back(val);
            }

            /**
            *   Range constructor, creates a list with a size equal to the range between two
            *   iterators and copy the values of this range to the new elements created.
            *
            *   @param first    An iterator representing first element of the range.
            *   @param last     An iterator indicating end of the range (will be excluded and not copied).
            *   @param alloc    The template param used for the allocation.
            */
            template <class InputIterator>
            list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
                    _size(0), _allocT(alloc)
            {
                newEndNode();

                for (; first != last; ++first)
                    push_back(*first);
            }
            
            /**
            *   Copy constructor, creates a list with the same size and copy/construct
            *   all x values to the new elements allocated.
            *   
            *   @param x        The list that will be copied.
            */
            list (const list& x) :
                    _size(0), _allocT(x._allocT), _allocNode(x._allocNode)
            {
                newEndNode();

                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    push_back(*it);
            }

            /**
            *   Destructor, destroys all the list's elements and list's nodes, including
            *   end node.
            */
            ~list()
            {
                while (_size > 0)
                    pop_back();
                // delete _endList; VERSION SANS ALLOC
                _allocNode.deallocate(_endList, 1);
            }

            /**
            *   Assigns a list to this list. Calls the copy constructor to do the
            *   assignment(copy and swap idiom).
            *   
            *   @param x        The list that will be assigned.
            */
            list& operator= (const list& x)
            {
                list copy(x);
                this->swap(copy);

                return *this;
            }


            /* ------------------------------------------------------------- */
            /* ------------------------- ITERATORS ------------------------- */

            /**
            *   @return     An iterator pointing to the first node of the list.
            */
            iterator begin()                        { return !_size ? iterator(_endList) :
                                                        iterator(_endList->next); }

            /**
            *   @return     A const_iterator pointing to the first element of the list.
            */
            const_iterator begin() const            { return !_size ? iterator(_endList) :
                                                        iterator(_endList->next); }

            /**
            *   @return     An iterator pointing to the list end node. Access this
            *               iterator will result in undefined behavior.
            */
            iterator end()                          { return iterator(_endList); }

            /**
            *   @return     An const_iterator pointing to the list end node. Access this
            *               iterator will result in undefined behavior.
            */
            const_iterator end() const              { return const_iterator(_endList); }

            /**
            *   @return     A reverse_iterator pointing to the last element of the list.
            *               This is list end node if the list is empty.
            */
            reverse_iterator rbegin()               { return !_size ? reverse_iterator(_endList) : 
                                                        reverse_iterator(_endList->prev); }
            
            /**
            *   @return     A const_reverse_iterator pointing to the last element of the list.
            *               This is list end node if the list is empty.
            */
            const_reverse_iterator rbegin() const   { return !_size ? const_reverse_iterator(_endList) :
                                                        const_reverse_iterator(_endList->prev); }

            /**
            *   @return     A reverse_iterator pointing before the first element of the list
            *               (so pointing to list end node because this is a circular linked list).
            *               Access this iterator will result in undefined behavior.
            */
            reverse_iterator rend()                 { return reverse_iterator(_endList); }

            /**
            *   @return     A const_reverse_iterator pointing before the first element of the list
            *               (so pointing to list end node because this is a circular linked list).
            *               Access this iterator will result in undefined behavior.
            */
            const_reverse_iterator rend() const     { return const_reverse_iterator(_endList); }


            /* ------------------------------------------------------------- */
            /* -------------------------- CAPACITY ------------------------- */
            
            /**
            *   @return     True if the list' size is equal to 0.
            */
            bool empty() const              { return _size == 0; }

            /**
            *   @return     The size of the list.
            */
            size_type size() const          { return _size; }
            
            /**
            *   @return     The max possible size to be allocated.
            */
            size_type       max_size() const
            {
                if (sizeof(value_type) == 1)
                    return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
                return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
            }


            /* ------------------------------------------------------------- */
            /* ---------------------- ELEMENTS ACCESS ---------------------- */ 

            /**
            *   Access first list's element. Undefined behavior if the list is empty.
            *   
            *   @return     A reference to the first list's element.
            */
            reference front()               { return _endList->next->content; }

            /**
            *   Access first list's element. Undefined behavior if the list is empty.
            *   
            *   @return     A const reference to the first list's element.
            */
            const_reference front() const   { return _endList->next->content; }

            /**
            *   Access last list's element. Undefined behavior if the list is empty.
            *   
            *   @return     A reference to the last list's element.
            */
            reference back()                { return _endList->prev->content; }

            /**
            *   Access last list's element. Undefined behavior if the list is empty.
            *   
            *   @return     A const reference to the last list's element.
            */
            const_reference back() const    { return _endList->prev->content; }


            /* ------------------------------------------------------------- */
            /* ------------------------- MODIFIERS ------------------------- */

            /**
            *   Assigns new contents to the list, replacing its current content, 
            *   and modifying its size accordingly.The new contents are elements constructed 
            *   from each of the elements in the range between first and last iterators.
            *   
            *   @param n    Number of new elements constructed.
            *   @param val  Each new elements will be copy constructed from val.
            */  
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                size_type i = 0;
                for (iterator it = begin(); first != last; ++it, ++i, ++first)
                {
                    // If list is to small, creating new Nodes
                    if (i >= _size)
                        push_back(*first);
                        
                    // If element already exist, just replacing his content
                    else
                    {
                        _allocT.destroy(&it->content);
                        _allocT.construct(&it->content, *first);
                    }
                }
                
                // Destroying remaining Nodes if list is taller than assignment size
                while (_size > i)
                    pop_back();
            }

            /**
            *   Assigns new contents to the list, replacing its current content, 
            *   and modifying its size accordingly.
            *   
            *   @param n    Number of new elements constructed.
            *   @param val  Each new elements will be copy constructed from val.
            */  
            void assign (size_type n, const value_type& val)
            {
                size_type i = 0;
                for (iterator it = begin(); i < n; ++it, ++i)
                {
                    // If list is to small, creating new Nodes
                    if (i >= _size)
                        push_back(val);
                        
                    // If element already exist, just replacing his content
                    else
                    {
                        _allocT.destroy(&it->content);
                        _allocT.construct(&it->content, val);
                    }
                }
                
                // Destroying remaining Nodes if list is taller than assignment size
                while (_size > i)
                    pop_back();
            }

            /**
            *   Adds a new element at the beginning of the list, after its current first element.
            *   Size is increased.  If list is empty, the new element is still inserted as first 
            *   list element.
            *
            *   @param val  The new element will be copy constructed from val.
            */
            void push_front (const value_type& val)
            {
                // Node* tmp = new Node; VERSION SANS ALLOC
                // tmp->content = val;
                Node* tmp = createNode(val);

                tmp->prev = _endList;
                tmp->next = _endList->next;
                _endList->next->prev = tmp;
                _endList->next = tmp;
                
                ++_size;
            }

            /**
            *   Removes the first element in the list, reducing the container size by one.
            *   This destroys the removed element. Does nothing if the list is empty.
            */
            void pop_front()
            {
                if (_size)
                    deleteNode(_endList->next);
            }

            /**
            *   Adds a new element at the end of the list, after its current last element.
            *   Size is increased. If list is empty, the new element becomes first list element.
            *
            *   @param val  The new element will be copy constructed from val.
            */
            void push_back (const value_type& val)
            {
                // Node* tmp = new Node; VERSION SANS ALLOC
                // tmp->content = val;
                Node* tmp = createNode(val);

                tmp->prev = _endList->prev;
                tmp->next = _endList;
                _endList->prev->next = tmp;
                _endList->prev = tmp;
                
                ++_size;
            }
        
            /**
            *   Removes the last element in the list, reducing the container size by one.
            *   This destroys the removed element. Does nothing if the list is empty.
            */
            void pop_back()
            {
                if (_size)
                    deleteNode(_endList->prev);
            }

            /**
            *   Inserts 1 element with a value of val at a position, and increases the list' size.
            *
            *   @param position The element will be inserted just before this position.
            *   @param val      Value of the element inserted.
            *   @return         An iterator on the newly element inserted.
            */
            iterator insert (iterator position, const value_type& val)
            {
                Node* newNode = createNode(val);
                
                // Linking new Node between position and position -1
                newNode->prev = position->prev;
                newNode->next = position->prev->next;
                
                // Linking position and position -1 to new element
                newNode->prev->next = newNode;
                newNode->next->prev = newNode;
                
                ++_size;
                return iterator(--position);
            }
            
            /**
            *   Inserts n elements with a value of val at a position, and increases the list' size.
            *
            *   @param position Elements will be inserted just before this position.
            *   @param n        Number of elements to be inserted.
            *   @param val      Value of the elements inserted.
            */
            void insert (iterator position, size_type n, const value_type& val)
            {
                while (n-- > 0)
                    position = insert(position, val);
            }
            
            /**
            *   Inserts all elements between first and last, and increases the vector' size.
            *
            *   @param position Elements will be inserted just before this position.
            *   @param first    An iterator pointing to the range's beginning (will be include).
            *   @param last     An iterator pointing to the range's end (will not be include).
            */  
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                // Inserting in reverse order
                for (ft::pair<reverse_iterator, reverse_iterator> it(last, first);
                        it.first != it.second; ++it.first)
                    position = insert(position, *it.first);
            }

            iterator erase (iterator position)
            {
                // Using iterator's Node constructor for creating last
                return erase(position, position->next);
            }

            iterator erase (iterator first, iterator last)
            {
                for (; first != last;)
                    deleteNode((++first)->prev);
                return last;
            }

            /**
            *   Swaps a list with the content of this one.
            *
            *   @param x    The list to be swapped.
            */
            void swap (list& x)
            {
                swap(_size, x._size);
                swap(_endList, x._endList);
                swap(_allocT, x._allocT);
                swap(_allocNode, x._allocNode);
            }

            /**
            *   Resizes the list so that it contains n elements. Push_back or pop_back will occured 
            *   depending if elements need to be added or removed.
            *    
            *   @param n    The number of elements that the list will contain after beeing resized.
            *   @param val  If new elements need to be added, they will be initialize with val
            *               (value initialize by default).
            */
            void resize (size_type n, value_type val = value_type())
            {
                while (n > _size)
                    push_back(val);
                while (n < _size)
                    pop_back();
            }

            /**
            *   Removes all elements from the list (which are destroyed), leaving the 
            *   container with a size of 0. List end node is still existing.
            */
            void clear()
            {
                while (_size)
                    pop_back();
            }
            

            /* ------------------------------------------------------------- */
            /* ------------------------ OPERATIONS ------------------------- */ 
            
            /**
            *   Transfering the entire x list at a certain position in this list. This effectively inserts 
            *   those elements into the container and removes them from x, altering the sizes of both containers.
            *
            *   @param position Position within the container where the elements of x are inserted.
            *   @param x        A list object of the same type.
            */
            void splice (iterator position, list& x)
            {
                while (x.size())
                    splice(position, x, x.begin());
            }

            /**
            *   Transfering one x element at a certain position in this list. This effectively inserts 
            *   those elements into the container and removes them from x, altering the sizes of both containers.
            *
            *   @param position Position within the container where the elements of x are inserted.
            *   @param x        A list object of the same type.
            *   @param i        Iterator to an element in x. Only this single element is transferred.
            */
            void splice (iterator position, list& x, iterator i)
            {
                // Linking previous and next node in x together
                i->next->prev = i->prev;
                i->prev->next = i->next;

                // Linking i in this list
                i->prev = position->prev;
                i->next = position.getNonConstPointer();
                position->prev->next = i.getNonConstPointer();
                position->prev = i.getNonConstPointer();
                
                --x._size;
                ++_size;
            }

            /**
            *   Transfering a range of x elements at a certain position in this list. This effectively 
            *   inserts those elements into the container and removes them from x, altering the 
            *   sizes of both containers.
            *
            *   @param position Position within the container where the elements of x are inserted.
            *   @param x        A list object of the same type.
            *   @param first    Iterator pointing to the first range's element inside x (will be transfered).
            *   @param last     Iterator pointing to the last range's element inside x (will not be transfered).
            */
            void splice (iterator position, list& x, iterator first, iterator last)
            {
                if (first == last)
                    return;

                if (first->next == last.getNonConstPointer())
                    splice(position, x, first);
                else
                {
                    // Counting range' size
                    size_type rangeSize = 0;
                    for (iterator tmp(first); tmp != last; ++tmp)
                        ++rangeSize;
                    
                    // Saving last range's elem
                    iterator lastRangeElem(last->prev);
                    
                    // Removing range from list x
                    first->prev->next = last.getNonConstPointer();
                    last->prev = first->prev;

                    // Linking range in this list
                    first->prev = position->prev;
                    lastRangeElem->next = position.getNonConstPointer();
                    position->prev->next = first.getNonConstPointer();
                    position->prev = lastRangeElem.getNonConstPointer();

                    x._size -= rangeSize;
                    _size += rangeSize;
                }
            }

            /**
            *   Removes from the container all the elements that compare equal to val. This calls the 
            *   destructor of these objects and reduces the container size by the number of elements removed.
            *
            *   @param val  Value of the elements to be removed.
            */
            void remove (const value_type& val)
            {
                for (iterator it = end(); it->next != end().getNonConstPointer();)
                {
                    if (it->next->content == val)
                        deleteNode(it->next);
                    else
                        ++it;
                }
            }

            /**
            *   Removes from the container all the elements for which Predicate pred returns true. This calls the 
            *   destructor of these objects and reduces the container size by the number of elements removed.
            *
            *   @param pred Unary predicate that takes a value of the same type as those contained 
            *               in the list and returns true or false (when true occured for an element, 
            *               this one will be removed).
            */
            template <class Predicate>
            void remove_if (Predicate pred)
            {
                for (iterator it = end(); it->next != end().getNonConstPointer();)
                {
                    if (pred(it->next->content))
                        deleteNode(it->next);
                    else
                        ++it;
                }
            }

            /**
            *   Removes all but the first element from every consecutive group of equal elements in the container.
            */
            void unique()
            {
                for (iterator it = end(); it->next != end().getNonConstPointer();)
                {
                    if (it != end() && *it == it->next->content)
                        deleteNode(it->next);
                    else
                        ++it;
                }
            }

            /**
            *   Removes all but the first element from every consecutive group in the container 
            *   for which the binary predicate will return true.
            *
            *   @param binary_pred  Binary predicate that takes two values of the same type than those contained 
            *                       in the list and returns true to remove the element passed as first argument, 
            *                       false otherwise.
            */
            template <class BinaryPredicate>
            void unique (BinaryPredicate binary_pred)
            {
                for (iterator it = end(); it->next->next != end().getNonConstPointer();)
                {
                    if (binary_pred(it->next->content, it->next->next->content))
                        deleteNode(it->next->next);
                    else
                        ++it;
                }
            }

            /**
            *   Merges x into the list by transferring all of its elements at their respective ordered positions 
            *   into the container (both containers shall already be ordered). The comparison between the two
            *   list elements is done by using operator<. This empty x list.
            *
            *   @param x    A list object of the same type.
            */
            void merge (list& x)
            {
                if (&x == this)
                    return ;
                    
                iterator thisIt = end();

                // Starting from the end, until all elements in x are removed and only
                // end element remained, pointing to itself
                for (iterator xIt = x.end(); xIt->next != x.end().getNonConstPointer();)
                {
                    // If we reached end of this list or if comp is true
                    if (thisIt->next == end().getNonConstPointer() ||
                            xIt->next->content < thisIt->next->content)
                    {
                        // Splicing new element and iterator in this list will be pointing on it
                        splice(thisIt->next, x, xIt->next);
                        ++thisIt;
                    }
                    else
                        ++thisIt;
                }
            }
            
            /**
            *   Merges x into the list by transferring all of its elements at their respective ordered positions 
            *   into the container (both containers shall already be ordered). The comparison between the two
            *   list elements is done by using a binary predicate. This empty x list.
            *
            *   @param x    A list object of the same type.
            *   @param comp Binary predicate that, taking two values of the same type than those contained in the list, 
            *               returns true if the first argument is considered to go before the second, and false otherwise.
            */
            template <class Compare>
            void merge (list& x, Compare comp)
            {
                if (&x == this)
                    return ;
                
                iterator thisIt = end();
                
                // Starting from the end, until all elements in x are removed and only
                // end element remained, pointing to itself
                for (iterator xIt = x.end(); xIt->next != x.end().getNonConstPointer();)
                {
                    // If we reached end of this list or if comp is true
                    if (thisIt->next == end().getNonConstPointer() ||
                            comp(xIt->next->content, thisIt->next->content))
                    {
                        // Splicing new element and iterator in this list will be pointing on it
                        splice(thisIt->next, x, xIt->next);
                        ++thisIt;
                    }
                    else
                        ++thisIt;
                }
            }


            /**
            *   Sorts the elements in the list using operator<. The nodes with their content are moved, 
            *   none element is destructed / copy constructed.
            */
            void sort()
            {
                for (iterator it = begin(); it->next != end().getNonConstPointer(); ++it)
                {
                    iterator tmp(it);
                    
                    // Checking if there is a value inf to it after it
                    for (iterator min(it->next); min != end(); ++min)
                        if (*min < *tmp)
                            tmp = min;

                    // Swapping it and the inf node and restarting to search
                    // inf values from the node that was swapped
                    if (*tmp < *it)
                    {
                        swap2Nodes(tmp.getNonConstPointer(), it.getNonConstPointer());
                        it = tmp;
                    }
                }
            }

            /**
            *   Sorts the elements in the list using a binary predicate. The nodes with their content 
            *   are moved, none element is destructed / copy constructed.
            *
            *   @param comp Binary predicate that, taking two values of the same type than those contained in the list, 
            *               returns true if the first argument is considered to go before the second, and false otherwise.
            */
            template <class Compare>
            void sort (Compare comp)
            {
                for (iterator it = begin(); it->next != end().getNonConstPointer(); ++it)
                {
                    iterator tmp(it);
                    
                    // Checking if there is a value inf to it after it
                    for (iterator min(it->next); min != end(); ++min)
                        if (comp(*min, *tmp))
                            tmp = min;

                    // Swapping it and the inf node and restarting to search
                    // inf values from the node that was swapped
                    if (comp(*tmp, *it))
                    {
                        swap2Nodes(tmp.getNonConstPointer(), it.getNonConstPointer());
                        it = tmp;
                    }
                }
            }

            /**
            *   Reverse the list. Each node from the beginning will be inserted from the
            *   end of the list one in front of the other.
            */
            void reverse()
            {
                if (_size > 1)
                {
                    Node* insertBefore = _endList;
                    Node* tmp;

                    while (_endList->next != insertBefore)
                    {
                        // First Node that will be move before Node insertBefore
                        tmp = _endList->next;

                        // Linking _endList and Node "_endList + 2"
                        _endList->next = tmp->next;
                        tmp->next->prev = _endList;

                        // Moving first Node between Node insertBefore
                        // and Node "insertBefore - 1"
                        tmp->next = insertBefore;
                        tmp->prev = insertBefore->prev;
                        tmp->prev->next = tmp;
                        tmp->next->prev = tmp;

                        // Node insertBefore is now pointing to the Node we moved 
                        insertBefore = tmp;
                    }
                }
            }


            /* ------------------------------------------------------------- */
            /* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

            /**
            *   @return     True if the 2 vectors have same size and same content.
            */
            friend bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
            {
                if (lhs.size() != rhs.size())
                    return false;

                for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
                        it.first != lhs.end(); ++it.first, ++it.second)
                    if (*(it.first) != *(it.second))
                        return false;
                return true;
            }
            
            /**
            *   @return     True if the 2 vectors have different size or different content.
            */
            friend bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)      { return !(lhs == rhs); }
            
            /**
            *   Compares the elements sequentially using operator< and stopping at the 
            *   first occurrence.
            *
            *   @return     True if all lhs' elements are < to rhs' elements, or if
            *               lhs' content == rhs' content and lhs' size < rhs' size.
            */
            friend bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
            {
                for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
                        it.first != lhs.end() && it.second != rhs.end(); ++it.first, ++it.second)
                    if (*(it.first) < *(it.second))
                        return true;
                return (lhs.size() < rhs.size());
            }

            /**
            *   Uses operator< to compare the 2 vectors (rhs < lhs).
            *
            *   @return     True if all lhs' elements are > to all rhs' elements, or if
            *               lhs' content == rhs' content and lhs' size > rhs' size.
            */
            friend bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)     { return rhs < lhs; }

            /**
            *   Uses operator< to compare the 2 vectors !(rhs < lhs).
            *
            *   @return     True if all lhs' elements are <= to all rhs' elements, or if
            *               lhs' content == rhs' content and lhs' size <= rhs' size.
            */
            friend bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)      { return !(rhs < lhs); }

            /**
            *   Uses operator< to compare the 2 vectors !(lhs < rhs).
            *
            *   @return     True if all lhs' elements are >= to all rhs' elements, or if
            *               lhs' content == rhs' content and lhs' size >= rhs' size.
            */
            friend bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)     { return !(lhs < rhs); }

            /**
            *   Swaps the content of two vectors.
            *
            *   @param x    Will be swap with y.
            *   @param y    Will be swap with x.
            */
            friend void swap(list& x, list& y)                                              { x.swap(y); }


        private:

            Node*                   _endList;       // Pointer to the neutral element of the circle linked list
            size_type               _size;          // Number of T values inside the list
            Alloc                   _allocT;        // Copy of allocator_type object
            std::allocator<Node>    _allocNode;     // Node's allocator


            /* ------------------------------------------------------------- */
            /* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
            
            /**
            *   Create a new endNode. Data isn't constructed.
            */
            void newEndNode()
            {
                // _endList = new Node;         VERSION SANS ALLOCATOR
                // _endList->next = _endList;
                // _endList->prev = _endList;           

                _endList = _allocNode.allocate(1);
                _endList->next = _endList;
                _endList->prev = _endList;          
            }

            /**
            *   Destroy Node's content and then deallocate the Node.
            *
            *   @param toDelete The Node to destroy and deallocate.
            */
            void deleteNode(Node *toDelete)
            {
                // Linking previous and next element together
                toDelete->prev->next = toDelete->next;
                toDelete->next->prev = toDelete->prev;

                // delete toDelete;         VERSION SANS ALLOCATOR
                _allocT.destroy(&toDelete->content);
                _allocNode.deallocate(toDelete, 1);

                --_size;
            }

            /**
            *   Allocate a new Node and copy construct his content from val.
            *
            *   @param val  The content to copy construct.
            *   @return     The Node newly created.
            */
            Node* createNode(const value_type& val = value_type())
            {
                Node *newNode = _allocNode.allocate(1);
                _allocT.construct(&newNode->content, val);
                
                return newNode;
            }

            /**
            *   Swap two nodes by exchanging their previous and next Node*.
            *
            *   @param a        Will be swap with b.
            *   @param b        Will be swap with a.
            */
            void swap2Nodes(Node *a, Node *b)
            {
                // If a and b are neighbor nodes but b is before a,
                // reversing them so a is always before b
                if (a->prev == b)
                    swap(a, b);

                // Saving elements next to a
                Node *aPrev = a->prev;
                Node *aNext = a->next;
                
                // Case a and b aren't neighbor nodes
                if (a->next != b)
                {
                    // Switching a to b position, between prev and next elem to b
                    a->prev = b->prev;
                    a->next = b->next;
                    b->next->prev = a;
                    b->prev->next = a;
                    
                    // Switching a to b position, between prev and next elem to a
                    b->prev = aPrev;
                    b->next = aNext;
                    aPrev->next = b;
                    aNext->prev = b;
                }
                
                // Case a and b are neighbor nodes
                else
                {
                    // switching a to b position
                    a->prev = b;
                    a->next = b->next;
                    b->next->prev = a;
                    
                    // Switching b to a position
                    b->prev = aPrev;
                    aPrev->next = b;
                    b->next = a;
                }
            }

            /**
            *   Swaps two variables using references.
            *
            *   @param a        Will be swap with b.
            *   @param b        Will be swap with a.
            */
            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp = a;
                a = b;
                b = tmp;
            }

    }; // class list
        
} // namespace ft

#endif