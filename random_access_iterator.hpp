/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/05 17:08:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include <memory>

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class random_iterator
	{
		public:

			/* -------- ALIASES -------- */

			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::size_type size_type;
			typedef std::random_access_iterator_tag iterator_category;


			/* -------- CONSTRUCTORS / DESTRUCTOR / ASSIGNMENT -------- */

			random_iterator() : _val() {}
			random_iterator(value_type& val) : _val(&val) {}
			random_iterator(const random_iterator& copy) : _val(copy._val) {};
			~random_iterator() {}

			random_iterator& operator=(const random_iterator& assign)
			{
				if (this != &assign)
					_val = assign._val;
				return (*this);
			}


			/* -------- OPERATORS -------- */

			// INTPUT / OUTPUT / FORWARD / BIDIRECTIONNAL ITERATOR PART

			reference operator*()			{ return (*_val); }
			pointer operator->() const		{ return (_val); }
			
			bool operator==(const random_iterator& it) const	{ return (it._val == _val); }
			bool operator!=(const random_iterator& it) const	{ return (it._val != _val); }
			bool operator<(const random_iterator& it) const		{ return (it._val > _val); }
			bool operator>(const random_iterator& it) const		{ return (it._val < _val); }
			bool operator<=(const random_iterator& it) const	{ return (it._val >= _val); }
			bool operator>=(const random_iterator& it) const	{ return (it._val <= _val); }

			random_iterator& operator++()		{ ++_val; return (*this); }
			random_iterator operator++(int)		{ random_iterator res(*this); ++(*this); return (res); };
			random_iterator& operator--()		{ --_val; return (*this); }
			random_iterator operator--(int)		{ random_iterator res(*this); --(*this); return (res); };
			
			
			// RANDOM ACCESS ITERATOR PART
			
			random_iterator& operator+=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					++_val;
				return (*this);
			}

			random_iterator operator+(size_type nb) const
			{
				random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					++it._val;
				return (it);
			}
			
			random_iterator& operator-=(size_type nb)
			{
				for (size_type i = 0; i < nb; i++)
					--_val;
				return (*this);
			}

			random_iterator operator-(size_type nb) const
			{
				random_iterator it(*this);
				
				for (size_type i = 0; i < nb; i++)
					--it._val;
				return (it);
			}

			reference operator[](size_type nb) const
			{
				value_type* tmp;

				tmp = _val;
				for (size_type i = 0; i < nb; i++)
					++tmp;
				return (*tmp);
			}

			difference_type operator-(random_iterator it) const
			{
				return (_val - it._val);
			}
			

			/* -------- FRIEND OPERATORS -------- */		
			
			friend random_iterator operator+(size_type nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt += nb);
			}

			friend random_iterator operator-(size_type nb, const random_iterator& it)
			{
				random_iterator newIt(it);
				return (newIt -= nb);
			}


		private:

			value_type*	_val;
	};
	
} // namespace ft

#endif