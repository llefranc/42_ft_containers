/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_everything.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:39:19 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/15 17:34:59 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

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
			v10[5] = "jbhkfbhsj";
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
			executeAllVecTests(v14, ++testNb, CONST);
			executeAllVecTests(v15, ++testNb, CONST);
			executeAllVecTests(v16, ++testNb, CONST);
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
			v10[5] = "jbhkfbhsj";
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
			executeAllVecTests(v14, ++testNb, CONST);
			executeAllVecTests(v15, ++testNb, CONST);
			executeAllVecTests(v16, ++testNb, CONST);
		}

		std::cout.rdbuf(coutbuf); //reset to standard output again
		
		return 0;
}

int main()
{

	ft::vector<char> v1(12, 'c');

	executeAllVecTests(v1, 0);

	
	// testAllVectors();
}