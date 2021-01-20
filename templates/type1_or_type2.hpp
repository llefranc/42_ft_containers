/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type1_or_type2.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:47:38 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/20 15:02:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE1_OR_TYPE2_HPP
#define TYPE1_OR_TYPE2_HPP

namespace ft
{
	/**
	*	Use a boolean to typedef either type 1 or type 2.
	*/
	template <bool isConst, typename isFalse, typename isTrue>
	struct chooseConst {};

	/**
	*	Typedef: const pointer, const ref...
	*/
	template <typename isFalse, typename isTrue>
	struct chooseConst<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};

	/**
	*	Typedef: pointer, ref...
	*/
	template <typename isFalse, typename isTrue>
	struct chooseConst<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};

} //namespace ft

#endif