/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/05 12:30:34 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>

#include "random_access_iterator.hpp"

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

			// class iterator
			// {
			// 	public:
				
			// 		typedef typename Alloc::difference_type difference_type;
			// 		typedef typename Alloc::value_type value_type;
			// 		typedef typename Alloc::reference reference;
			// 		typedef typename Alloc::pointer pointer;
			// 		typedef std::random_access_iterator_tag iterator_category;
				
			// 		iterator(value_type val) : _val(val) {}
			// 		~iterator() {}

			// 		reference operator*() { return (_val); }

			// 	private:

			// 		value_type	_val;
			// };

			/* -------- CONSTRUCTORS -------- */

			// default (1)
			explicit vector(const allocator_type& alloc = allocator_type());

			// fill (2)
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());
							
			// range (3)
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 		const allocator_type& alloc = allocator_type());
					
			// // copy (4)
			// vector (const vector& x);

			/* -------- METHODS -------- */
			// typename vector<T, Alloc>::iterator begin () const;
			iterator begin () const
			{
				return (iterator(*_vector));
			}
		
		private:	
		
			allocator_type		_alloc;			// Copy of allocator_type object
			pointer				_vector;		// Pointer on an array of T values
			size_type			_size;			// Number of T values inside the vector
			size_type			_capacity;		// Capacity allocated (can be greater than size)
	};
	

	/* -------- CONSTRUCTORS -------- */

	// default (1)
	template <typename T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc) :
			_alloc(alloc), _size(0), _capacity(0)
	{
		_vector = _alloc.allocate(_size);
	}

	// fill (2)
	template <typename T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) :
			_alloc(alloc), _size(n), _capacity(n)
	{
		_vector = _alloc.allocate(_size);
		for (size_type i = 0; i < _size; ++i)
			_vector[i] = val;

		for (size_type i = 0; i < _size; ++i)
			std::cout << _vector[i] << "\n";
	}

	/* -------- METHODS -------- */
	// template <typename T, class Alloc>
	// typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() const
	// {
	// 	return (vector<T, Alloc>::iterator());
	// }
	// template <typename T, class Alloc>
	// iterator vector<T, Alloc>::begin() const
	// {
	// 	return (iterator(*_vector));
	// }

} // namespace ft


#endif