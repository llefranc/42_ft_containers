/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 11:05:03 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include <memory>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "../iterators/random_access_iterator.hpp"
#include "../templates/stl_like.hpp"

#include <cstdio>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			/* -------------------------- ALIASES -------------------------- */
			
			typedef	T												value_type;
			typedef	Alloc											allocator_type;
			typedef	ptrdiff_t										difference_type;
			typedef	size_t											size_type;

			typedef	T&												reference;
			typedef	const T&										const_reference;
			typedef	T*												pointer;
			typedef	const T*										const_pointer;
			
			typedef typename ft::random_iterator<T, false, Alloc>	iterator;
			typedef typename ft::random_iterator<T, true, Alloc>	const_iterator;


			/* ------------------------ CONSTRUCTORS ----------------------- */

			/*
			** Default constructor, creates a vector with a size of 0
			**
			** @param alloc		The template param used for the allocation
			*/
			explicit vector(const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(0), _capacity(0)
			{
				_vector = _alloc.allocate(_capacity);
			};

			/*
			** Fill constructor, creates a vector with a size of n and initialized the 
			** values.
			**
			** @param n			The number of elements that will be created
			** @param val		The value used for initialization (value initialized by default)
			** @param alloc		The template param used for the allocation
			*/
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(n), _capacity(n)
			{
				_vector = _alloc.allocate(_capacity);
				
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_vector[i], val);
			}
							
			/*
			** Range constructor, creates a vector with a size equal to the range between two
			** iterators and copy the values of this range to the new elements created.
			**
			** @param first		An iterator representing first element of the range
			** @param last		An iterator indicating end of the range (will be excluded and not copied)
			** @param alloc		The template param used for the allocation
			*/
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<InputIterator>::type* = 0) :
					_alloc(alloc)
			{
				_size = last - first;
				_capacity = _size;
				_vector = _alloc.allocate(_capacity);

				for (int i = 0; first != last; ++first, ++i)
					_alloc.construct(&_vector[i], *first);
			}
					
			/*
			** Copy constructor, creates a vector with a size equal vector x size and copy
			** all x values to the new elements created.
			**
			** @param x			The vector that will be copied.
			*/
			vector(const vector& x) :
					_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);
				for (ft::pair<int, const_iterator> i(0, x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					_alloc.construct(&_vector[i.first], *i.second);
			}

			
			/* ------------------------- DESTRUCTOR ------------------------ */

			/*
			** Destructor, destroy all the vector's elements and then deallocates vector's
			** ressources.
			*/
			~vector()
			{
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(&(*it));
				_alloc.deallocate(_vector, _capacity);
			}
			

			/* ------------------------- OPERATOR= ------------------------- */
			
			vector& operator= (const vector& x)
			{
				vector tmp(x);
				swap(tmp);
				return (*this);
			}


			/* ------------------------- ITERATORS ------------------------- */
			
			iterator		begin()				{ return iterator(_vector); }
			const_iterator	begin() const		{ return const_iterator(_vector); }
			iterator		end()				{ return iterator(_vector + _size); }
			const_iterator	end() const			{ return const_iterator(_vector + _size); }


			/* -------------------------- CAPACITY ------------------------- */
			
			size_type		size() const		{ return _size; }
			
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
					reallocateVec(n);
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			size_type		capacity() const	{ return _capacity; }
			bool			empty() const		{ return _size == 0; }

			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				if (n > _capacity)
					reallocateVec(n);
			}

			/* ---------------------- ELEMENTS ACCESS ---------------------- */
			reference operator[] (size_type n)				{ return _vector[n]; }
			const_reference operator[] (size_type n) const	{ return _vector[n]; }
			
			reference at(size_type n)
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}

			const_reference at(size_type n) const
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}
			
			reference front()								{ return _vector[0]; }
			const_reference front() const					{ return _vector[0]; }
			
			reference back()								{ return _vector[_size - 1]; }
			const_reference back() const					{ return _vector[_size - 1]; }


			/* ------------------------- MODIFIERS ------------------------- */
 			// range (1)	
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				// Allocating more storage only if actual capacity isn't enough
				if (static_cast<size_type>(last - first) > _capacity)
					reallocateVec(static_cast<size_type>(last - first));
				
				size_type i = 0;
				for (; first != last; ++i, ++first)
					_alloc.construct(&_vector[i], *first);
				_size = i;
			}
			
			// fill (2)	
			void assign (size_type n, const value_type& val)
			{
				// Allocating more storage only if actual capacity isn't enough
				if (n > _capacity)
					reallocateVec(n);
					
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_vector[i], val);
				_size = n;
			}
			
			void push_back (const value_type& val)
			{
				if (_size + 1 > _capacity)
					reallocateVec(!_capacity ? _capacity + 1 : _capacity * 2);
				_alloc.construct(&_vector[_size++], val);
			}

			void pop_back()
			{
				if (_size)
					_alloc.destroy(&_vector[_size-- - 1]);
			}
			
			/*
			** Inserts 1 elements with a value of val at a position, and increases the vector' size.
			** A reallocation will occured only if vector's capacity isn't enough.
			**
			** @param position	The element will be inserted just before this position. All elements
			**					after this position will be moved of a len of 1.
			** @param val		Value of the element inserted.
			** @return			An iterator on the newly element inserted.
			*/
			iterator insert (iterator position, const value_type& val)
			{
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				insert(position, 1, val);
				return iterator(&_vector[index]);
			}
			
			/*
			** Inserts n elements with a value of val at a position, and increases the vector' size.
			** A reallocation will occured only if vector's capacity isn't enough.
			**
			** @param position	Elements will be inserted just before this position. All elements
			**					after this position will be moved of a len of n.
			** @param n			Number of elements to be inserted.
			** @param val		Value of the elements inserted.
			*/
			void insert (iterator position, size_type n, const value_type& val)
			{
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);
				
				// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
				iterator newPosition(&_vector[index]);
				
				// Moving at newPosition + n all elements after newPosition
				if (newPosition != end())
					moveElements(newPosition, n);
				
				// Constructing n new elements from val
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), val);
				_size += n;
			}

			// range (3)	
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, 
						typename ft::enable_if<InputIterator>::type* = 0)
			{
				// Counting number of elements to add
				size_type n = 0;
				InputIterator tmp(first);
				while (tmp++ != last)
					++n;
				
				// In case of a realloc, position will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where position iterator is pointing to create a new one after the reallocation
				difference_type index = position - begin();
				
				if (_size + n > _capacity)
					reallocateVec(_capacity + n);

				// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
				iterator newPosition(&_vector[index]);
				
				// Moving at newPosition + n all elements after newPosition
				if (newPosition != end())
					moveElements(newPosition, n);

				// Constructing n new elements from the iterator's range
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), *first++);
				_size += n;
			}

			
			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			/*
			** Swaps a vector with the content of this one.
			**
			** @param x		The vector to be swapped.
			*/
			void swap (vector& x)
			{
				swap(_alloc, x._alloc);
				swap(_vector, x._vector);
				swap(_size, x._size);
				swap(_capacity, x._capacity);
			}

			void clear()
			{
				while (_size)
					pop_back();
			}

			
			/* --------------- NON MEMBER FUNCTION OVERLOADS --------------- */
			// (1)	
			// template <class T, class Alloc>
			// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// (2)	
			// template <class T, class Alloc>
			// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// (3)	
			// template <class T, class Alloc>
			// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// (4)	
			// template <class T, class Alloc>
			// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// (5)	
			// template <class T, class Alloc>
			// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// (6)	
			// template <class T, class Alloc>
			// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			// template <class T, class Alloc>
			// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
			
		private:	
		
			Alloc				_alloc;			// Copy of allocator_type object
			pointer				_vector;		// Pointer on an array of T values
			size_type			_size;			// Number of T values inside the vector
			size_type			_capacity;		// Capacity allocated (can be greater than size)

			/*
			** Reallocates a vector with a new capacity, and copy/construct the previous
			** one using the allocator. Then call destruct the previous one with the destructor.
			**
			** @param newCapacity		The new that will be allocated by the allocator.
			*/
			void reallocateVec(size_type newCapacity)
			{
				pointer tmp = _alloc.allocate(newCapacity);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&tmp[i], _vector[i]);

				this->~vector();
				_capacity = newCapacity;
				_vector = tmp;
			}

			/*
			** Swaps two variables.
			**
			** @param a		Will be swap with b.
			** @param b		Will be swap with a.
			*/
			template <typename U>
			void swap(U& a, U&b)
			{
				U tmp = a;
				a = b;
				b = tmp;
			}

			/*
			** Move to the right on an array all elements (from a position until the end
			** of the array). Each element will be constructed/copied to his new position,
			** then destructed at his previous position.
			**
			** @param pos		Indicates first element to move. All elements at his right will be moved too.
			** @param lenMov	The len of the movement for each element.
			*/
			void moveElements(iterator pos, size_type lenMov)
			{
				// Starting from the end, until it meets pos iterator
				for (ft::pair<iterator, iterator> it(end() - 1, end());
					it.second != pos; --it.first, --it.second)
				{
					_alloc.construct(&(*(it.first + lenMov)), *it.first);
					_alloc.destroy(&(*it.first));
				}
			}
	};
}

#endif