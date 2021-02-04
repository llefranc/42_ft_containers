/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:03 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/04 15:52:40 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>

# define BASE_WIDTH 80

struct Node
{
	int data;
	Node* left;
	Node* right;
};

std::string toString(int i)
{
   std::stringstream ss;
   ss << i;
   return ss.str();
}

// add
// erase
// search
// print tree + depth tree

/**
*	Creates a new node and assign data. left and right node ptr are NULL.
*
*	@param data		The content of the created node.
*	@return			The newly created node.
*/

Node* createNode(int data)
{
	Node* newNode = new Node;

	newNode->data = data;
	newNode->left = 0;
	newNode->right = 0;

	return newNode;
}


/**
*	Recursive function that recurses by comparing the data of each node with the new node data 
*	and calling itself with left / right side of the node depending on the result of 
*	the comparison, until it meets a leaf. Then inserting the element.
*
*	@param root		First node of the tree.
*	@param 
*/
Node* insert(Node* root, Node* newNode)
{
	// Case creating the tree
	if (!root)
		return newNode;

	// Case data already exist in the tree
	if (root->data == newNode->data)
		return root;

	// Recursive loop until we reach a leaf
	if (root->data > newNode->data && root->left)
		return insert(root->left, newNode);
	else if (root->data < newNode->data && root->right)
		return insert(root->right, newNode);

	// if we reach this step, we arrived to a leaf : inserting new node to his correct position
	root->data > newNode->data ? root->left = newNode : root->right = newNode;
	return root;
}

/**
*	Recursive function that calculates the tree's height. Calls itself on left son and right son for 
*	each node and increases height by 1 each time it can access node son.
*
*	@param root		The root of the tree (start with first node, then call itself with left
*					and right node' sons until meeting leaf).
*	@param height	The heigth of the actual node. Increases this param by 1 each time 
*					it's calling itself on a node' son.
*	@param return	The height of the tree (-1 if empty, 0 if only root node).
*/
int heightTree(Node *root, int height)
{
	// We reached a NULL, returning
	if (!root)
		return height - 1;

	// Exploring left side of the actual node, then right side
	int leftHeight = heightTree(root->left, height + 1);
	int rightHeight = heightTree(root->right, height + 1);

	return leftHeight > rightHeight ? leftHeight : rightHeight;
}

#include <cmath>

// int printLevel(Node *root,  int maxHeight, int actualHeight, int printHeight, int width)
// {
// 	// We reached a NULL, returning
// 	if (!root)
// 	{
// 		// if (actualHeight <= printHeight)
// 		if (actualHeight <= printHeight)
// 		{
// 			// for (int i = pow(static_cast<double>(printHeight - actualHeight) + 1.0, 2); i >= 0; --i)
// 			// for (int i = printHeight - actualHeight; i >= 0; --i)
// 			for (int i = pow(printHeight - actualHeight, 2); i >= 0; --i)
// 			{
// 				std::cout.width(width);		std::cout << "  ";
// 				std::cout.width(width);		std::cout << "";
// 			}
// 		}
// 		return actualHeight - 1;
// 	}

// 	if (actualHeight == printHeight)
// 	{
// 		std::cout.width(width);		std::cout << root->data;
// 		std::cout.width(width);		std::cout << "";
// 	}

// 	// Exploring left side of the actual node, then right side
// 	int leftHeight = printLevel(root->left, maxHeight, actualHeight + 1, printHeight, width);

// 	if (actualHeight == maxHeight)
// 	{
// 		for (int i = printHeight - actualHeight; i >= 0; --i)
// 		{
// 			std::cout.width(width);		std::cout << "  ";
// 			std::cout.width(width);		std::cout << "";
// 		}
// 	}

// 	int rightHeight = printLevel(root->right, maxHeight, actualHeight + 1, printHeight, width);

// 	return leftHeight > rightHeight ? leftHeight : rightHeight;
// }

// void printTree(Node *root, int height, int width)
// {
// 	for (int i = 0; i <= height; ++i)
// 	{
// 		printLevel(root, height, 0, i, width /= 2);
// 		std::cout << "\n";
// 	}
// }

int printLevel(Node *root, std::string& buff, int maxHeight, int actualHeight, int printHeight)
{
	// We reached a NULL, returning
	if (!root)
	{
		// if (actualHeight <= printHeight)
		if (actualHeight <= printHeight)
		{
			for (int i = pow(2, actualHeight - printHeight); i > 0; --i)
				buff += " ";
		}
		return actualHeight - 1;
	}

	if (actualHeight == printHeight)
		buff += toString(root->data) + " ";

	// Exploring left side of the actual node, then right side
	int leftHeight = printLevel(root->left, buff, maxHeight, actualHeight + 1, printHeight);
	int rightHeight = printLevel(root->right, buff, maxHeight, actualHeight + 1, printHeight);

	return leftHeight > rightHeight ? leftHeight : rightHeight;
}

void printTree(Node *root, int height, int width)
{
	(void)width;
	for (int i = 0; i <= height; ++i)
	{
		std::string buff;
		printLevel(root, buff, height, 0, i);
		std::cout << buff << "\n";

		COMPTER LE LEVEL OU ON DOIT PRINT ET YA PAS DE NODE ET FAIRE 2 puissance N
	}
}

int main()
{
	Node* root;

	root = createNode(15);

	insert(root, createNode(12));
	insert(root, createNode(13));
	// insert(root, createNode(14));
	insert(root, createNode(6));
	// insert(root, createNode(20));
	// insert(root, createNode(99));
	// insert(root, createNode(97));
	// insert(root, createNode(98));
	// insert(root, createNode(0));
	// insert(root, createNode(8));
	// insert(root, createNode(5));

	// std::cout << heightTree(root, 0);
	printTree(root, heightTree(root, 0), 60);


	return 0;
}