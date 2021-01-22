/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_everything.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:39:19 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/22 15:24:12 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int		testAllVectors();

void	printTestNumber(int *nb)
{
	static int i = 0;

	if (nb)
		i = *nb;
	else
		std::cout << "\n---------------------\ntest " <<++i << ":\t";
}

int main()
{
	testAllVectors();
}
