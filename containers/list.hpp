/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 20:02:59 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

#include "../iterators/list_iterator.hpp"
#include "../iterators/rev_list_iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class list
	{
		private:

			struct Node
			{
				T		content;
				Node*	prev;
				Node*	next;
			};			
		
		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef	ptrdiff_t									difference_type;
			typedef	size_t										size_type;

			typedef	T&											reference;
			typedef	const T&									const_reference;
			typedef	T*											pointer;
			typedef	const T*									const_pointer;
			
			typedef typename ft::list_iterator<T, Node, false>		iterator;
			typedef typename ft::list_iterator<T, Node, true>		const_iterator;

			typedef typename ft::rev_list_iterator<T, Node, false>	reverse_iterator;
			typedef typename ft::rev_list_iterator<T, Node, true>	const_reverse_iterator;

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			// default (1)	
			explicit list (const allocator_type& alloc = allocator_type()) :
					_size(0), _allocT(alloc)
			{
				newEndNode();
			}
			
			// fill (2)	
			explicit list (size_type n, const value_type& val = value_type(),
			                const allocator_type& alloc = allocator_type()) :
					_size(0), _allocT(alloc)
			{
				newEndNode();

				while (_size < n)
					push_back(val);
			}

			// range (3)	
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
					_size(0), _allocT(alloc)
			{
				newEndNode();

				for (; first != last; ++first)
					push_back(*first);
			}
			
			// copy (4)	
			list (const list& x) :
					_size(0), _allocT(x._allocT), _allocNode(x._allocNode)
			{
				newEndNode();

				for (const_iterator it = x.begin(); it != x.end(); ++it)
					push_back(*it);
			}

			~list()
			{
				while (_size > 0)
					pop_back();
				// delete _endList; VERSION SANS ALLOC
				_allocNode.deallocate(_endList, 1);
			}

			// copy (1)
			list& operator= (const list& x)
			{
				list copy(x);
				this->swap(copy);

				return *this;
			}

			iterator begin()				{ return !_size ? iterator(_endList) : iterator(_endList->next); }
			const_iterator begin() const	{ return !_size ? iterator(_endList) : iterator(_endList->next); }

			iterator end()					{ return iterator(_endList); }
			const_iterator end() const		{ return const_iterator(_endList); }

			reverse_iterator rbegin()				{ return !_size ? reverse_iterator(_endList) : reverse_iterator(_endList->prev); }
			const_reverse_iterator rbegin() const	{ return !_size ? const_reverse_iterator(_endList) :
														const_reverse_iterator(_endList->prev); }

			reverse_iterator rend()					{ return reverse_iterator(_endList); }
			const_reverse_iterator rend() const		{ return const_reverse_iterator(_endList); }

			bool empty() const						{ return _size == 0; }

			size_type size() const			{ return _size; }
			
			/**
			*	@return		The max possible size to be allocated.
			*/
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}

			reference front()				{ return _endList->next->content; }
			const_reference front() const 	{ return _endList->next->content; }

			reference back()				{ return _endList->prev->content; }
			const_reference back() const	{ return _endList->prev->content; }

			/**
			*	Assigns new contents to the list, replacing its current content, 
			*	and modifying its size accordingly.The new contents are elements constructed 
			*	from each of the elements in the range between first and last iterators.
			*	
			*	@param n	Number of new elements constructed.
			*	@param val	Each new elements will be copy constructed from val.
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
			*	Assigns new contents to the list, replacing its current content, 
			*	and modifying its size accordingly.
			*	
			*	@param n	Number of new elements constructed.
			*	@param val	Each new elements will be copy constructed from val.
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

			void pop_front()
			{
				if (!_size)
					return ;
				
				Node* tmp = _endList->next;
				_endList->next->next->prev = _endList;
				_endList->next = _endList->next->next;

				// delete tmp; VERSION SANS ALLOC
				deleteNode(tmp);
				--_size;
			}

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
	
			void pop_back()
			{
				if (!_size)
					return ;
				
				Node* tmp = _endList->prev;
				_endList->prev->prev->next = _endList;
				_endList->prev = _endList->prev->prev;

				// delete tmp;  VERSION SANS ALLOC
				deleteNode(tmp);
				--_size;
			}

			/**
			*	Inserts 1 element with a value of val at a position, and increases the list' size.
			*
			*	@param position	The element will be inserted just before this position.
			*	@param val		Value of the element inserted.
			*	@return			An iterator on the newly element inserted.
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
			*	Inserts n elements with a value of val at a position, and increases the list' size.
			*
			*	@param position	Elements will be inserted just before this position.
			*	@param n		Number of elements to be inserted.
			*	@param val		Value of the elements inserted.
			*/
			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n-- > 0)
					position = insert(position, val);
			}
			
			// range (3)	
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				// Inserting in reverse order
				for (ft::pair<reverse_iterator, reverse_iterator> it(last, first);
						it.first != it.second; ++it.first)
					position = insert(position, *it.first);
			}

			// 	iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			void swap (list& x)
			{
				swap(_size, x._size);
				swap(_endList, x._endList);
			}

			void resize (size_type n, value_type val = value_type())
			{
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			void clear()
			{
				while (_size)
					pop_back();
			}

			
			// entire list (1)	
			// void splice (iterator position, list& x);
			// single element (2)	
			// void splice (iterator position, list& x, iterator i);
			// element range (3)	
			// void splice (iterator position, list& x, iterator first, iterator last);
			// void remove (const value_type& val);

			// template <class Predicate>
			//   void remove_if (Predicate pred);

			//   (1)	
			// void unique();
			// (2)	
			// template <class BinaryPredicate>
			//   void unique (BinaryPredicate binary_pred);

			//   (1)	
			//   void merge (list& x);
			// (2)	
			// template <class Compare>
			//   void merge (list& x, Compare comp);

			//   (1)	
			//   void sort();
			// (2)	
			// template <class Compare>
			//   void sort (Compare comp);

			/**
			*	Reverse the list. Each node from the beginning will be inserted from the
			*	end of the list one in front of the other.
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

			//   (1)	
			//   friend bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (2)	
			//   friend bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (3)	
			//   friend bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (4)	
			//   friend bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (5)	
			//   friend bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (6)	
			//   friend bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			friend void swap (list& x, list& y)	{ x.swap(y); }

		private:

			Node*		_endList;
			size_type	_size;
			Alloc		_allocT;
			std::allocator<Node>	_allocNode;

			/* ------------------------------------------------------------- */
			/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
			
			/**
			*	Create a new endNode. Data isn't constructed.
			*/
			void newEndNode()
			{
				// _endList = new Node;			VERSION SANS ALLOCATOR
				// _endList->next = _endList;
				// _endList->prev = _endList;			

				_endList = _allocNode.allocate(1);
				_endList->next = _endList;
				_endList->prev = _endList;			
			}

			/**
			*	Destroy Node's content and then deallocate the Node.
			*
			*	@param toDelete	The Node to destroy and deallocate.
			*/
			void deleteNode(Node *toDelete)
			{
				_allocT.destroy(&toDelete->content);
				_allocNode.deallocate(toDelete, 1);
			}

			/**
			*	Allocate a new Node and copy construct his content from val.
			*
			*	@param val	The content to copy construct.
			*	@return		The Node newly created.
			*/
			Node* createNode(const value_type& val = value_type())
			{
				Node *newNode = _allocNode.allocate(1);
				_allocT.construct(&newNode->content, val);
				
				return newNode;
			}

			/**
			*	Swaps two variables.
			*
			*	@param a		Will be swap with b.
			*	@param b		Will be swap with a.
			*/
			template <typename U>
			void swap(U& a, U&b)
			{
				U tmp = a;
				a = b;
				b = tmp;
			}

	}; // class list
	
} // namespace ft

#endif