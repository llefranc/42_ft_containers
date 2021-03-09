/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_map_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/15 10:49:09 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_MAP_ITERATOR_HPP
#define REV_MAP_ITERATOR_HPP

#include "../templates/type1_or_type2.hpp"
#include "map_iterator.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * -------------------- FT::REV_MAP_ITERATOR ------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct rev_map_iterator
    * (destructor):         Rev_map_iterator destructor
    * operator=:            Assign content
    *
    * - Operators
    * operators:            Operators for rev_map_iterator
    * non-member operators: Operators for rev_map_iterator
    * ------------------------------------------------------------- *
    */
        
    /**
    *   @param Key      Type of container's key elements.
    *   @param T        Type of container's mapped elements.
    *   @param Compare  The predicate used to sort the binary tree.
    *   @param Node     The structure used as nodes in the binary tree.
    *   @param B        Boolean to indicate if it's an iterator / a const iterator.
    */
    template<class Key, class T, class Compare, typename Node, bool B>
    class rev_map_iterator
    {
        /* ------------------------------------------------------------- */
        /* -------------------------- ALIASES -------------------------- */
        
        public:
        
            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;
            
            typedef std::bidirectional_iterator_tag                                     iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
            typedef Node*                                                               nodePtr;
            

            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */
            
        private:

            nodePtr         _node;      // Pointer to a binary tree's node
            nodePtr         _lastElem;  // Pointer to the dummy node of binary tree
            key_compare     _comp;      // Comparison object used to sort the binary tree
        
        
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:
        
            /**
            *   Default constructor, creates a rev_map_iterator pointing to a node.
            *
            *   @param node     A pointer to a node containing a T element. Value initialized if not provided.
            *   @param lastElem A pointer to the dummy node of the binary tree. Value initialized if not provided.
            *   @param comp     The comparison object used to sort the binary tree.  Value initialized if not provided.
            */
            rev_map_iterator(nodePtr node = 0, nodePtr lastElem = 0,
                            const key_compare& comp = key_compare()) :
                _node(node), _lastElem(lastElem), _comp(comp) {}
        
            /**
            *   Copy constructor : creates a const rev_map_iterator pointing to the same node.
            *   Convert constructor : creates a rev_map_iterator from a const rev_map_iterator,
            *   pointing to the same node.
            *   
            *   @param copy     The iterator that will be copied.
            */
            rev_map_iterator(const rev_map_iterator<Key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }
            
            /**
            *   Convert constructor : creates a rev_map_iterator from a const / not const 
            *   map_iterator, pointing to the previous T element. This is necessary so 
            *   begin() == rend(), and end == rbegin().
            *   
            *   @param copy     The map_iterator that will be converted.
            */
            explicit rev_map_iterator(map_iterator<Key, T, Compare, Node, false> copy)
            {
                --copy;
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }

            ~rev_map_iterator() {}

            /**
            *   Assigns a rev_map_iterator to this rev_map_iterator. Both iterators will point to the
            *   same node.
            *   
            *   @param x    The rev_map_iterator that will be assigned.
            */
            rev_map_iterator& operator=(const rev_map_iterator& assign)
            {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* --------------------------- GETTERS ------------------------- */

            /**
            *   @return A non constant pointer to the actual node that the iterator is 
            *           pointing to.
            */
            nodePtr getNonConstNode() const         { return _node; }

            /**
            *   @return A non constant pointer to the dummy node at the end of the 
            *           binary tree.
            */
            nodePtr getNonConstLastElem() const     { return _lastElem; }

            /**
            *   @return The comparison object used to sort the binary tree.
            */
            key_compare getCompare() const          { return _comp; }


            /* ------------------------------------------------------------- */
            /* -------------------------- OPERATORS ------------------------ */

            reference operator*() const             { return (_node->content); }
            pointer operator->() const              { return (&_node->content); }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            rev_map_iterator& operator++()
            {
                // Opposite logic than in --operator
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, previousNode->content.first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }

                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            rev_map_iterator operator++(int)
            {
                // Opposite logic than in --operator
                rev_map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(_node->content.first, res->first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, res->first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            rev_map_iterator& operator--()
            {
                // To save base value and compare it with parents if no right son
                nodePtr previousNode = _node;

                // Special case where iterator is on lastElem : we're looping to the beginning
                // of the tree
                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (*this);
                }

                // _comp is equivalent to operator <. So:
                //      - operator>(lhs, rhs)  <==>  _comp(rhs, lhs)
                //      - operator<=(lhs, rhs)  <==>  !_comp(rhs, lhs)
                //      - operator>=(lhs, rhs)  <==>  !_comp(lhs, rhs)

                // Moving node* until we find a node with an higher value or equal value (_lastElem == end)
                //                              <=> _node->content.first <= previousNode->content.first)
                while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first))
                {
                    // Case right son is either node with higher value or _lastElem node    
                    if (_node->right && (_node->right == _lastElem || 
                        // <=> _node->right->content.first > previousNode->content.first))
                            _comp(previousNode->content.first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        // Starting from the minimum key in the right subtree
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }

                    // No right son so need to go up of one level and try same loop with node's parent
                    else
                        _node = _node->parent;
                }
                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            rev_map_iterator operator--(int)
            {
                // Same logic than in ++operator
                rev_map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(res->first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(res->first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            bool operator==(const rev_map_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const rev_map_iterator& it) const   { return (it._node != _node); }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
            
        private:

            /**
            *   Searches for the element with the highest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the highest key in the tree.
            */
            Node* searchMaxNode(Node *root)
            {
                // Until we meet tree's right extremity and circular link _lastElem
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Searches for the element with the lowest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the lowest key in the tree.
            */
            Node* searchMinNode(Node *root)
            {
                // Until we meet tree's left extremity and circular link _lastElem
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

    }; // class rev_map_iterator

} // namespace ft

#endif