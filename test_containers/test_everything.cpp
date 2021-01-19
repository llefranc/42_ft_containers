/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_everything.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:39:19 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/19 16:09:22 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void	printTestNumber(int *nb)
{
	static int i = 0;

	if (nb)
		i = *nb;
	else
		std::cout << "\n---------------------\ntest " <<++i << ":\t";
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

			vector<char> v0(12, 'c');
			vector<char> v1(v0);
			vector<char> v2(1,'a');
			vector<char> v3;
			v3 = v2;

			vector<int> v10(5, 100);
			vector<int> v11(0);
			vector<int> v12(1, 89123891);
			vector<int> v13(v10.begin(), v10.end());
			vector<int> v14;
			v14 = v13;

			vector<double*> v20;
			vector<double*> v21(1, &nb_test_ptr);
			vector<double*> v22;
			v22 = v21;

			vector<std::string> v30(6, "salut");
			vector<std::string> v31(v30);
			v31[0] = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			v31[5] = "jbhkfbhsj";
			vector<std::string> v32(4);
			vector<std::string> v33(v30.begin(), v30.end());
			vector<std::string> v34;
			v34 = v33;

			vector<Bob> v40(2);
			vector<Bob> v41(v40);
			vector<Bob> v42(1);
			vector<Bob> v43;
			v43 = v42;

			const vector<int> v100(5, 100);
			const vector<int> v101;
			
			const vector<char> v200(v1);
			const vector<char> v201(v200);

			const vector<std::string> v300(3, "bonjour");


			int testNb = 0;
			executeAllVecTests(v0, ++testNb);
			executeAllVecTests(v1, ++testNb);
			executeAllVecTests(v2, ++testNb);
			executeAllVecTests(v3, ++testNb);

			executeAllVecTests(v10, ++testNb);
			executeAllVecTests(v11, ++testNb);
			executeAllVecTests(v12, ++testNb);
			executeAllVecTests(v13, ++testNb);
			executeAllVecTests(v14, ++testNb);

			executeAllVecTests(v20, ++testNb);
			executeAllVecTests(v21, ++testNb);
			executeAllVecTests(v22, ++testNb);

			executeAllVecTests(v30, ++testNb);
			executeAllVecTests(v31, ++testNb);
			executeAllVecTests(v32, ++testNb);
			executeAllVecTests(v33, ++testNb);
			executeAllVecTests(v34, ++testNb);

			executeAllVecTests(v40, ++testNb);
			executeAllVecTests(v41, ++testNb);
			executeAllVecTests(v42, ++testNb);
			executeAllVecTests(v43, ++testNb);
			
			executeAllVecTests(v100, ++testNb, CONST);
			executeAllVecTests(v101, ++testNb, CONST);
			executeAllVecTests(v200, ++testNb, CONST);
			executeAllVecTests(v201, ++testNb, CONST);
			executeAllVecTests(v300, ++testNb, CONST);
		}

		// testing std::vector
		{
			std::ofstream out("results/std::vector_result.txt");
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to std::vector_result.txt

			int nb = 0;
			printTestNumber(&nb);
			
			using namespace std;

			vector<char> v0(12, 'c');
			vector<char> v1(v0);
			vector<char> v2(1,'a');
			vector<char> v3;
			v3 = v2;

			vector<int> v10(5, 100);
			vector<int> v11(0);
			vector<int> v12(1, 89123891);
			vector<int> v13(v10.begin(), v10.end());
			vector<int> v14;
			v14 = v13;

			vector<double*> v20;
			vector<double*> v21(1, &nb_test_ptr);
			vector<double*> v22;
			v22 = v21;

			vector<std::string> v30(6, "salut");
			vector<std::string> v31(v30);
			v31[0] = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			v31[5] = "jbhkfbhsj";
			vector<std::string> v32(4);
			vector<std::string> v33(v30.begin(), v30.end());
			vector<std::string> v34;
			v34 = v33;

			vector<Bob> v40(2);
			vector<Bob> v41(v40);
			vector<Bob> v42(1);
			vector<Bob> v43;
			v43 = v42;

			const vector<int> v100(5, 100);
			const vector<int> v101;
			
			const vector<char> v200(v1);
			const vector<char> v201(v200);

			const vector<std::string> v300(3, "bonjour");


			int testNb = 0;
			executeAllVecTests(v0, ++testNb);
			executeAllVecTests(v1, ++testNb);
			executeAllVecTests(v2, ++testNb);
			executeAllVecTests(v3, ++testNb);

			executeAllVecTests(v10, ++testNb);
			executeAllVecTests(v11, ++testNb);
			executeAllVecTests(v12, ++testNb);
			executeAllVecTests(v13, ++testNb);
			executeAllVecTests(v14, ++testNb);

			executeAllVecTests(v20, ++testNb);
			executeAllVecTests(v21, ++testNb);
			executeAllVecTests(v22, ++testNb);

			executeAllVecTests(v30, ++testNb);
			executeAllVecTests(v31, ++testNb);
			executeAllVecTests(v32, ++testNb);
			executeAllVecTests(v33, ++testNb);
			executeAllVecTests(v34, ++testNb);

			executeAllVecTests(v40, ++testNb);
			executeAllVecTests(v41, ++testNb);
			executeAllVecTests(v42, ++testNb);
			executeAllVecTests(v43, ++testNb);
			
			executeAllVecTests(v100, ++testNb, CONST);
			executeAllVecTests(v101, ++testNb, CONST);
			executeAllVecTests(v200, ++testNb, CONST);
			executeAllVecTests(v201, ++testNb, CONST);
			executeAllVecTests(v300, ++testNb, CONST);
		}

		std::cout.rdbuf(coutbuf); //reset to standard output again
		
		return 0;
}

#include <cmath>

#include <memory>

int main()
{
	// std::vector<char> v0(11, 'b');
	std::vector<char> v1(12, 'c');

	// char c = v1.front()

	std::vector<char>::reverse_iterator it(v1.begin());
	// ft::vector<char> v2(v0);
	

	// std::cout << (v0 < v1);
	// std::cout << (v2 == v0);
	
	// v0.erase(v0.end());

	// ft::vector<char>::iterator it = v0.erase(v0.begin(), v0.begin());
	// std::cout << "it = " << *it << "\n";
	// v0.erase(v0.begin(), v0.end());

	// std::vector<char> vec(12, 'c');
	// vec.erase(vec.end());
	// std::vector<char>::iterator iter = vec.erase(vec.end());

	// for (std::vector<char>::iterator it = vec.begin(); it != iter; ++it)
	// 		std::cout << *it << " | ";
	// std::cout << "it = " << *it << "\n";
	
	// for (std::vector<char>::iterator it2 = vec.begin(); it2 != it; ++it2)
	// 	std::cout << *it2 << "|";

	testAllVectors();
}
