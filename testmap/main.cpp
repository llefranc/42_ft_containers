/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:03 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/09 17:25:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

void balanceTheTree(Node** root, Node* newNode);

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

void balanceTheTree(Node** root, Node* node)
{
	while (node)
	{
		int balance;
		
		std::cout << "balance = " << balanceOfSubtrees(node) << "pour data = " << node->data << "\n";
		if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0) // right right case
			rotateLeft(root, node);
		else if (balance < -1 && balanceOfSubtrees(node->right) > 0) // right left case
		{
			rotateRight(root, node->right);
			rotateLeft(root, node);
		}
		else if (balance > 1 && balanceOfSubtrees(node->left) > 0) // left left case
			rotateRight(root, node);
		else if (balance > 1 && balanceOfSubtrees(node->left) < 0) // left right case
		{
			rotateLeft(root, node->left);
			rotateRight(root, node);
		}
		node = node->parent;
	}
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

	balanceTheTree(root, newNode);

	return newNode;
}

bool deleteNodeTest(Node** root, int data, bool deallocate)
{
	Node* tmp = searchNode(*root, data);
	Node* balanceNode = 0;

	// If element isn't present, nothing to delete
	if (!tmp)
		return 0;
	
	// Case the node to delete is the root
	if (!tmp->parent)
	{
		// The tree will be empty
		if (!tmp->left && !tmp->right)
			*root = 0;

		// Case only one son (left or right)	
		else if (tmp->left && !tmp->right)
		{
			balanceNode = tmp->left; //new
			*root = tmp->left;
			tmp->left->parent = 0;
		}
		else if (!tmp->left && tmp->right)
		{
			balanceNode = tmp->left; //new
			*root = tmp->right;
			tmp->right->parent = 0;
		}
		
		// Case two sons, need to switch the data of the node to delete with the highest data
		// in the left subtree, and to delete the node in the left subtree
		else
		{
			Node* maxNode = searchMaxNode(tmp->left);
			tmp->data = maxNode->data;
			return deleteNode(&tmp->left, maxNode->data, 1);
		}
	}

	// Case the node to delete is a leaf
	else if (!tmp->left && !tmp->right)
	{
		balanceNode = tmp->parent;
		tmp->data <= tmp->parent->data ? tmp->parent->left = 0 : tmp->parent->right = 0;
	}
	
	// Case only one son (left or right)
	else if (tmp->left && !tmp->right)
	{
		balanceNode = tmp->left;
		tmp->data <= tmp->parent->data ? tmp->parent->left = tmp->left : tmp->parent->right = tmp->left;
		tmp->left->parent = tmp->parent;
	}
	else if (!tmp->left && tmp->right)
	{
		balanceNode = tmp->right;
		tmp->data <= tmp->parent->data ? tmp->parent->left = tmp->right : tmp->parent->right = tmp->right;
		tmp->right->parent = tmp->parent;
	}

	// Case two sons, need to switch the data of the node to delete with the highest data
	// in the left subtree, and to delete the node in the left subtree
	else
	{
		Node* maxNode = searchMaxNode(tmp->left);
		tmp->data = maxNode->data;
		return deleteNode(&tmp->left, maxNode->data, 1);
	}
	
	balanceTheTree(root, balanceNode);
	
	if (deallocate)
		delete tmp;

	return 1;	
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

	for (int i = 0, j = 33; i < 20 && j > -10; i += 2, j -=3)
	{
		insertAndBalanceNode(&root, root, i);
		insertAndBalanceNode(&root, root, j);
	}
	printTree(root, heightTree(root, 0));

	std::cout << "deleting 33\n";
	deleteNodeTest(&root, 33, 1);
	std::cout << "deleting 30\n";
	deleteNodeTest(&root, 30, 1);
	std::cout << "---------------------------------------\n";
	printTree(root, heightTree(root, 0));

	// insertAndBalanceNodeTest(&root, root, 16);
	// // insertNode(root, 16);
	// printTree(root, heightTree(root, 0));
	// printTree(root, heightTree(root, 0));

	
	return 0;
}
