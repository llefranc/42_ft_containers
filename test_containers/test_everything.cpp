/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_everything.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:39:19 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/21 17:16:54 by llefranc         ###   ########.fr       */
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


int main()
{
	// const std::vector<int> vec;
	// vec.push_back(1);
	// vec.push_back(2);
	// vec.push_back(3);
	// vec.push_back(4);
	// vec.push_back(5);

	// //rit	
	// //it	
	// //		a 0 1 2 b

	// std::vector<int>::const_reverse_iterator it1(vec.begin() + 1);

	// std::vector<int>::reverse_iterator it2(vec.end() - 1);

	// std::cout << "std:" << (it1 - it2) << "\n";
	
	// std::cout << "beg: " << *(vec.begin() + 1) << " end: " << *(vec.end() - 1) << "\n";
	// std::cout << "it1 =" << *it1; 
	// std::cout << " it2: " << *it2 << "\n";

	// std::cout << "-----------------------------------\n";

	// ftvec.push_back(1);
	// ftvec.push_back(2);
	// ftvec.push_back(3);
	// ftvec.push_back(4);
	// ftvec.push_back(5);

	// const ft::vector<int> ftvec(4, 3);
	// ft::vector<int>::const_reverse_iterator ftit2(ftvec.rbegin());
	// // ftit2;
	// ft::vector<int>::const_reverse_iterator ff(ftit2);
	// std::cout << *ftit2;

	// ft::vector<int> ft(4,3);
	// ft::vector<int>::reverse_iterator i(ft.rbegin());
	// // ft::vector<int>::reverse_iterator f2(i);
	// std::cout << *i;
	

	// std::cout << "ftstd:" << (ftit - ftit2) << "\n";

	// std::cout << "beg: " << *(ftvec.begin() + 1) << " end: " << *(ftvec.end() - 1) << "\n";
	// std::cout << "ftit1 =" << *ftit; 
	// std::cout << " ftit2: " << *ftit2 << "\n";


	// std::vector<int> vec;
	// vec.push_back(0);
	// vec.push_back(1);
	// vec.push_back(2);

	// // std::vector<int>::reverse_iterator it = vec.begin();
	// std::vector<int>::iterator it(vec.begin());
	// std::vector<int>::iterator it2(vec.rbegin());

	// std::cout << "it1 =" << *it; 
	// std::cout << " it2: " << *it2 << "\n";
	
	// ft::vector<int> vec2;
	// vec2.push_back(0);
	// vec2.push_back(1);
	// vec2.push_back(2);

	// // ft::vector<int>::reverse_iterator it = vec2.begin();
	// ft::vector<int>::reverse_iterator it3(vec2.begin());
	// ft::vector<int>::reverse_iterator it4(vec2.rbegin());

	// std::cout << "ft:" << (it3 - it4) << "\n";
	// std::cout << "it1 =" << *it3 << " it2: " << *it4 << "\n";

	// const ft::vector<int> ftvec(4, 3);


	// ft::vector<int>::const_reverse_iterator ftit(ftvec.rbegin() + 1);
	// ft::vector<int>::const_reverse_iterator it;

	// it = ftit;

	testAllVectors();
}
