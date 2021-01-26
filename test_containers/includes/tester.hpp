/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:27:13 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 20:22:23 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>

#include <vector>
#include <list>

// Include the containers to test
#include "../../containers/vector.hpp"
#include "../../containers/list.hpp"

// Needed for testing
#include "../../templates/stl_like.hpp"
#include "print_type.hpp"
#include "Bob_test.hpp"

#define NOTCONST 0
#define CONST 1

void	printTestNumber(int *nb);

int		testAllVectors();
int		testAllLists();

#endif