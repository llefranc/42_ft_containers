/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_like.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/24 16:56:19 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_LIKE_HPP
#define STL_LIKE_HPP

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::PAIR -------------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct pair
    * (destructor):         Pair destructor
    * operator=:            Assign content
    *
    * - Public member variables:
    * T1:                   First pair's member variable
    * T2:                   Second pair's member variable
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
            
    }; // pair


    /**
    * ------------------------------------------------------------- *
    * ---------------------- FT::ALLOCATOR ------------------------ *
    * - Coplien form:
    * (constructor)     Creates a new allocator instance
    * (destructor)      Destructs an allocator instance
    *
    * - Member functions:
    * Address           Obtains the address of an object
    * Allocate          Allocates uninitialized storage
    * Deallocate        Deallocates storage
    * Construct         Constructs an object in allocated storage
    * Destroy           Destroys an object in allocated storage
    * ------------------------------------------------------------- *
    */
 
    template <class T>
    class allocator
    {
        /* ------------------------------------------------------------- */
        /* --------------------------- ALIASES ------------------------- */
        
        public:

            typedef T           value_type;
            typedef T*          pointer;
            typedef T&          reference;
            typedef const T*    const_pointer;
            typedef const T&    const_reference;
            typedef size_t      size_type;
            typedef long int    difference_type;


        /* ------------------------------------------------------------- */
        /* ------------------------ COPLIEN FORM ----------------------- */

        allocator() throw() {};
        
        allocator(const allocator&) throw() {};

        template <class U>
        allocator(const allocator<U>&) throw() {};

        ~allocator() throw() {};


        /* ------------------------------------------------------------- */
        /* ---------------------- MEMBER FUNCTIONS --------------------- */

        /**
        *   @return The address of x object.
        */
        pointer address(reference x) const              { return &x; }

        /**
        *   @return The address of x object.
        */
        const_pointer address(const_reference x) const  { return &x; }


        /**
        *   Allocates uninitialized storage.
        *
        *   @param n    The number of objects to allocates.
        *   @return     A pointer to the newly allocated area.
        */
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

        /**
        *   Deallocates storage (this doesn't call destructors for the objects present
        *   in this storage).
        *
        *   @param p    The address of a previously allocated area with allocate.
        *   @param n    The size of the area to deallocate.
        *   @return     A pointer to the newly allocated area.
        */
        void deallocate (pointer p, size_type n)
        {
            (void)n;
            ::operator delete(p);
        }

        /**
        *   Constructs an object in allocated storage.
        *
        *   @param p    A pointer to an unintialized allocated storage.
        *   @param v    The value to use as the copy constructor argument.
        */
        void construct(pointer p, const T& v) { new((void*)p)T(v); }
        
        /**
        *   Destroy an object in allocated storage.
        *
        *   @param p    A pointer to the object that is going to be destroyed.
        */
        void destroy(pointer p) { p->~T(); }
        
    }; // allocator


    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::LESS -------------------------- *
    */
   
    template <class T>
    struct less
    {
        typedef T       first_argument_type;
        typedef T       second_argument_type;
        typedef bool    result_type;
        
        bool operator() (const T& x, const T& y) const {return x<y;}
        
    }; // less


    /**
    * ------------------------------------------------------------- *
    * ---------------------- FT::ENABLE_IF ------------------------ *
    */

    /**
    *   Typedef an int into type only if B is true.
    */

    template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };
        
        
    /**
    * ------------------------------------------------------------- *
    * --------------------- FT::IS_INTEGRAL ----------------------- *
    */

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