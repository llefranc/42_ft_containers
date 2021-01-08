/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_or_not_const_templates.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:47:38 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/08 17:02:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_OR_NOT_CONST_TEMPLATES_HPP
#define CONST_OR_NOT_CONST_TEMPLATES_HPP

namespace ft
{
	template <bool isConst, typename isFalse, typename isTrue>
	struct chooseConst {};

	template <typename isFalse, typename isTrue>
	struct chooseConst<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};

	template <typename isFalse, typename isTrue>
	struct chooseConst<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};

} //namespace ft

#endif