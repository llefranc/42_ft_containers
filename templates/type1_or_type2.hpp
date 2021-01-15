/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type1_or_type2.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:47:38 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/15 12:31:56 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE1_OR_TYPE2_HPP
#define TYPE1_OR_TYPE2_HPP

namespace ft
{
	// Typedef type 1 or type 2 using a boolean
	template <bool isConst, typename isFalse, typename isTrue>
	struct chooseConst {};

	// Typedef const
	template <typename isFalse, typename isTrue>
	struct chooseConst<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};

	// Typedef non_const
	template <typename isFalse, typename isTrue>
	struct chooseConst<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};

} //namespace ft

#endif