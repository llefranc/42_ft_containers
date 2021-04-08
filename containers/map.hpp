/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/08 12:19:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <cmath>

#include "../templates/stl_like.hpp"

#include "../iterators/map_iterator.hpp"
#include "../iterators/rev_map_iterator.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::MAP --------------------------- *
    *
    * - Coplien form:           
    * (constructor):    Construct map
    * (destructor):     Map destructor
    * operator=:        Assign map
    *
    * - Iterators:
    * begin:            Return iterator to beginning
    * end:              Return iterator to end
    * rbegin:           Return reverse iterator to reverse beginning
    * rend:             Return reverse iterator to reverse end
    *
    * - Capacity:
    * empty:            Test whether container is empty
    * size:             Return container size
    * max_size:         Return maximum size
    *
    * - Element access:
    * operator[]:       Access element
    *
    * - Modifiers:
    * insert:           Insert elements
    * erase:            Erase elements
    * swap:             Swap content
    * clear:            Clear content
    *
    * - Observers:
    * key_comp:         Return key comparison object
    * value_comp:       Return value comparison object
    *
    * - Operations:
    * find:             Get iterator to element
    * count:            Count elements with a specific key
    * lower_bound:      Return iterator to lower bound
    * upper_bound:      Return iterator to upper bound
    * equal_range       Get range of equal elements
    * ------------------------------------------------------------- *
    */

    /**
    *   @param key      Type of keys mapped to elements.
    *   @param T        Type of elements mapped to keys.
    *   @param Compare  Comparison object used to sort the binary tree.
    *   @param Alloc    Object used to manage the vector' storage.
    */
    template < class Key, class T, class Compare = ft::less<Key>, 
            class Alloc = ft::allocator<ft::pair<const Key, T> >
    > class map
    {
            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

        private:        

            struct Node
            {
                ft::pair<const Key, T>  content;
                Node*                   parent;
                Node*                   left;
                Node*                   right;
            };


            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */
            
        public:

            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef Alloc                                           allocator_type;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;

            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            
            typedef typename ft::map_iterator<Key, T, Compare, Node, false>     iterator;
            typedef typename ft::map_iterator<Key, T, Compare, Node, true>      const_iterator;

            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, false> reverse_iterator;
            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, true>  const_reverse_iterator;


            /* ------------------------------------------------------------- */
            /* ---------------------- NESTED CLASSES ----------------------- */

            /**
            *   Comparison object using map's key_compare. It can be return with the value_comp method.
            */
            class value_compare
            {
                friend class map;
                
                protected:
                
                    key_compare comp;
                    
                    value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object

                public:
                
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;

                    bool operator()(const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
            

            /* ------------------------------------------------------------- */
            /* ------------------------ ATTRIBUTES ------------------------- */
            
        private:

            Node*                   _root;          // Pointer to the first element of the tree (root)
            Node*                   _lastElem;      // Pointer to the last elem of the tree
            size_type               _size;          // Number of T values inside the map
            allocator_type          _allocPair;     // Copy of allocator_type object
            key_compare             _comp;          // Copy of comp key_compare predicate
            ft::allocator<Node>     _allocNode;     // Node's allocator
            
            
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */
            
        public:
            
            
            /**
            *   Default constructor, creates a map with a size of 0. Initalizes a last elem node
            *   pointing to itself.
            *
            *   @param comp     The template param used for sorting the map.
            *   @param alloc    The template param used for the allocation.
            */
            explicit map(const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type()) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
            }


            /**
            *   Range constructor, creates a map with a size equal to the range between two
            *   iterators and copy the values of this range to the new elements created.
            *
            *   @param first    An iterator representing first element of the range.
            *   @param last     An iterator indicating end of the range (will be excluded and not copied).
            *   @param comp     The template param used for sorting the map.
            *   @param alloc    The template param used for the allocation.
            */
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(), 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
                
                for (; first != last; ++first)
                    insert(*first);
            }

            /**
            *   Copy constructor, creates a map with the same size and copy/construct
            *   all x values to the new elements allocated.
            *   
            *   @param x        The map that will be copied.
            */
            map(const map& x) :
                _size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;

                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    insert(*it);
            }

            /**
            *   Destructor, destroys and deallocates all the map's elements and map's nodes, 
            *   including last elem node.
            */
            ~map()
            {
                clear();
                deallocateNode(_lastElem);
            }

            /**
            *   Assigns a map to this map. Calls the copy constructor to do the
            *   assignment(copy and swap idiom).
            *   
            *   @param x        The map that will be assigned.
            */
            map& operator=(const map& x)
            {
                map tmp(x);
                this->swap(tmp);
                
                return *this;
            }


            /* ------------------------------------------------------------- */
            /* ------------------------- ITERATORS ------------------------- */

            /**
            *   @return     An iterator pointing to the first node of the map (minimum value).
            */
            iterator begin()                        { return iterator(_lastElem->right, _lastElem, _comp); }
            
            /**
            *   @return     A const_iterator pointing to the first node of the map (minimum value).
            */
            const_iterator begin() const            { return const_iterator(_lastElem->right, _lastElem, _comp); }

            /**
            *   @return     An iterator pointing after the last map's element, on a dummy node. 
            *               Access this iterator will result in undefined behavior.
            */
            iterator end()                          { return iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A const_iterator pointing after the last map's element, on a dummy node. 
            *               Access this iterator will result in undefined behavior.
            */
            const_iterator end() const              { return const_iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A reverse_iterator pointing to the last element of the map (maximum value).
            */
            reverse_iterator rbegin()               { return reverse_iterator(_lastElem->left, _lastElem, _comp); }

            /**
            *   @return     A const_reverse_iterator pointing to the last element of the map (maximum value).
            */
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastElem->left, _lastElem, _comp); }

            /**
            *   @return     A reverse_iterator pointing before the first map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            reverse_iterator rend()                 { return reverse_iterator(_lastElem, _lastElem, _comp); }

            /**
            *   @return     A const_reverse_iterator pointing before the first map's element, on a dummy node.
            *               Access this iterator will result in undefined behavior.
            */
            const_reverse_iterator rend() const     { return const_reverse_iterator(_lastElem, _lastElem, _comp); }


            /* ------------------------------------------------------------- */
            /* -------------------------- CAPACITY ------------------------- */

            /**
            *   @return     True if the map' size is equal to 0.
            */
            bool empty() const              { return _size == 0; }

            /**
            *   @return     The size of the map.
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
            *   Searches for a specific key in the tree, and if this one isn't existing,
            *   creating it. Then returning a reference on it that allows modification.
            *
            *   @param k    The key so search in the tree. If this one isn't existing, it will 
            *               be created and it's mapped value will be value-initialized.
            *   @return     A reference to the key's mapped value in the tree (already existing,
            *               or newly created).
            */
            mapped_type& operator[](const key_type& k)
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return tmp->content.second;

                value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
                return insertNode(_root, val)->content.second;
            }
            

            /* ------------------------------------------------------------- */
            /* ------------------------- MODIFIERS ------------------------- */

            /**
            *   Inserts one element if the key didn't already exist in map. Increases 
            *   the size by one if the element was inserted.
            *
            *   @param val  The pair<key, mapped value> to insert.
            *   @return     Return a pair with an iterator pointing to the newly element 
            *               inserted if the key wasn't existing in map, otherwise an iterator 
            *               to the key already present; and a boolean : true if the element 
            *               was inserted, false if already  existing.
            */
            ft::pair<iterator,bool> insert (const value_type& val)
            {
                // Searches in the tree if val's key is already present and returns 
                // an iterator to the key inside the tree if it's the case
                Node* elemIsPresent = searchNode(_root, val.first);
                if (elemIsPresent)
                    return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem, _comp), false);

                // Inserts the pair in the tree and returns an iterator to its position
                ++_size;
                return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem, _comp), true);
            }
            
            /**
            *   Inserts one element if the key didn't already exist in map, starting from 
            *   a certain position in the tree in order to optimize the insert process.
            *   Increases the size by one if the element was inserted.
            *
            *   @param position Hint for the position where the element can be inserted.
            *                   The function optimizes its insertion time if position points to 
            *                   the element that will precede the inserted element.
            *   @param val      The pair<key, mapped value> to insert.
            *   @return         An iterator pointing to the newly element inserted if the key 
            *                   wasn't existing in map, otherwise an iterator to the key already present.
            */
            iterator insert (iterator position, const value_type& val)
            {   
                // If position key is higher than val, we need to decrease position 
                // until we find the closest highest key from val in the tree
                if (position->first > val.first)
                {
                    iterator prev(position);
                    --prev;
                    while (prev != end() && prev->first >= val.first)
                    {
                        --position;
                        --prev;
                    }
                }

                // Opposite case
                else if (position->first < val.first)
                {
                    iterator next(position);
                    ++next;
                    while (next != end() && next->first <= val.first)
                    {
                        ++position;
                        ++next;
                    }
                }

                // If the value already exist, and the tree isn't empty
                if (position != end() && val.first == position->first)
                    return position;

                ++_size;
                return iterator(insertNode(position.getNode(), val), _lastElem, _comp);
            }
            
            /**
            *   Inserts all elements between first and last (if they're not already existing), 
            *   and increases the map' size.
            *
            *   @param first    An iterator pointing to the range's beginning (will be include).
            *   @param last     An iterator pointing to the range's end (will not be include).
            */  
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                while (first != last)
                    insert(*first++);
            }

            /**
            *   Removes from the map one element at a specific position. This reduces the size 
            *   of the container by one.
            *
            *   @param position Iterator pointing to a single element to be removed from the map.
            */
            void erase (iterator position)
            {
                deleteNode(position.getNode(), position->first);
                --_size;
            }

            /**
            *   Removes from the map one element that matches a specific key. This reduces the size 
            *   of the container by the number of elements removed (which can be only one).
            *
            *   @param k    The key to find in map and to remove.
            *   @return     Number of elements erased. Since you can't have twice the same key in 
            *               map, this is either 0 or 1.
            */
            size_type erase (const key_type& k)
            {
                size_type ret = deleteNode(_root, k);
                _size -= ret;
                return ret;
            }

            /**
            *   Removes from the map a range of elements. Size is decreased by the number of 
            *   elements removed.
            *
            *   @param first    An iterator pointing to the range's beginning (will be included).
            *   @param last     An iterator pointing to the range's end (will not be included).
            */
            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    iterator tmp(first);
                    ++first;
                    erase(tmp);
                }
            }

            /**
            *   Swaps a map with the content of this one.
            *
            *   @param x    The map to be swapped.
            */
            void swap (map& x)
            {
                swap(_root, x._root);
                swap(_lastElem, x._lastElem);
                swap(_size, x._size);
                swap(_comp, x._comp);
                swap(_allocPair, x._allocPair);
                swap(_allocNode, x._allocNode);
            }

            /**
            *   Removes all elements from the map (which are destroyed), leaving the 
            *   container with a size of 0. Map dummy node (end node) is still existing.
            */
            void clear()        { erase(begin(), end()); }


            /* ------------------------------------------------------------- */
            /* ------------------------- OBSERVERS ------------------------- */
            
            /**
            *   @return A copy of the comparison object used by the container to compare keys.
            */
            key_compare key_comp() const        { return _comp; }

            /**
            *   @return A comparison object that can be used to compare two elements to get 
            *           whether the key of the first one goes before the second. This object 
            *           is using a copy of the map's comparison object.
            */
            value_compare value_comp() const    { return value_compare(_comp); }
            
            
            /* ------------------------------------------------------------- */
            /* ------------------------ OPERATIONS ------------------------- */

            /**
            *   Searches the container for an element with a specific key.
            *
            *   @param k    The key to find in the container.
            *   @return     An iterator to the element matching the key if it exists in 
            *               map, container's end otherwise.
            */
            iterator find(const key_type& k)
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return iterator(tmp, _lastElem, _comp);
                
                // Case no match
                return end();
            }

            /**
            *   Searches the container for an element with a specific key.
            *
            *   @param k    The key to find in the container.
            *   @return     A const_iterator to the element matching the key if it exists in 
            *               map, container's end otherwise.
            */
            const_iterator find(const key_type& k) const
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return const_iterator(tmp, _lastElem, _comp);
                
                // Case no match
                return end();
            }

            /**
            *   Searches the container for elements with a specific key and returns the number of matches.
            *
            *   @param k    The key to count the number of occurences.
            *   @return     The number of matches. Since keys can't be twice time in map, this is 
            *               either 0 or 1.
            */
            size_type count (const key_type& k) const
            {
                Node* tmp = searchNode(_root, k);
                
                return tmp ? true: false;
            }

            /**
            *   Searches for the element whose key is not considered to go before k.
            *
            *   @param k    The key to search for.
            *   @return     An iterator to the the first element in the container whose key 
            *               is not considered to go before k, or map::end if all keys are 
            *               considered to go before k.
            */
            iterator lower_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }
            
            /**
            *   Searches for the element whose key is not considered to go before k.
            *
            *   @param k    The key to search for.
            *   @return     A const_iterator to the the first element in the container whose key 
            *               is not considered to go before k, or map::end if all keys are 
            *               considered to go before k.
            */
            const_iterator lower_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }

            /**
            *   Searches for the element whose key is considered to go after k.
            *
            *   @param k    The key to search for.
            *   @return     An iterator to the the first element in the container whose key 
            *               is considered to go after k, or map::end if no keys are 
            *               considered to go after k.
            */
            iterator upper_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            /**
            *   Searches for the element whose key is considered to go after k.
            *
            *   @param k    The key to search for.
            *   @return     A const_iterator to the the first element in the container whose key 
            *               is considered to go after k, or map::end if no keys are 
            *               considered to go after k.
            */
            const_iterator upper_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            /**
            *   Returns the bounds of a range that includes all the elements in the container 
            *   which have a specific key. Because the elements in a map container have unique keys, 
            *   the range returned will contain a single element at most.
            *
            *   @param k    The key to search in the tree.
            *   @return     The function returns a pair of iterators, whose member pair::first is the 
            *               lower bound of the range (the same as lower_bound), and pair::second is the 
            *               upper bound (the same as upper_bound).
            */
            pair<iterator,iterator> equal_range(const key_type& k)
            {
                iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<iterator, iterator>(it, next);
            }

            /**
            *   Returns the bounds of a range that includes all the elements in the container 
            *   which have a specific key. Because the elements in a map container have unique keys, 
            *   the range returned will contain a single element at most.
            *
            *   @param k    The key to search in the tree.
            *   @return     The function returns a pair of const_iterators, whose member pair::first 
            *               is the lower bound of the range (the same as lower_bound), and pair::second 
            *               is the upper bound (the same as upper_bound).
            */
            pair<const_iterator,const_iterator> equal_range(const key_type& k) const
            {
                const_iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                const_iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<const_iterator, const_iterator>(it, next);
            }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
            
        private:

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

            /**
            *   Creates a pair.
            *
            *   @param x    First element of the pair.
            *   @param y    Second element of the pair.
            */
            template <class T1,class T2>
            pair<T1,T2> make_pair(T1 x, T2 y) const
            {
                return pair<T1,T2>(x,y);
            }


            /* ----- PRIVATE MEMBER FUNCTIONS : AVL BINARY SEARCH TREE ----- */
            /* ----------- inserting / deleting inside the tree ------------ */

            /**
            *   Creates a new node and assign pair. left and right node ptr are NULL.
            *
            *   @param pair     The content (as a pair) of the created node.
            *   @return         The newly created node.
            */
            Node* createNode(const value_type& pair)
            {
                Node* newNode = _allocNode.allocate(1);

                _allocPair.construct(&newNode->content, pair);
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                return newNode;
            }

            /**
            *   Calls the destructor of node's content, and then deallocates the node.
            *
            *   @param del  The node to destroy / deallocate.
            */
            void deallocateNode(Node* del)
            {
                _allocPair.destroy(&del->content);
                _allocNode.deallocate(del, 1);
            }

            /**
            *   Calculates the tree's height.
            *
            *   @param root     The root of the tree (start with first node, then call itself with left
            *                   and right node' sons until meeting leaf).
            *   @param height   The heigth of the actual node. Increases this param by 1 each time 
            *                   it's calling itself on a node' son.
            *   @param return   The height of the tree (-1 if empty, 0 if only root node).
            */
            int heightTree(Node *root, int height)
            {
                // We reached a NULL, returning
                if (!root || root == _lastElem)
                    return height - 1;

                // Exploring left side of the actual node, then right side
                int leftHeight = heightTree(root->left, height + 1);
                int rightHeight = heightTree(root->right, height + 1);

                return leftHeight > rightHeight ? leftHeight : rightHeight;
            }

            /**
            *   Searches key in the tree and returns the element if it finds key.
            *
            *   @param root     Will start to look in the tree for the element from this node.
            *   @param key      The key to search.
            *   @param return   The element containing the key in the tree. NULL if no match occured for key.
            */
            Node* searchNode(Node* root, key_type key) const
            {
                // We reached a leaf or tree is empty
                if (!root || root == _lastElem)
                    return 0;
                
                // Case we find a match
                if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
                    return root;
                
                // Recursive loop until we find key
                if (root->content.first > key && root->left && root->left != _lastElem)
                    return searchNode(root->left, key);
                else if (root->content.first < key && root->right && root->right != _lastElem)
                    return searchNode(root->right, key);

                // If we reach this step in the first searchNode func that was called
                // with root (first node of the tree), then element is missing.
                return 0;
            }

            /**
            *   Searches for the element with the highest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the highest key in the tree.
            */
            Node* searchMaxNode(Node *root) const
            {
                // Until we meet tree's right extremity and circular link _lastElem
                if (root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Searches for the element with the lowest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the lowest key in the tree.
            */
            Node* searchMinNode(Node *root) const
            {
                // Until we meet tree's left extremity and circular link _lastElem
                if (root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

            /**
            *   Inserts a pair in the tree or a specific subtree by adding a new element, and 
            *   then equilibrates the AVL tree if necessary. If element is already present, 
            *   does nothing and return NULL.
            *
            *   @param insertPos    The starting node for the insertion in a specific subtree (will start to look for
            *                       a place for data from this node). If insertPos is root node, then it's an insertion
            *                       in the whole tree.
            *   @param data         The pair to insert in the tree.
            *   @param return       The element inserted in the tree. NULL if the element already exist in the tree. 
            */
            Node* insertNode(Node* insertPos, const value_type& pair)
            {
                // Case creating first node of the tree
                if (_root == _lastElem)
                {
                    _root = createNode(pair);
                    
                    _root->left = _lastElem;
                    _root->right = _lastElem;
                    _lastElem->left = _root;
                    _lastElem->right = _root;

                    return _root;
                }

                // Case key already exist in the tree
                if (insertPos->content.first == pair.first)
                    return 0;

                // Recursive loop until we reach a leaf or fake last node (_lastElem)
                if (insertPos->content.first > pair.first && 
                        insertPos->left && insertPos->left != _lastElem)
                    return insertNode(insertPos->left, pair);
                else if (insertPos->content.first < pair.first && 
                        insertPos->right && insertPos->right != _lastElem)
                    return insertNode(insertPos->right, pair);

                // If we reach this step, we arrived to a leaf or to the max node / min node 
                // of the tree (they're both linked to _lastElem): inserting new node to his correct position
                Node *newNode = createNode(pair);

                // Case we reached a left or right leaf
                if (insertPos->content.first > newNode->content.first && !insertPos->left)
                    insertPos->left = newNode;
                else if (insertPos->content.first < newNode->content.first && !insertPos->right)
                    insertPos->right = newNode;

                // Case we reach min node or max node, inserting the node between min / max
                // and lastElem
                else if (insertPos->left && insertPos->content.first > newNode->content.first)
                {
                    newNode->left = _lastElem;
                    _lastElem->right = newNode;
                    insertPos->left = newNode;
                }
                else if (insertPos->right && insertPos->content.first < newNode->content.first)
                {
                    newNode->right = _lastElem;
                    _lastElem->left = newNode;
                    insertPos->right = newNode;
                }
                    
                newNode->parent = insertPos;

                // Equilibrating the tree from newNode to root node
                balanceTheTree(&_root, newNode);

                return newNode;
            }

            /**
            *   Deletes the node that matches key from the tree or a specific subtree, and then equilibrates the 
            *   AVL tree if necessary. If element is missing, this function does nothing.
            *
            *   @param deletePos    The starting node for the deletion in a specific subtree (will start to look for
            *                       the key to delete from this node). If deletePos is root node, then it will looks 
            *                       for the element to delete in the whole tree.
            *   @param key          The key to delete in the tree.
            *   @param return       True if a deletion occured, false otherwise. 
            */
            bool deleteNode(Node* deletePos, key_type key)
            {
                // Balance node will point to the first node impacted by the deletion (if we delete a node, 
                // it will be the parent node; if we delete root, it will be one of his son). 
                // We will then call balanceTheTree function to equilibrate the AVL tree
                Node* balanceNode = 0;
                
                // The node to delete, looking from deletePos node until we match key
                Node* del = searchNode(deletePos, key);

                // If element isn't present, nothing to delete
                if (!del)
                    return false;
                
                /* --------------- CASE DELETING ROOT --------------- */
                // Case the node to delete is the root
                if (!del->parent)
                {
                    // Root is the only node in the tree, it will be empty
                    if (del->left == _lastElem && del->right == _lastElem)
                    {
                        _root = _lastElem;
                        _lastElem->left = _lastElem;
                        _lastElem->right = _lastElem;
                    }

                    // Case only one son (left or right, need to equilibrate the tree
                    // for only root)
                    else if (del->left && del->right == _lastElem)
                    {
                        balanceNode = del->parent;
                        _root = del->left;
                        del->left->parent = 0;
                        
                        // Since the tree is AVL, if _root has only one son, this son is 
                        // a leaf and has no left and right son. So the new root has to be 
                        // llastElem from left and right side, but he's already 
                        // linked to inked to _it from one side (in this case, left)
                        _lastElem->left = del->left;
                        del->left->right = _lastElem;
                    }
                    else if (del->left == _lastElem && del->right)
                    {
                        balanceNode = del->parent;
                        _root = del->right;
                        del->right->parent = 0;

                        // Same explanation but with opposite side than just above
                        _lastElem->right = del->right;
                        del->right->left = _lastElem;
                    }
                    
                    // Case two sons, need to switch the key of the node to delete with the highest key
                    // in the left subtree, and to delete the node with this highest key in the left subtree
                    else
                    {
                        Node* maxNode = searchMaxNode(del->left);
                        
                        // Need to destroy then construct for copying const variable)
                        _allocPair.destroy(&del->content);
                        _allocPair.construct(&del->content, maxNode->content);
                        
                        return deleteNode(del->left, maxNode->content.first);
                    }
                }


                /* --------------- CASE DELETING NODE --------------- */
                // Case the node to delete is a leaf
                else if ((!del->left || del->left == _lastElem) && (!del->right || del->right == _lastElem))
                {
                    balanceNode = del->parent;

                    // Case min node / max node, linking differs for _lastElem
                    Node* linkToParent = 0;
                    if (del->left == _lastElem || del->right == _lastElem)
                    {
                        linkToParent = _lastElem;
                        del->content.first <= del->parent->content.first ?
                            _lastElem->right = del->parent : _lastElem->left = del->parent;
                    }
                        
                    del->content.first <= del->parent->content.first ?
                        del->parent->left = linkToParent : del->parent->right = linkToParent;
                }
                
                // Case only one son (only left son or only right son)
                else if ((del->left && del->left != _lastElem) && (!del->right || del->right == _lastElem))
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->left : del->parent->right = del->left;
                    del->left->parent = del->parent;

                    // Case the node to delete is max node, need to relink _lastElem
                    if (del->right == _lastElem)
                    {
                        _lastElem->left = del->left;
                        del->left->right = _lastElem;
                    }
                }
                else if ((!del->left || del->left == _lastElem) && del->right && del->right != _lastElem)
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->right : del->parent->right = del->right;
                    del->right->parent = del->parent;
                    
                    // Case the node to delete is max node, need to relink _lastElem
                    if (del->left == _lastElem)
                    {
                        _lastElem->right = del->right;
                        del->right->left = _lastElem;
                    }
                }

                // Case two sons, need to switch the key of the node to delete with the highest key
                // in the left subtree, and to delete the node with this highest key in the left subtree
                else
                {
                    Node* maxNode = searchMaxNode(del->left);

                    // Need to destroy then construct for copying const variable)
                    _allocPair.destroy(&del->content);
                    _allocPair.construct(&del->content, maxNode->content);
                    
                    return deleteNode(del->left, maxNode->content.first);
                }

                // Equilibrating the tree from balanceNode to root node
                balanceTheTree(&_root, balanceNode);

                deallocateNode(del);
                return true;
            }


            /* ----- PRIVATE MEMBER FUNCTIONS : AVL BINARY SEARCH TREE ----- */
            /* -------------------- balancing the tree --------------------- */

            /**
            *   Compares the heights of left and right subtrees.
            *
            *   @param node His left and right subtrees will be compare.
            *   @return     Difference between left and right subtrees. Will be negative if right
            *               subtree > left subtree.
            */
            int balanceOfSubtrees(Node* node)
            {
                if (!node)
                    return 0;
                return heightTree(node->left, 1) - heightTree(node->right, 1);
            }

            /**
            *   Does a right rotation between a node and his left child. The left child will go up
            *   and take the position of this node; and this node will become the right child of the node
            *   going up.
            *
            *   @param root             First node of the tree.
            *   @param nodeGoingDown    Rotation will occured around this node.
            */
            void rotateRight(Node** root, Node* nodeGoingDown)
            {
                //   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \     RIGHT ROTATION            / \             |
                //             P   C  ------------------->>>     A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                Node* nodeGoingUp = nodeGoingDown->left;
                
                // Left Q' son become right P' son
                nodeGoingDown->left = nodeGoingUp->right;
                
                // Case right son is NULL to prevent segfault
                if (nodeGoingUp->right)
                    nodeGoingUp->right->parent = nodeGoingDown;
                
                // rigth P' son is Q
                nodeGoingUp->right = nodeGoingDown;
                
                // Parent P = Parent Q
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if Q has a parent (if not, Q is root) and if it's the case,
                // determinating if it's left son or right son. Then updating Q's parent with
                // his new son, P node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;
                
                // Parent of Q is now P
                nodeGoingDown->parent = nodeGoingUp;

                // Updating root node if the rotation occured on root
                if (!nodeGoingUp->parent)
                    *root = nodeGoingUp;
            }

            /**
            *   Does a left rotation between a node and his right child. The right child will go up
            *   and take the position of this node; and this node will become the left child of the node
            *   going up.
            *
            *   @param root             First node of the tree.
            *   @param nodeGoingDown    Rotation will occured around this node.
            */
            void rotateLeft(Node** root, Node* nodeGoingDown)
            {
                //   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \          LEFT ROTATION        / \             |
                //             P   C    <<<-------------------   A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                Node* nodeGoingUp = nodeGoingDown->right;
                
                // Right P' son become left Q' son
                nodeGoingDown->right = nodeGoingUp->left;

                // Case Q left son is NULL to prevent segfault
                if (nodeGoingUp->left)
                    nodeGoingUp->left->parent = nodeGoingDown;
                
                // Left Q' son is now P
                nodeGoingUp->left = nodeGoingDown;
                
                // Parent Q = Parent P
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if P has a parent (if not, P is root) and if it's the case,
                // determinating if it's left son or right son. Then updating P's parent with
                // his new son, Q node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;

                // Parent of P is now Q
                nodeGoingDown->parent = nodeGoingUp;

                // Updating root node if the rotation occured on root
                if (!nodeGoingUp->parent)
                    *root = nodeGoingUp;
            }

            /**
            *   Starts from a node in the AVL tree, and will check for this node and all the parent's node
            *   until root if their balance (height of left and right subtree) is correct. If not, a rotation
            *   (left or right) around the unbalanced node will occured in order to restore tree's balance.
            *
            *   @param root First node of the tree.
            *   @param node Will check the balance's node, and will check every parent until reaching root.
            */
            void balanceTheTree(Node** root, Node* node)
            {
                // Checking balance of subtrees every parents of this node until we 
                // reach root node          
                while (node)
                {
                    int balance;
                    
                    // Right right case (right subtree is deeper, and right right subtree aswell)
                    if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
                        rotateLeft(root, node);

                    // Right left case (if balance of right node == 0, no difference between right 
                    // right case and and right left case)
                    else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
                    {
                        rotateRight(root, node->right);
                        rotateLeft(root, node);
                    }
                    
                    // Left left case (opposite of right right case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
                        rotateRight(root, node);

                    // Left right case (opposite of right left case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
                    {
                        rotateLeft(root, node->left);
                        rotateRight(root, node);
                    }
                    node = node->parent;
                }
            }
            
    };  // class map
        
} // namespace ft

#endif