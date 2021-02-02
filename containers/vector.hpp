/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:44:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/02 07:59:01 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>

#include "../iterators/random_access_iterator.hpp"
#include "../iterators/rev_random_access_iterator.hpp"
#include "../templates/stl_like.hpp"

#include <cstdio>

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------ FT::VECTOR ------------------------- *
	*
	* - Coplien form:
	* (constructor):		Construct vector
	* (destructor):			Vector destructor
	* operator=:			Assign content
	*
	* - Iterators:
	* begin:				Return iterator to beginning
	* end:					Return iterator to end
	* rbegin:				Return reverse iterator to reverse beginning
	* rend:					Return reverse iterator to reverse end
	*
	* - Capacity:
	* size:					Return size
	* max_size:				Return maximum size
	* resize:				Change size
	* capacity:				Return size of allocated storage capacity
	* empty:				Test whether vector is empty
	* reserve:				Request a change in capacity
	*
	* - Element access:
	* operator[]:			Access element
	* at:					Access element
	* front:				Access first element
	* back:					Access last element
	*
	* - Modifiers:
	* assign:				Assign vector content
	* push_back:			Add element at the end
	* pop_back:				Delete last element
	* insert:				Insert elements
	* erase:				Erase elements
	* swap:					Swap content
	* clear:				Clear content
	*
	* - Non-member function overloads:
	* relational operators:	Relational operators for vector
	* swap:					Exchange contents of vectors
	* ------------------------------------------------------------- *
	*/
	
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
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
			
			typedef typename ft::random_iterator<T, false>		iterator;
			typedef typename ft::random_iterator<T, true>		const_iterator;

			typedef typename ft::rev_random_iterator<T, false>	reverse_iterator;
			typedef typename ft::rev_random_iterator<T, true>	const_reverse_iterator;


			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			/**
			*	Default constructor, creates a vector with a size of 0.
			*
			*	@param alloc	The template param used for the allocation
			*/
			explicit vector(const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(0), _capacity(0)
			{
				_vector = _alloc.allocate(_capacity);
			};

			/**
			*	Fill constructor, creates a vector with a size of n and initialized the 
			*	values.
			*
			*	@param n		The number of elements that will be created
			*	@param val		The value used for initialization (value initialized by default)
			*	@param alloc	The template param used for the allocation
			*/
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(n), _capacity(n)
			{
				_vector = _alloc.allocate(_capacity);
				
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_vector[i], val);
			}
							
			/**
			*	Range constructor, creates a vector with a size equal to the range between two
			*	iterators and copy the values of this range to the new elements created.
			*
			*	@param first	An iterator representing first element of the range
			*	@param last		An iterator indicating end of the range (will be excluded and not copied)
			*	@param alloc	The template param used for the allocation
			*/
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
					_alloc(alloc), _size(0)
			{
				InputIterator tmp(first);
				while (tmp++ != last)
					_size++;
				
				_capacity = _size;
				_vector = _alloc.allocate(_capacity);

				for (int i = 0; first != last; ++first, ++i)
					_alloc.construct(&_vector[i], *first);
			}
					
			/**
			*	Copy constructor, creates a vector with the same size and copy/construct
			*	all x values to the new area allocated.
			*	
			*	@param x		The vector that will be copied.
			*/
			vector(const vector& x) :
					_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);
				
				for (ft::pair<int, const_iterator> i(0, x.begin());
						i.second != x.end(); ++i.first, ++i.second)
					_alloc.construct(&_vector[i.first], *i.second);
			}

			/**
			*	Destructor, destroys all the vector's elements and then deallocates vector's
			*	ressources.
			*/
			~vector()
			{
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(&(*it));
				_alloc.deallocate(_vector, _capacity);
			}
			
			/**
			*	Assigns a vector to this vector. Calls the copy constructor to do the
			*	assignment(copy and swap idiom).
			*	
			*	@param x		The vector that will be assigned.
			*/
			vector& operator= (const vector& x)
			{
				vector tmp(x);
				swap(tmp);
				return (*this);
			}


			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */
			
			/**
			*	@return		An iterator pointing at the first element of the vector.
			*/
			iterator		begin()					{ return iterator(_vector); }
			
			/**
			*	@return		A const_iterator pointing at the first element of the vector.
			*/
			const_iterator	begin() const			{ return const_iterator(_vector); }
			
			/**
			*	@return		An iterator pointing after the last element of the vector. Access this
			*				iterator will result in undefined behavior.
			*/
			iterator		end()					{ return iterator(_vector + _size); }

			/**
			*	@return		A const_iterator pointing after the last element of the vector. Access this
			*				iterator will result in undefined behavior.
			*/
			const_iterator	end() const				{ return const_iterator(_vector + _size); }

			/**
			*	@return		A reverse_iterator pointing at the last element of the vector.
			*/
			reverse_iterator rbegin()				{ return reverse_iterator(_vector + _size - 1); }

			/**
			*	@return		A const_reverse_iterator pointing at the last element of the vector.
			*/
			const_reverse_iterator rbegin() const	{ return const_reverse_iterator(_vector + _size - 1); }
			
			/**
			*	@return		A reverse_iterator pointing before the first element of the vector. Access this
			*				iterator will result in undefined behavior.
			*/
			reverse_iterator rend()					{ return reverse_iterator(_vector - 1); }
			
			/**
			*	@return		A const_reverse_iterator pointing before the first element of the vector. Access
			*				this iterator will result in undefined behavior.
			*/
			const_reverse_iterator rend() const		{ return const_reverse_iterator(_vector - 1); }
		

			/* ------------------------------------------------------------- */
			/* -------------------------- CAPACITY ------------------------- */
			
			/**
			*	@return		The size of the vector.
			*/
			size_type		size() const		{ return _size; }
			
			
			/**
			*	@return		The max possible size to be allocated.
			*/
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}
			
			/**
			*	Resizes the vector so that it contains n elements. If the capacity isn't 
			*	enough, a reallocation will happen. 
			*	 
			*	@param n	The number of elements that the vector will contain after beeing resized.
			*	@param val	If new elements need to be added, they will be initialize with val
			*				(value initialize by default).
			*/
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
					reallocateVec(n);
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			/**
			*	@return		The actual size of the capacity allocated (in number of possible elements
			*				than the vector can contain).
			*/
			size_type		capacity() const	{ return _capacity; }

			/**
			*	@return		True if the vector' size is equal to 0.
			*/
			bool			empty() const		{ return _size == 0; }

			/**
			*	Requests that the vector capacity be at least enough to contain n elements. If the
			*	actual capacity is greater than n, nothing happen. If the capacity requested 
			*	is > than max size, a lenght_error exception is thrown.
			*	 
			*	@param n	The new capacity to be allocated.
			*/
			void			reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				if (n > _capacity)
					reallocateVec(n);
			}


			/* ------------------------------------------------------------- */
			/* ---------------------- ELEMENTS ACCESS ---------------------- */
			
			/**
			*	Access an element at n index. Undefined behavior if n is outside 
			*	vector's range.
			*	
			*	@return		A reference to the element at n index.
			*/
			reference operator[] (size_type n)				{ return _vector[n]; }
			
			/**
			*	Access an element at n index. Undefined behavior if n is outside 
			*	vector's range.
			*	
			*	@return		A const reference to the element at n index.
			*/
			const_reference operator[] (size_type n) const	{ return _vector[n]; }
			
			/**
			*	Access an element at n index. If n is outside vector's range, throw an 
			*	out_of_range exception.
			*	
			*	@return		A reference to the element at n index.
			*/
			reference at(size_type n)
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}

			/**
			*	Access an element at n index. If n is outside vector's range, throw an 
			*	out_of_range exception.
			*	
			*	@return		A const reference to the element at n index.
			*/
			const_reference at(size_type n) const
			{
				if (!(n < _size))
					throw std::out_of_range("vector");
				return _vector[n];
			}
			
			
			/**
			*	Access first vector's element. Undefined behavior if the vector is empty.
			*	
			*	@return		A reference to the first vector's element.
			*/
			reference front()								{ return _vector[0]; }
			
			/**
			*	Access first vector's element. Undefined behavior if the vector is empty.
			*	
			*	@return		A const reference to the first vector's element.
			*/
			const_reference front() const					{ return _vector[0]; }
			
			/**
			*	Access last vector's element. Undefined behavior if the vector is empty.
			*	
			*	@return		A reference to the last vector's element.
			*/
			reference back()								{ return _vector[_size - 1]; }

			/**
			*	Access last vector's element. Undefined behavior if the vector is empty.
			*	
			*	@return		A const reference to the last vector's element.
			*/
			const_reference back() const					{ return _vector[_size - 1]; }


			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */
			
			/**
			*	Assigns new contents to the vector, replacing its current content, 
			*	and modifying its size accordingly. The new contents are elements constructed 
			*	from each of the elements in the range between first and last iterators.
			*	
			*	@param first	An iterator pointing at the beginning of the range (will be included).
			*	@param last		An iterator pointing at the end of the range (will not be included)
			*/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				// Allocating more storage only if actual capacity isn't enough
				if (static_cast<size_type>(last - first) > _capacity)
					reallocateVec(static_cast<size_type>(last - first));
				
				size_type i = 0;
				for (; first != last; ++i, ++first)
					_alloc.construct(&_vector[i], *first);
				_size = i;
			}
			
			/**
			*	Assigns new contents to the vector, replacing its current content, 
			*	and modifying its size accordingly.
			*	
			*	@param n	Number of new elements constructed.
			*	@param val	Each new elements will be copy constructed from val.
			*/	
			void assign (size_type n, const value_type& val)
			{
				// Allocating more storage only if actual capacity isn't enough
				if (n > _capacity)
					reallocateVec(n);
					
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&_vector[i], val);
				_size = n;
			}
			
			/**
			*	Adds a new element at the end of the vector, after its current last element.
			*	Size is increased and a reallocation happen if actual capacity isn't enough.
			*
			*	@param val	The new element will be copy constructed from val.
			*/
			void push_back (const value_type& val)
			{
				if (_size + 1 > _capacity)
					reallocateVec(!_capacity ? 1 : _capacity * 2);
				_alloc.construct(&_vector[_size++], val);
			}

			/**
			*	Removes the last element in the vector, reducing the container size by one.
			*	This destroys the removed element.
			*/
			void pop_back()
			{
				if (_size)
					_alloc.destroy(&_vector[_size-- - 1]);
			}
			
			/**
			*	Inserts 1 element with a value of val at a position, and increases the vector' size.
			*	A reallocation will occured only if vector's capacity isn't enough.
			*
			*	@param position	The element will be inserted just before this position. All elements
			*					after this position will be moved of a len of 1.
			*	@param val		Value of the element inserted.
			*	@return			An iterator on the newly element inserted.
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
			
			/**
			*	Inserts n elements with a value of val at a position, and increases the vector' size.
			*	A reallocation will occured only if vector's capacity isn't enough.
			*
			*	@param position	Elements will be inserted just before this position. All elements
			*					after this position will be moved of a len of n.
			*	@param n		Number of elements to be inserted.
			*	@param val		Value of the elements inserted.
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
					moveElementsToTheRight(newPosition, n);
				
				// Constructing n new elements from val
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), val);
				_size += n;
			}

			/**
			*	Inserts all elements between first and last, and increases the vector' size.
			*	A reallocation will occured only if vector's capacity isn't enough.
			*
			*	@param position	Elements will be inserted just before this position. All elements
			*					after this position will be moved of the range' size.
			*	@param first	An iterator pointing to the range's beginning (will be include).
			*	@param last		An iterator pointing to the range's end (will not be include).
			*/	
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, 
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
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
					moveElementsToTheRight(newPosition, n);

				// Constructing n new elements from the iterator's range
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(&(*newPosition++), *first++);
				_size += n;
			}

			/**
			*	Removes from the vector a single element and reduces vector' size by 1.
			*	Erasing elements other than vector.end() will occured a reallocation.
			*
			*	@param position	The element that will erased. The element's range past this position
			*					will be moved to this position.
			*	@return			An iterator pointing to the new location of the element that follows 
								the element erased by the function call.
			*/
			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}
			
			/**
			*	Removes from the vector all elements between first and last, and reduces vector' size.
			*	Erasing elements other than from vector.end() to vector.end() will occured a reallocation.
			*
			*	@param first	The beginning of the range to erase (will be include).
			*	@param last		The end of the range to erase (will not be include). The element's range
			*					past this position will be moved to this first position.
			*	@return			An iterator pointing to the new location of the element that follows 
			*					the elements' range erased by the function call.
			*/
			iterator erase (iterator first, iterator last)
			{
				if (first == end() || first == last)
					return first;
				
				// In case of a realloc, iterators will be invalited because _vector
				// points to another allocated area so we need to save the index array
				// where first is pointing to create a new iterator after the reallocation
				difference_type index = first - begin();
				
				// If there is elements after the iterators range, we need to move them at first position
				if (last < end())
				{
					moveElementsToTheLeft(first, last);
					_size -= static_cast<size_type>(last - first);
				}
				else
				{
					size_type newSize = _size - static_cast<size_type>(last - first);
					while (_size != newSize)
						pop_back();
				}
				
				return iterator(&_vector[index]);
			}

			/**
			*	Swaps a vector with the content of this one.
			*
			*	@param x	The vector to be swapped.
			*/
			void swap (vector& x)
			{
				swap(_alloc, x._alloc);
				swap(_vector, x._vector);
				swap(_size, x._size);
				swap(_capacity, x._capacity);
			}

			/**
			*	Removes all elements from the vector (which are destroyed), leaving the 
			*	container with a size of 0.
			*/
			void clear()
			{
				while (_size)
					pop_back();
			}


			/* ------------------------------------------------------------- */
			/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

			/**
			*	@return		True if the 2 vectors have same size and same content.
			*/
			friend bool operator==(const vector& lhs, const vector& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;

				for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
						it.first != lhs.end(); ++it.first, ++it.second)
					if (*(it.first) != *(it.second))
						return false;
				return true;
			}

			/**
			*	@return		True if the 2 vectors have different size or different content.
			*/
			friend bool operator!=(const vector& lhs, const vector& rhs)	{ return !(lhs == rhs); }
			
			/**
			*	Compares the elements sequentially using operator< and stopping at the 
			*	first occurrence.
			*
			*	@return		True if all lhs' elements are < to rhs' elements, or if
			*				lhs' content == rhs' content and lhs' size < rhs' size.
			*/
			friend bool operator<(const vector& lhs, const vector& rhs)
			{
				for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
						it.first != lhs.end() && it.second != rhs.end(); ++it.first, ++it.second)
					if (*(it.first) < *(it.second))
						return true;
				return (lhs.size() < rhs.size());
			}

			/**
			*	Uses operator< to compare the 2 vectors (rhs < lhs)
			*
			*	@return		True if all lhs' elements are > to all rhs' elements, or if
			*				lhs' content == rhs' content and lhs' size > rhs' size.
			*/
			friend bool operator>(const vector& lhs, const vector& rhs)		{ return rhs < lhs; }

			/**
			*	Uses operator< to compare the 2 vectors !(rhs < lhs)
			*
			*	@return		True if all lhs' elements are <= to all rhs' elements, or if
			*				lhs' content == rhs' content and lhs' size <= rhs' size.
			*/
			friend bool operator<=(const vector& lhs, const vector& rhs)	{ return !(rhs < lhs); }
			
			/**
			*	Uses operator< to compare the 2 vectors !(lhs < rhs)
			*
			*	@return		True if all lhs' elements are >= to all rhs' elements, or if
			*				lhs' content == rhs' content and lhs' size >= rhs' size.
			*/
			friend bool operator>=(const vector& lhs, const vector& rhs)	{ return !(lhs < rhs); }

			/**
			*	Swaps the content of two vectors.
			*
			*	@param x	Will be swap with y.
			*	@param y	Will be swap with x.
			*/
			friend void swap (vector& x, vector& y)							{ x.swap(y); }
			
			
		private:	
		
			Alloc				_alloc;			// Copy of allocator_type object
			pointer				_vector;		// Pointer on an array of T values
			size_type			_size;			// Number of T values inside the vector
			size_type			_capacity;		// Capacity allocated (can be greater than size)


			/* ------------------------------------------------------------- */
			/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */

			/**
			*	Reallocates a vector with a new capacity, and copy/construct the previous
			*	one using the allocator. Then call destruct the previous one with the destructor.
			*
			*	@param newCapacity		The new that will be allocated by the allocator.
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

			/**
			*	Move to the right all elements from a certain position until the end
			*	of the array. Each element will be constructed/copied to his new position,
			*	then destructed at his previous position.
			*
			*	@param pos		Indicates first element to move. All elements at his right will be moved too.
			*	@param lenMov	The len of the movement for each element.
			*/
			void moveElementsToTheRight(iterator pos, size_type lenMov)
			{
				// Starting from the end, until it meets pos iterator
				for (ft::pair<iterator, iterator> it(end() - 1, end());
					it.second != pos; --it.first, --it.second)
				{
					_alloc.construct(&(*(it.first + lenMov)), *it.first);
					_alloc.destroy(&(*it.first));
				}
			}

			/**
			*	Move to the left all elements from a certain position until the end 
			*	of the array. Each element will be constructed/copied to his new position,
			*	and destructed at his previous position.
			*
			*	@param first	Iterator pointing to the new range's beginning, elements will be
			*					moved to this position.
			*	@param last		Iterator pointing to the first element to move. Every element after
			*					this one until the end will be moved.
			*/
			void moveElementsToTheLeft(iterator first, iterator last)
			{
				for (; first != end(); ++first, ++last)
				{
					// Destructing the previous element to replace it by a new one.
					// First will destroy all the element until the end.
					_alloc.destroy(&(*first));
					
					// Moving a new element to the left at first position, only if there is
					// still element to move
					if (last < end())
						_alloc.construct(&(*(first)), *last);
				}
			}
			
	}; // class vector

} // namespace ft

#endif