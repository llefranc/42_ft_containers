/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary_tree.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:47:24 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/10 13:58:05 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

Node* createNode(int data)
{
	Node* newNode = new Node;

	newNode->data = data;
	newNode->parent = 0;
	newNode->left = 0;
	newNode->right = 0;

	return newNode;
}

Node* searchNode(Node* root, int data)
{
	// We reached a leaf
	if (!root)
		return 0;
	
	if (root->data == data)
		return root;
	
	// Recursive loop until we find data
	if (root->data > data && root->left)
		return searchNode(root->left, data);
	else if (root->data < data && root->right)
		return searchNode(root->right, data);

	// If we reach this step in the first searchNode func that was called
	// with root (first node of the tree), then element is missing.
	return 0;
}

Node* searchMaxNode(Node *root)
{
	if (root->right)
		return searchMaxNode(root->right);
	return root;
}

Node* searchMinNode(Node *root)
{
	if (root->left)
		return searchMinNode(root->left);
	return root;
}

Node* insertNode(Node** root, Node* insertPos, int data)
{
	// Case creating the tree
	if (!root)
		return createNode(data);

	// Case data already exist in the tree
	if (insertPos->data == data)
		return 0;

	// Recursive loop until we reach a leaf
	if (insertPos->data > data && insertPos->left)
		return insertNode(root, insertPos->left, data);
	else if (insertPos->data < data && insertPos->right)
		return insertNode(root, insertPos->right, data);

	// if we reach this step, we arrived to a leaf : inserting new node to his correct position
	Node *newNode = createNode(data);
	insertPos->data > newNode->data ? insertPos->left = newNode : insertPos->right = newNode;
	newNode->parent = insertPos;

	// Equilibrating the tree from newNode to root node
	balanceTheTree(root, newNode);

	return newNode;
}

bool deleteNode(Node** root, Node* deletePos, int data, bool deallocate)
{
	// Balance node will point to the node to the first node impacted by the deletion
	// (if we delete a node, it will be parent node; if we delete root, it will be 
	// one of his son). We will then call balanceTheTree function to equilibrate the AVL tree
	Node* balanceNode = 0;
	
	// The node to delete, looking from deletePos node until we match data
	Node* del = searchNode(deletePos, data);

	// If element isn't present, nothing to delete
	if (!del)
		return false;
	
	// Case the node to delete is the root
	if (!del->parent)
	{
		// Root is the only node in the tree, it will be empty
		if (!del->left && !del->right)
			*root = 0;

		// Case only one son (left or right, need to equilibrate the tree
		// after from this son)
		else if (del->left && !del->right)
		{
			balanceNode = del->left;
			*root = del->left;
			del->left->parent = 0;
		}
		else if (!del->left && del->right)
		{
			balanceNode = del->right;
			*root = del->right;
			del->right->parent = 0;
		}
		
		// Case two sons, need to switch the data of the node to delete with the highest data
		// in the left subtree, and to delete the node with this highest data in the left subtree
		else
		{
			Node* maxNode = searchMaxNode(del->left);
			del->data = maxNode->data;
			return deleteNode(root, del->left, maxNode->data, 1);
		}
	}

	// Case the node to delete is a leaf
	else if (!del->left && !del->right)
	{
		balanceNode = del->parent;
		del->data <= del->parent->data ? del->parent->left = 0 : del->parent->right = 0;
	}
	
	// Case only one son (left or right)
	else if (del->left && !del->right)
	{
		balanceNode = del->parent;
		// balanceNode = del->left;
		del->data <= del->parent->data ? del->parent->left = del->left : del->parent->right = del->left;
		del->left->parent = del->parent;
	}
	else if (!del->left && del->right)
	{
		balanceNode = del->parent;
		// balanceNode = del->right;
		del->data <= del->parent->data ? del->parent->left = del->right : del->parent->right = del->right;
		del->right->parent = del->parent;
	}

	// Case two sons, need to switch the data of the node to delete with the highest data
	// in the left subtree, and to delete the node with this highest data in the left subtree
	else
	{
		Node* maxNode = searchMaxNode(del->left);
		del->data = maxNode->data;
		return deleteNode(root, del->left, maxNode->data, 1);
	}
	
	// Equilibrating the tree from balanceNode to root node
	balanceTheTree(root, balanceNode);
	
	if (deallocate)
		delete del;

	return true;
}

