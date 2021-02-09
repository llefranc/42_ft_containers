/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:03 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/09 16:05:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

void balanceTheTree(Node** root, Node* newNode);
void balanceTheTreeTest(Node** root, Node* node);


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
	return heightTree(node->left, 1) - heightTree(node->right, 1);
}

// Right rotation of node Q:
// Let P be Q's left child.
// Set Q's left child to be P's right child.
// [Set P's right-child's parent to Q]
// Set P's right child to be Q.
// [Set Q's parent to P]

// Left rotation of node P:
// Let Q be P's right child.
// Set P's right child to be Q's left child.
// [Set Q's left-child's parent to P]
// Set Q's left child to be P.
// [Set P's parent to Q]

void rotateRight(Node** root, Node* node)
{
	Node* nodeGoingUp = node->left;
	
	// fils gauche Q is fils gauche P
	node->left = nodeGoingUp->right;
	
	// case right son is NULL to prevent segfault
	if (nodeGoingUp->right)
		nodeGoingUp->right->parent = node;
	
	// fils gauche P is  Q
	nodeGoingUp->right = node;
	
	// Parent P = Parent Q
	nodeGoingUp->parent = node->parent;
	
	if (node->parent && node->parent->left == node) // il est sur le pere gauche
		node->parent->left = nodeGoingUp;
	else if (node->parent) // il est sur le pere droit
		node->parent->right = nodeGoingUp;
	
	// Parent Q is P
	node->parent = nodeGoingUp;

	// new root node
	if (!nodeGoingUp->parent)
		*root = nodeGoingUp;
}

void rotateLeft(Node** root, Node* node)
{
	Node* nodeGoingUp = node->right;
	
	// fils droite P is fils gauche Q
	node->right = nodeGoingUp->left;

	// Case left son is NULL to prevent segfault
	if (nodeGoingUp->left)
		nodeGoingUp->left->parent = node;
	
	// fils gauche Q is P
	nodeGoingUp->left = node;
	
	// Parent Q = Parent P
	nodeGoingUp->parent = node->parent;
	
	if (node->parent && node->parent->left == node) // il est sur le pere gauche
		node->parent->left = nodeGoingUp;
	else if (node->parent) // il est sur le pere droit
		node->parent->right = nodeGoingUp;

	// Parent P is Q
	node->parent = nodeGoingUp;

	// new root node
	if (!nodeGoingUp->parent)
		*root = nodeGoingUp;
}

Node* insertAndBalanceNode(Node** root, Node* insertPos, int data)
{
	// Case creating the tree
	if (!root)
		return createNode(data);

	// Case data already exist in the tree
	if (insertPos->data == data)
		return 0;

	// Recursive loop until we reach a leaf
	if (insertPos->data > data && insertPos->left)
		return insertAndBalanceNode(root, insertPos->left, data);
	else if (insertPos->data < data && insertPos->right)
		return insertAndBalanceNode(root, insertPos->right, data);

	// if we reach this step, we arrived to a leaf : inserting new node to his correct position
	Node *newNode = createNode(data);
	insertPos->data > newNode->data ? insertPos->left = newNode : insertPos->right = newNode;
	newNode->parent = insertPos;

	// std::cout << "inserting node :" << newNode->data << ", tree before balancing:\n";

	// printTree(*root, heightTree(*root, 0));
	// std::cout << "----------------\n";

	balanceTheTree(root, newNode);

	// std::cout << "tree after balancing: \n";
	// printTree(*root, heightTree(*root, 0));
	// std::cout << "----------------\n";

	return newNode;
}

void balanceTheTree(Node** root, Node* node)
{
	while (node)
	{
		int balance;
		// std::cout << "balance of node " << node->data << " = " << balanceOfSubtrees(node) << "\n";
		// printTree(*root, heightTree(*root, 0));

		
		if ((balance = balanceOfSubtrees(node)) < -1 && node->right->right) // right right case
		{
			rotateLeft(root, node);
			// std::cout << " right right case\n";
		}
		else if ((balance = balanceOfSubtrees(node)) < -1 && node->right->left) // right left case
		{
			rotateRight(root, node->right);
			rotateLeft(root, node);
			// std::cout << " right left case\n";
		}
		else if (balance > 1 && node->left->left) // left left case
		{
			rotateRight(root, node);
			// std::cout << " left left case\n";
		}
		else if (balance > 1 && node->left->right) // left right case
		{
			rotateLeft(root, node->left);
			rotateRight(root, node);
			// std::cout << " left right case\n";
		}
		

		node = node->parent;
	}
	// std::cout << "\n";	
}

void balanceTheTreeTest(Node** root, Node* node)
{
	while (node)
	{
		int balance;
		// std::cout << "balance of node " << node->data << " = " << balanceOfSubtrees(node) << "\n";
		// printTree(*root, heightTree(*root, 0));

		
		if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0) // right right case
		{
			// printTree(*root, heightTree(*root, 0));
			rotateLeft(root, node);
			// std::cout << " right right case\n";
			// return;
		}
		else if (balance < -1 && balanceOfSubtrees(node->right) > 0) // right left case
		{
			rotateRight(root, node->right);
			rotateLeft(root, node);
			// std::cout << " right left case\n";
			// return;
		}
		else if (balance > 1 && balanceOfSubtrees(node->left) > 0) // left left case
		{
			// std::cout << " left left case\n";
			rotateRight(root, node);
			// return ;
		}
		else if (balance > 1 && balanceOfSubtrees(node->left) < 0) // left right case
		{
			// std::cout << " left right case\n";
			rotateLeft(root, node->left);
			rotateRight(root, node);
			// return ;
		}
		

		node = node->parent;
	}
	// std::cout << "\n";	
}


Node* insertAndBalanceNodeTest(Node** root, Node* insertPos, int data)
{
	// Case creating the tree
	if (!root)
		return createNode(data);

	// Case data already exist in the tree
	if (insertPos->data == data)
		return 0;

	// Recursive loop until we reach a leaf
	if (insertPos->data > data && insertPos->left)
		return insertAndBalanceNodeTest(root, insertPos->left, data);
	else if (insertPos->data < data && insertPos->right)
		return insertAndBalanceNodeTest(root, insertPos->right, data);

	// if we reach this step, we arrived to a leaf : inserting new node to his correct position
	Node *newNode = createNode(data);
	insertPos->data > newNode->data ? insertPos->left = newNode : insertPos->right = newNode;
	newNode->parent = insertPos;

	// std::cout << "inserting node :" << newNode->data << ", tree before balancing:\n";

	// printTree(*root, heightTree(*root, 0));
	// std::cout << "----------------\n";

	balanceTheTreeTest(root, newNode);

	// std::cout << "tree after balancing: \n";
	// printTree(*root, heightTree(*root, 0));
	// std::cout << "----------------\n";

	return newNode;
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

	root = createNode(10);

	std::string a;

	for (int i = 0, j = 33; i < 40 && j > -10; i += 2, j -=3)
	{
		std::cout << "i = " << i << "\n";
		// std::cin >> a;
		
		insertAndBalanceNodeTest(&root, root, i);
		// printTree(root, heightTree(root, 0));


		std::cout << "j = " << j << "\n";
		// std::cin >> a;
		
		insertAndBalanceNodeTest(&root, root, j);
		// printTree(root, heightTree(root, 0));

	}
	printTree(root, heightTree(root, 0));
	// std::cout << "---------------------------------------\n";

	
	// insertAndBalanceNodeTest(&root, root, 16);
	// // insertNode(root, 16);
	// printTree(root, heightTree(root, 0));
	// printTree(root, heightTree(root, 0));

	
	return 0;
}

// int main(int ac, char **av)
// {
// 	(void)av;
// 	(void)ac;

// 	Node* root;
// 	root = createNode(18);

// 	insertAndBalanceNodeTest(&root, root, 18);
// 	insertAndBalanceNodeTest(&root, root, 21);
// 	insertAndBalanceNodeTest(&root, root, 14);
// 	insertAndBalanceNodeTest(&root, root, 12);
// 	insertAndBalanceNodeTest(&root, root, 15);
// 	insertAndBalanceNodeTest(&root, root, 16);
	
// 	printTree(root, heightTree(root, 0));

// 	return 0;
// }




// i = 0
// j = 33
// i = 2
// j = 30
// i = 4
// j = 27
// i = 6
// j = 24
// i = 8
// j = 21
// i = 10
// j = 18
// i = 12
// j = 15
// i = 14
// j = 12
// i = 16
// j = 9
// i = 18
// j = 6
// i = 20
// j = 3
// i = 22
// j = 0
// i = 24
// j = -3
// i = 26
// j = -6
// i = 28
// j = -9
// i = 30
// j = -12
// i = 32
// j = -15
// i = 34
// j = -18
// i = 36
// j = -21
// i = 38
// j = -24