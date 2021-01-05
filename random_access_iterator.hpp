/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:15:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/05 12:23:31 by llefranc         ###   ########.fr       */
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

			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef std::random_access_iterator_tag iterator_category;

			random_iterator(value_type val) : _val(val) {}
			~random_iterator() {}

			reference operator*() { return (_val); }

		private:

			value_type	_val;
	};
} // namespace ft

#endif