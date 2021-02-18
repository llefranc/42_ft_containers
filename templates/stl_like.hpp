/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_like.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/18 14:59:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_LIKE_HPP
#define STL_LIKE_HPP

#include "../iterators/random_access_iterator.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::PAIR -------------------------- *
    *
    * Coplien form:
    * (constructor):        Construct pair
    * (destructor):         Pair destructor
    * operator=:            Assign content
    *
    * Public member variables:
    * T1:                   First pair's member variable.
    * T2:                   Second pair's member variable.
    * ------------------------------------------------------------- *
    */

    template <typename T1, typename T2>
    class pair
    {
        public:
            
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */
            
            /**
            *   Default constructor, value initialized first and second.
            */
            pair() : first(), second() {};
            
            /**
            *   Initialization constructor.
            *
            *   @param a    Will initialize first.
            *   @param b    Will initialize second.
            */
            pair(const T1& a, const T2& b) : first(a), second(b) {};
            
            /**
            *   Copy constructor, creates a pair with the same member variables.
            *
            *   @param copy     The pair that will be copied.
            */
            // pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {};
            
            /**
            *   Copy constructor, creates a pair with the same member variables.
            *
            *   @param copy     The pair that will be copied.
            */
            template <typename U, typename V>
            pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

            ~pair() {};
        
            /**
            *   Assigns a pair to this pair.
            *   
            *   @param assign   The pair that will be assigned.
            */
            pair& operator=(const pair& assign)
            {
                if (this != &assign)
                {
                    first = assign.first;
                    second = assign.second;
                }
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* ------------------ PUBLIC MEMBER VARIABLES ------------------ */
            
            T1 first;
            T2 second;
    };

	/**
    * ------------------------------------------------------------- *
    * ------------------------- FT::LESS -------------------------- *
    */
	template <class T>
	struct less
	{
		typedef T		first_argument_type;
		typedef T		second_argument_type;
		typedef bool	result_type;
		
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

	/**
	* ------------------------------------------------------------- *
    * ---------------------- FT::ALLOCATOR ------------------------ *
    */
   	template <class T>
	class allocator
	{
		public:

			typedef T			value_type;
			typedef T* 			pointer;
			typedef T& 			reference;
			typedef const T*	const_pointer;
			typedef const T&	const_reference;
			typedef size_t		size_type;
			typedef long int	difference_type;

		// allocator() throw() {}
		// allocator(const allocator&) throw() {}
		// template <class U>
		// allocator (const allocator<U>&) throw() {}
		// ~allocator() throw() {}

		allocator() throw() {};

		// copy (2)	
		allocator(const allocator&) throw() {};

		template <class U>
		allocator(const allocator<U>&) throw() {};

		~allocator() throw() {};

		// pointer address(reference x) const				{ return &x; }
		// const_pointer address(const_reference x) const	{ return &x; }

		pointer allocate(size_type n)
		{
			pointer ret;
			size_t size = n * sizeof(value_type);

			try
			{
				ret = reinterpret_cast<pointer>(::operator new(size));
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
			return ret;
		}

		void deallocate (pointer p, size_type n)
		{
			(void)n;
			::operator delete(p);
		}

		void construct(pointer p, const T& v) { new((void*)p)T(v); }
		
    	void destroy(pointer p) { p->~T(); }
		
		template <class T1, class T2>
		friend bool operator== (const allocator<T1>&, const allocator<T2>&) throw()  { return true; }
		template <class T1, class T2>
		friend bool operator!= (const allocator<T1>&, const allocator<T2>&) throw() { return false; }
	};


    /* --------------------------- STD::ENABLE_IF -------------------------- */

    /**
    *   Typedef an int into type only if B is true.
    */

    template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };
        
        
    /* --------------------------- STD::IS_INTEGRAL -------------------------- */

    /**
    *   Value will be true if T is an integral, false otherwise.
    */
    template <typename T>
    struct is_integral { static const bool value = false; };

    template <>
    struct is_integral<bool> { static const bool value = true; };
        
    template <>
    struct is_integral<char> { static const bool value = true; };

    template <>
    struct is_integral<short> { static const bool value = true; };

    template <>
    struct is_integral<int> { static const bool value = true; };

    template <>
    struct is_integral<long> { static const bool value = true; };

    template <>
    struct is_integral<long long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned char> { static const bool value = true; };

    template <>
    struct is_integral<unsigned short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned int> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

} // namespace ft

#endif