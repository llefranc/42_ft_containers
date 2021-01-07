/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/07 16:53:37 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>

#include "random_access_iterator.hpp"

#define EXTRA_MEM 10

namespace ft
{
	
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			/* -------- ALIASES -------- */
			
			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			// !!!!! FAIRE LES TYPEDEF DES ITERATEURS
			typedef typename ft::random_iterator<T>				iterator;
			
			typedef	typename allocator_type::difference_type	difference_type;
			typedef	typename allocator_type::size_type			size_type;


			/* -------- CONSTRUCTORS -------- */

			// default (1)
			explicit vector(const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(0), _capacity(EXTRA_MEM)
			{
				_vector = _alloc.allocate(_capacity);
				_end = _vector + _size;
			};

			// fill (2)
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(n), _capacity(n + EXTRA_MEM)
			{
				_vector = _alloc.allocate(_capacity);
				_end = _vector + _size;
				
				for (size_type i = 0; i < _size; ++i)
					_vector[i] = val;
			}
							
			// FAIRE LE FUCKING TRAITTTTT
			// range (3) 
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 		const allocator_type& alloc = allocator_type()) :
			// 		_alloc(alloc)
			// {
			// 	_size = last - first;
			// 	_capacity = _size + EXTRA_MEM;

			// 	_vector = _alloc.allocate(_capacity);
			// 	_end = _vector + _size;

			// 	for (iterator it = begin(); first != last; ++first, ++it)
			// 		*it = *first;
			// }
					
			// copy (4)
			vector (const vector& x) :
					_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);
				_end = _vector + _size;
				
				for (std::pair<iterator, iterator> i(begin(), x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					*i.first = *i.second;
			}

			/* -------- METHODS -------- */
			iterator	begin() const		{ return (iterator(_vector)); }
			iterator	end() const			{ return (iterator(_end)); }
			size_type	size() const		{ return (_size); }
		
			/* -------- HELENE PARTIE <3 -------- */

			/* -------- FIN HELENE PARTIE :'( -------- */
			
			// void swap (vector& x)
			// {				
			// 	std::swap(_size, x._size);
			// 	std::swap(_capacity, x._capacity);
			// 	std::swap(_alloc, x._alloc);
			// 	if (_size > x._size)
			// 		vector vec(*this);
			// 	else
			// 		vector vec(x);
			// }

		private:	
		
			allocator_type		_alloc;			// Copy of allocator_type object
			pointer				_vector;		// Pointer on an array of T values
			pointer				_end;			// Pointer at the end of T values array
			size_type			_size;			// Number of T values inside the vector
			size_type			_capacity;		// Capacity allocated (can be greater than size)
	};
	

	/* -------- CONSTRUCTORS -------- */

	// default (1)
	// template <typename T, class Alloc>
	// vector<T, Alloc>::vector(const allocator_type& alloc) :
	// 		_alloc(alloc), _size(0), _capacity(0)
	// {
	// 	_vector = _alloc.allocate(_size);
	// }

	// // fill (2)
	// template <typename T, class Alloc>
	// vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) :
	// 		_alloc(alloc), _size(n), _capacity(n)
	// {
	// 	_vector = _alloc.allocate(_size);
	// 	for (size_type i = 0; i < _size; ++i)
	// 		_vector[i] = val;

	// 	for (size_type i = 0; i < _size; ++i)
	// 		std::cout << _vector[i] << "\n";
	// }

	// /* -------- METHODS -------- */
	
	// template <typename T, class Alloc>
	// ft::vector<T, Alloc>::iterator vector<T, Alloc>::begin() const
	// {
	// 	return (iterator(*_vector));
	// }

} // namespace ft


#endif