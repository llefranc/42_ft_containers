/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_everything.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:39:19 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/15 16:20:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>

#include "../containers/vector.hpp"
#include "../templates/stl_like.hpp"
#include "vector_test.hpp"
#include "Bob_test.hpp"

void	printTestNumber(int *nb)
{
	static int i = 0;

	if (nb)
		i = *nb;
	else
		std::cout << "test " <<++i << ": ";
}

int		testAllVectors()
{
		std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf

		double nb_test_ptr = 5.6;

		// testing ft::vector
		{
			std::ofstream out("results/ft::vector_result.txt");
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to ft::vector_result.txt

			int nb = 0;
			printTestNumber(&nb);
			
			using namespace ft;
			vector<char> v0;
			vector<char> v1(12, 'c');
			vector<char> v2(v1);
			vector<int> v3(5, 100);
			vector<int> v4(0);
			vector<int> v5(1, 89123891);
			vector<int> v6(v3.begin(), v3.end());
			vector<double*> v7;
			vector<double*> v8(1, &nb_test_ptr);
			vector<std::string> v9(6, "salut");
			vector<std::string> v10(v9);
			v10[0] = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			vector<std::string> v11(4);
			vector<Bob> v12(2);
			vector<Bob> v13(v12);
			const vector<int> v14(5, 100);
			const vector<char> v15(v1);
			const vector<std::string> v16(3, "bonjour");

//RAJOUTER ICI OPERATOR =

			int testNb = 0;
			executeAllVecTests(v0, ++testNb);
			executeAllVecTests(v1, ++testNb);
			executeAllVecTests(v2, ++testNb);
			executeAllVecTests(v3, ++testNb);
			executeAllVecTests(v4, ++testNb);
			executeAllVecTests(v5, ++testNb);
			executeAllVecTests(v6, ++testNb);
			executeAllVecTests(v7, ++testNb);
			executeAllVecTests(v8, ++testNb);
			executeAllVecTests(v9, ++testNb);
			executeAllVecTests(v10, ++testNb);
			executeAllVecTests(v11, ++testNb);
			executeAllVecTests(v12, ++testNb);
			executeAllVecTests(v13, ++testNb);
			executeAllVecTests(v14, ++testNb);
			executeAllVecTests(v15, ++testNb);
			executeAllVecTests(v16, ++testNb);
		}

		// testing std::vector
		{
			std::ofstream out("results/std::vector_result.txt");
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to std::vector_result.txt

			int nb = 0;
			printTestNumber(&nb);
			
			using namespace std;
			vector<char> v0;
			vector<char> v1(12, 'c');
			vector<char> v2(v1);
			vector<int> v3(5, 100);
			vector<int> v4(0);
			vector<int> v5(1, 89123891);
			vector<int> v6(v3.begin(), v3.end());
			vector<double*> v7;
			vector<double*> v8(1, &nb_test_ptr);
			vector<std::string> v9(6, "salut");
			vector<std::string> v10(v9);
			v10[0] = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			vector<std::string> v11(4);
			vector<Bob> v12(2);
			vector<Bob> v13(v12);
			const vector<int> v14(5, 100);
			const vector<char> v15(v1);
			const vector<std::string> v16(3, "bonjour");

			int testNb = 0;
			executeAllVecTests(v0, ++testNb);
			executeAllVecTests(v1, ++testNb);
			executeAllVecTests(v2, ++testNb);
			executeAllVecTests(v3, ++testNb);
			executeAllVecTests(v4, ++testNb);
			executeAllVecTests(v5, ++testNb);
			executeAllVecTests(v6, ++testNb);
			executeAllVecTests(v7, ++testNb);
			executeAllVecTests(v8, ++testNb);
			executeAllVecTests(v9, ++testNb);
			executeAllVecTests(v10, ++testNb);
			executeAllVecTests(v11, ++testNb);
			executeAllVecTests(v12, ++testNb);
			executeAllVecTests(v13, ++testNb);
			executeAllVecTests(v14, ++testNb);
			executeAllVecTests(v15, ++testNb);
			executeAllVecTests(v16, ++testNb);
		}

		std::cout.rdbuf(coutbuf); //reset to standard output again
		
		return 0;
}

int main()
{
	{
		testAllVectors();
		#define testSTD
		testAllVectors();
	}
}