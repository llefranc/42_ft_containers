/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/22 16:41:25 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

#include "../iterators/list_iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class list
	{
		private:

			struct Node
			{
				T		data;
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

			// typedef typename ft::rev_list_iterator<T, false>	reverse_iterator;
			// typedef typename ft::rev_list_iterator<T, true>	const_reverse_iterator;

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			// default (1)	
			explicit list (const allocator_type& alloc = allocator_type()) :
					_size(0)
			{
				(void)alloc;
				newEndNode();
			}
			
			// fill (2)	
			explicit list (size_type n, const value_type& val = value_type(),
			                const allocator_type& alloc = allocator_type()) :
					_size(0)
			{
				(void)alloc;
				newEndNode();

				while (_size < n)
					push_back(val);
			}

			// range (3)	
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
					_size(0)
			{
				(void)alloc;
				newEndNode();

				for (; first != last; ++first)
					push_back(*first);
			}
			
			// copy (4)	
			list (const list& x) :
					_size(x._size)
			{
				newEndNode();

				for (const_iterator it = x.begin(); it != x.end(); ++it)
					push_back(*it);
			}

			// ~list()
			// {
			// 	while (_size-- > 0)

			// }

			//copy (1)	list& operator= (const list& x);

			iterator begin()		{ return !_size ? iterator(_endList) : iterator(_endList->next); }
			const_iterator begin() const	{ return !_size ? iterator(_endList) : iterator(_endList->next); }

			iterator end()			{ return iterator(_endList); }
			const_iterator end() const		{ return const_iterator(_endList); }

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;

			//  reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// bool empty() const;

			//size_type size() const;
			// size_type max_size() const;

			// reference front();
			// const_reference front() const;

			// reference back();
			// const_reference back() const;

			// range (1)	
			// template <class InputIterator>
			//   void assign (InputIterator first, InputIterator last);
			// fill (2)	
			// void assign (size_type n, const value_type& val);

			// void push_front (const value_type& val);

			// void pop_front();

			void push_back (const value_type& val)
			{
				Node* tmp = new Node;
				tmp->data = val;

				tmp->prev = _endList->prev;
				tmp->next = _endList;
				_endList->prev->next = tmp;
				_endList->prev = tmp;
				
				++_size;
			}
	
			// void pop_back();


			// single element (1)	
			// iterator insert (iterator position, const value_type& val);
			// fill (2)	
			//     void insert (iterator position, size_type n, const value_type& val);
			// range (3)	
			// template <class InputIterator>
			//     void insert (iterator position, InputIterator first, InputIterator last);

			// 	iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			// void swap (list& x);

			// void resize (size_type n, value_type val = value_type());
			// void clear();
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

			//   void reverse();

			//   (1)	
			// template <class T, class Alloc>
			//   bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (2)	
			// template <class T, class Alloc>
			//   bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (3)	
			// template <class T, class Alloc>
			//   bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (4)	
			// template <class T, class Alloc>
			//   bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (5)	
			// template <class T, class Alloc>
			//   bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
			// (6)	
			// template <class T, class Alloc>
			//   bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

			//   template <class T, class Alloc>
			//   void swap (list<T,Alloc>& x, list<T,Alloc>& y);

		private:

			Node*		_endList;
			size_type	_size;
			
			void newEndNode()
			{
				_endList = new Node;
				_endList->next = _endList;
				_endList->prev = _endList;			
			}
	}; // class list
	
} // namespace ft

#endif