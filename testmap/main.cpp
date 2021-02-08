/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:03 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/08 17:06:22 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

/**
*	Compares the heights of left and right subtrees.
*
*	@param node	His left and right subtrees will be compare.
*	@return		Difference between left and right subtrees. Will be negative if right
*				subtree > left subtree.
*/
int balanceOfSubtrees(Node* node)
{
	if (!node)
		return 0;
	return heightTree(node->left, 0) - heightTree(node->right, 0);
}

int main(int ac, char **av)
{
	// if (ac != 2)
	// {
	// 	std::cout << "Wrong nb of args\n";
	// 	return 1;
	// }
	(void)av;
	(void)ac;

	Node* root;

	root = createNode(11);

	insertNode(root, 6);
	insertNode(root, 2);
	insertNode(root, 0);
	insertNode(root, 4);
	insertNode(root, 8);
	insertNode(root, 7);
	insertNode(root, 9);

	// insertNode(root, 17);
	// insertNode(root, 12);
	// insertNode(root, 14);
	// insertNode(root, 20);

	// std::cout << heightTree(root, 0);
	printTree(root, heightTree(root, 0));

	std::cout << balanceOfSubtrees(root) << "\n";
	
	return 0;
}