/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:20:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/13 17:01:33 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "../templates/type1_or_type2.hpp"

namespace ft
{
	template<class Key, class T, class Compare, typename Node, bool B>
	class map_iterator
	{
		public:
		
			typedef Key												key_type;
			typedef Compare											key_compare;
			typedef	T												mapped_type;
			
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef long int										difference_type;
			typedef size_t											size_type;
			
			typedef typename chooseConst<B, value_type&, const value_type&>::type		reference;
			typedef typename chooseConst<B, value_type*, const value_type*>::type		pointer;
			typedef Node*																nonConstPointer;
			
			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			map_iterator(nonConstPointer node = 0, nonConstPointer lastElem = 0) :
				_node(node), _lastElem(lastElem) {}
		
			map_iterator(const map_iterator<Key, T, Compare, Node, false>& copy)
			{
				_node = copy.getNonConstNode();
				_lastElem = copy.getNonConstLastElem();
			}
			
			~map_iterator() {}

			nonConstPointer	getNonConstNode() const		{ return _node; }
			nonConstPointer	getNonConstLastElem() const		{ return _lastElem; }

			map_iterator& operator=(const map_iterator& assign)
			{
				if (this != &assign)
					_node = assign._node;
				return (*this);
			}

			reference operator*() const			{ return (_node->content); }
			pointer operator->() const		{ return (&_node->content); } //pointer et pas non const pointer ? a approfondir


// ALLER TO EN BAS A GAUCHE QUAND YA UN FDP A DROITE
			map_iterator& operator++()
			{
				// To save base value and compare it with parents if no right son
				nonConstPointer previousNode = _node;

				// Special case where iterator is on lastElem : we're looping to the beginning
				// of the tree
				if (_node == _lastElem)
				{
					_node = _lastElem->right;
					return (*this);
				}

				// Moving node* until we find a node with an higher value or equal value (_lastElem == end)
				while (_node != _lastElem && _node->content.first <= previousNode->content.first)
				{
					// Case right son is either node with higher value or _lastElem node	
					if (_node->right && (_node->right == _lastElem || 
							_node->right->content.first > previousNode->content.first))
						_node = _node->right;

					// No right son so need to go up of one level and try same loop with node's parent
					else
						_node = _node->parent;
				}
				return (*this);
			}

			map_iterator operator++(int)
			{
				// Same logic than in operator++
				map_iterator res(*this);

				if (_node == _lastElem)
				{
					_node = _lastElem->right;
					return (res);
				}
				while (_node != _lastElem && _node->content.first <= res->first)
				{
					if (_node->right && (_node->right == _lastElem || 
							_node->right->content.first > res->first))
						_node = _node->right;
					else
						_node = _node->parent;
				}
				return (res);
			}

			map_iterator& operator--()
			{
				// Same logic than in operator++
				nonConstPointer previousNode = _node;

				if (_node == _lastElem)
				{
					_node = _lastElem->left;
					return (*this);
				}

				while (_node != _lastElem && _node->content.first >= previousNode->content.first)
				{
					if (_node->left && (_node->left == _lastElem || 
							_node->left->content.first < previousNode->content.first))
						_node = _node->left;
					else
						_node = _node->parent;
				}
				return (*this);
			}

			map_iterator operator--(int)
			{
				// Same logic than in operator++
				map_iterator res(*this);

				if (_node == _lastElem)
				{
					_node = _lastElem->left;
					return (res);
				}
				while (_node != _lastElem && _node->content.first >= res->first)
				{
					if (_node->left && (_node->left == _lastElem || 
							_node->left->content.first < res->first))
						_node = _node->left;
					else
						_node = _node->parent;
				}
				return (res);
			}

			bool operator==(const map_iterator& it) const	{ return (it._node == _node); }
			bool operator!=(const map_iterator& it) const	{ return (it._node != _node); }

		protected:

			nonConstPointer	_node;
			nonConstPointer	_lastElem;
	};
} // namespace ft


#endif