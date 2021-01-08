/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:53:34 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/08 11:50:54 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP
#define TEMP

#include <iostream>

template<typename, int>
void	put()
{
	std::cout << "c'est n'imp\n";
}

template<>
void	put<int, true>()
{
	std::cout << "c'est vrai\n";
}

template<>
void	put<float, false>()
{
	std::cout << "c'est faux\n";
}

template<class T = int> class Random
{
	public:
	
	Random() : _value() {}
	Random(T value) : _value(value) {}
	
	void	printSize() const {std::cout << sizeof(T);}

	// T& operator*() {return (_value);}

	friend std::ostream& operator<<(std::ostream& flux, Random<T>& obj)
	{
		flux << obj._value;
		return (flux);
	}

	private:

		T _value;
};

template<typename U, typename V, template <class T> class C = Random>
class Test
{
	public:
	
	Test(int nbU, int nbV) : _sizeU(nbU), _sizeV(nbV)
	{
		_ptrU = new C<U>[nbU];
		_ptrV = new C<V>[nbV];
	}

	void printU()
	{
		for (int i = 0; i < _sizeU; ++i)
			std::cout << *_ptrU++ << " | ";
		std::cout << "\n";
	}

	void printV()
	{
		for (int i = 0; i < _sizeV; ++i)
			std::cout << *_ptrV++ << " | ";
		std::cout << "\n";
	}

	private:

		C<U>* _ptrU;
		C<V>* _ptrV;
		int	_sizeU;
		int _sizeV;
};

#endif