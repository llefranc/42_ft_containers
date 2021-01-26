/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_defs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:03:59 by llefranc          #+#    #+#             */
/*   Updated: 2021/01/26 15:57:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/tester.hpp"

#include "../includes/tester.hpp"
#include "list_tests.hpp"

int		testAllLists()
{
		std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf

		double nb_test_ptr = 5.6;

		// testing ft::list
		{
			std::ofstream out("results/ft::list_result.txt");
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to ft::list_result.txt

			int nb = 0;
			printTestNumber(&nb);
			
			using namespace ft;

			list<char> v0(12, 'c');
			list<char> v1(v0);
			list<char> v2(1,'a');
			list<char> v3;
			v3 = v2;
			list<char> v4;
			for (char c = 'a'; c < 'f'; ++c)
				v4.push_back(c);

			list<int> v10(5, 100);
			list<int> v11(0);
			list<int> v12(1, 89123891);
			list<int> v13(v10.begin(), v10.end());
			list<int> v14;
			v14 = v13;
			list<int> v15;
			for (int i = 0; i < 4; ++i)
				v15.push_back(i);

			list<double*> v20;
			list<double*> v21(1, &nb_test_ptr);
			list<double*> v22;
			v22 = v21;

			list<std::string> v30(6, "salut");
			list<std::string> v31(v30);
			v31.front() = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			v31.back() = "jbhkfbhsj3123t1672313f123125635";
			list<std::string> v32(4);
			list<std::string> v33(v30.begin(), v30.end());
			list<std::string> v34;
			v34 = v33;

			list<Bob> v40(2);
			list<Bob> v41(v40);
			list<Bob> v42(1);
			list<Bob> v43;
			v43 = v42;

			const list<int> v100(5, 100);
			const list<int> v101;
			
			const list<char> v200(v1);
			const list<char> v201(v200);

			const list<std::string> v300(3, "bonjour");


			int testNb = 0;
			executeAllListTests(v0, ++testNb);
			executeAllListTests(v1, ++testNb);
			executeAllListTests(v2, ++testNb);
			executeAllListTests(v3, ++testNb);
			executeAllListTests(v4, ++testNb);

			executeAllListTests(v10, ++testNb);
			executeAllListTests(v11, ++testNb);
			executeAllListTests(v12, ++testNb);
			executeAllListTests(v13, ++testNb);
			executeAllListTests(v14, ++testNb);
			executeAllListTests(v15, ++testNb);

			executeAllListTests(v20, ++testNb);
			executeAllListTests(v21, ++testNb);
			executeAllListTests(v22, ++testNb);

			executeAllListTests(v30, ++testNb);
			executeAllListTests(v31, ++testNb);
			executeAllListTests(v32, ++testNb);
			executeAllListTests(v33, ++testNb);
			executeAllListTests(v34, ++testNb);

			executeAllListTests(v40, ++testNb);
			executeAllListTests(v41, ++testNb);
			executeAllListTests(v42, ++testNb);
			executeAllListTests(v43, ++testNb);
			
			executeAllListTests(v100, ++testNb, CONST);
			executeAllListTests(v101, ++testNb, CONST);
			executeAllListTests(v200, ++testNb, CONST);
			executeAllListTests(v201, ++testNb, CONST);
			executeAllListTests(v300, ++testNb, CONST);
		}

		// testing std::list
		{
			std::ofstream out("results/std::list_result.txt");
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to std::list_result.txt

			int nb = 0;
			printTestNumber(&nb);
			
			using namespace std;

			list<char> v0(12, 'c');
			list<char> v1(v0);
			list<char> v2(1,'a');
			list<char> v3;
			v3 = v2;
			list<char> v4;
			for (char c = 'a'; c < 'f'; ++c)
				v4.push_back(c);

			list<int> v10(5, 100);
			list<int> v11(0);
			list<int> v12(1, 89123891);
			list<int> v13(v10.begin(), v10.end());
			list<int> v14;
			v14 = v13;
			list<int> v15;
			for (int i = 0; i < 4; ++i)
				v15.push_back(i);

			list<double*> v20;
			list<double*> v21(1, &nb_test_ptr);
			list<double*> v22;
			v22 = v21;

			list<std::string> v30(6, "salut");
			list<std::string> v31(v30);
			v31.front() = "jbhkfbhsjdhfbhsdkjfbjksdbkhfsdf";
			v31.back() = "jbhkfbhsj3123t1672313f123125635";
			list<std::string> v32(4);
			list<std::string> v33(v30.begin(), v30.end());
			list<std::string> v34;
			v34 = v33;

			list<Bob> v40(2);
			list<Bob> v41(v40);
			list<Bob> v42(1);
			list<Bob> v43;
			v43 = v42;

			const list<int> v100(5, 100);
			const list<int> v101;
			
			const list<char> v200(v1);
			const list<char> v201(v200);

			const list<std::string> v300(3, "bonjour");


			int testNb = 0;
			executeAllListTests(v0, ++testNb);
			executeAllListTests(v1, ++testNb);
			executeAllListTests(v2, ++testNb);
			executeAllListTests(v3, ++testNb);
			executeAllListTests(v4, ++testNb);

			executeAllListTests(v10, ++testNb);
			executeAllListTests(v11, ++testNb);
			executeAllListTests(v12, ++testNb);
			executeAllListTests(v13, ++testNb);
			executeAllListTests(v14, ++testNb);
			executeAllListTests(v15, ++testNb);

			executeAllListTests(v20, ++testNb);
			executeAllListTests(v21, ++testNb);
			executeAllListTests(v22, ++testNb);

			executeAllListTests(v30, ++testNb);
			executeAllListTests(v31, ++testNb);
			executeAllListTests(v32, ++testNb);
			executeAllListTests(v33, ++testNb);
			executeAllListTests(v34, ++testNb);

			executeAllListTests(v40, ++testNb);
			executeAllListTests(v41, ++testNb);
			executeAllListTests(v42, ++testNb);
			executeAllListTests(v43, ++testNb);
			
			executeAllListTests(v100, ++testNb, CONST);
			executeAllListTests(v101, ++testNb, CONST);
			executeAllListTests(v200, ++testNb, CONST);
			executeAllListTests(v201, ++testNb, CONST);
			executeAllListTests(v300, ++testNb, CONST);
		}

		std::cout.rdbuf(coutbuf); //reset to standard output again
		
		return 0;
}
