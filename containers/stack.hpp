/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/02 19:33:00 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
			
			
			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */
			
			explicit stack (const container_type& ctnr = container_type()) :
					_ctnr(ctnr) {}
			
			stack(const stack& other) :
					_ctnr(other._ctnr) {}
				
			~stack() {}
		
			stack& operator=(const stack& other)
			{
				// _ctnr.operator=(static_cast<std::deque<T> >(other));
				return *this;
			}

			bool empty() const	{ return _ctnr.empty(); }
			
		private:

			container_type	_ctnr;
	}; // class stack
	
} // namespace ft

#endif