/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:19:42 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/04/07 19:32:35 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <string>

#include "containers/list.hpp"
#include "containers/vector.hpp"
#include "containers/map.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"

int main()
{
    std::vector<int>            std_vec;
    std::list<std::string>      std_lis;
    std::stack<char>            std_sta;
    std::stack<double>          std_que;
    std::map<int, std::string>  std_map;
    
    ft::vector<int>             ft_vec;
    ft::list<std::string>       ft_lis;
    ft::stack<char>             ft_sta;     /* All acting like the real containers from the STL */
    ft::queue<double>           ft_que;
    ft::map<int, std::string>   ft_map;

}