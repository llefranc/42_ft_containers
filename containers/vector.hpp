/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/12 17:59:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include <memory>
#include <iostream>

#include "../iterators/random_access_iterator.hpp"
#include "../templates/stl_like.hpp"

#define EXTRA_MEM 10

namespace ft
{
	template <typename T>
	class vector
	{
		public:

			/* -------------------------- ALIASES -------------------------- */
			
			typedef	T										value_type;
			typedef	ptrdiff_t								difference_type;
			typedef	size_t									size_type;

			typedef	T&										reference;
			typedef	const T&								const_reference;
			typedef	T*										pointer;
			typedef	const T*								const_pointer;
			
			typedef typename ft::random_iterator<T, false>	iterator;
			typedef typename ft::random_iterator<T, true>	const_iterator;


			/* ------------------------ CONSTRUCTORS ----------------------- */

			// default (1)
			explicit vector() :
					_size(0), _capacity(EXTRA_MEM)
			{
				_vector = new T [_capacity];
				_end = _vector + _size;
			};

			// fill (2)
			explicit vector(size_type n, const value_type& val = value_type()) :
					_size(n), _capacity(n + EXTRA_MEM)
			{
				_vector = new T [_capacity];
				_end = _vector + _size;
				
				for (size_type i = 0; i < _size; ++i)
					_vector[i] = val;
			}
							
			// range (3) 
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, typename ft::enable_if<InputIterator>::type* = 0)
			{
				_size = last - first;
				_capacity = _size + EXTRA_MEM;

				_vector = new T [_capacity];
				_end = _vector + _size;

				for (iterator it = begin(); first != last; ++first, ++it)
					*it = *first;
			}
					
			// copy (4)
			vector(const vector& x) :
					_size(x._size), _capacity(x._capacity)
			{
				_vector = new T [_capacity];
				_end = _vector + _size;
				
				for (ft::pair<iterator, iterator> i(begin(), x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					*i.first = *i.second;
			}

			
			/* ------------------------- DESTRUCTOR ------------------------ */

			// ~vector()
			// {
				
			// }

			/* -------------------------- METHODS -------------------------- */
			
			iterator		begin()				{ return iterator(_vector); }
			const_iterator	begin() const		{ return const_iterator(_vector); }
			iterator		end()				{ return iterator(_vector + _size); }
			const_iterator	end() const			{ return const_iterator(_vector + _size); }

			size_type		size() const		{ return _size; }
			// size_type		max_size() const;	{ }
			// void resize (size_type n, value_type val = value_type());
			size_type		capacity() const	{ return _capacity; }

		private:	
		
			pointer				_vector;		// Pointer on an array of T values
			pointer				_end;			// Pointer at the end of T values array
			size_type			_size;			// Number of T values inside the vector
			size_type			_capacity;		// Capacity allocated (can be greater than size)
	};
}

#endif