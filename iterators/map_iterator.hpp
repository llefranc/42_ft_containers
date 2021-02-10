/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:20:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/10 16:38:22 by llefranc         ###   ########.fr       */
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

			map_iterator(nonConstPointer node = 0) : _node(node) {}
			map_iterator(const map_iterator<Key, T, Compare, Node, false>& copy) { _node = copy.getNonConstPointer(); }
			~map_iterator() {}

			nonConstPointer	getNonConstPointer() const		{ return _node; }

			map_iterator& operator=(const map_iterator& assign)
			{
				if (this != &assign)
					_node = assign._node;
				return (*this);
			}

			reference operator*()			{ return (_node->content); }
			pointer operator->() const		{ return (&_node->content); } //pointer et pas non const pointer ? a approfondir

			map_iterator& operator++()
			{
				// pointe sur le meme element
				nonConstPointer previousNode = _node;

				// on va sur la droit, l'elem doit etre sup. Si pas d'elem a droite, on remonte les parents
				// jusqu'a trouver un element superieur
				while (_node->content.first >= previousNode->content.first)
				{
					if (_node->right && _node->content.first > previousNode->content.first)
						_node = _node->right;
					else
						_node = _node->parent;
				}
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator res(*this);

				while (_node->content.first >= res->first)
				{
					if (_node->right && _node->content.first > res->first)
						_node = _node->right;
					else
						_node = _node->parent;
				}
				return (*this);
			}

			map_iterator& operator--()
			{
				// pointe sur le meme element
				nonConstPointer previousNode = _node;

				while (_node->content.first <= previousNode->content.first)
				{
					if (_node->left && _node->content.first < previousNode->content.first)
						_node = _node->left;
					else
						_node = _node->parent;
				}
				return (*this);
			}

			map_iterator operator--(int)
			{
				map_iterator res(*this);

				while (_node->content.first <= res->content.first)
				{
					if (_node->left && _node->content.first < res->content.first)
						_node = _node->left;
					else
						_node = _node->parent;
				}
				return (*this);
			}

			bool operator==(const map_iterator& it) const	{ return (it._node == _node); }
			bool operator!=(const map_iterator& it) const	{ return (it._node != _node); }

		protected:

			nonConstPointer	_node;
	};
} // namespace ft


#endif