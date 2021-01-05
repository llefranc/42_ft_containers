/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/05 10:33:52 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>

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
			typedef	typename allocator_type::difference_type	difference_type;
			typedef	typename allocator_type::size_type			size_type;

			/* -------- CONSTRUCTORS -------- */

			// default (1)
			explicit vector(const allocator_type& alloc = allocator_type());

			// fill (2)
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());
			// explicit vector(size_type n, size_type val,
			// 				const allocator_type& alloc = allocator_type());
							
			// range (3)
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 		const allocator_type& alloc = allocator_type());
					
			// // copy (4)
			// vector (const vector& x);
		
		private:	
		
			allocator_type		_alloc;
			pointer				_vector;
			size_type			_size;
			size_type			_capacity;
	};
	
	template <typename T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc) :
			_alloc(alloc), _size(0), _capacity(0)
	{
		_vector = _alloc.allocate(_size);
	}

	template <typename T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) :
			_alloc(alloc), _size(n), _capacity(n)
	{
		_vector = _alloc.allocate(_size);
		for (int i = 0; i < _size; ++i)
			_vector[i] = val;
	}
}


#endif