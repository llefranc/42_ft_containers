/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary_tree.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:47:24 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/08 16:50:44 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

Node* createNode(int data)
{
	Node* newNode = new Node;

	newNode->data = data;
	newNode->balance = 0;
	newNode->parent = 0;
	newNode->left = 0;
	newNode->right = 0;

	return newNode;
}

Node* insertNode(Node* root, int data)
{
	// Case creating the tree
	if (!root)
		return createNode(data);

	// Case data already exist in the tree
	if (root->data == data)
		return 0;

	// Recursive loop until we reach a leaf
	if (root->data > data && root->left)
		return insertNode(root->left, data);
	else if (root->data < data && root->right)
		return insertNode(root->right, data);

	// if we reach this step, we arrived to a leaf : inserting new node to his correct position
	Node *newNode = createNode(data);
	root->data > newNode->data ? root->left = newNode : root->right = newNode;
	newNode->parent = root;
	
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

bool deleteNode(Node** root, int data, bool deallocate)
{
	Node* tmp = searchNode(*root, data);

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
			*root = tmp->left;
			tmp->left->parent = 0;
		}
		else if (!tmp->left && tmp->right)
		{
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
		tmp->data <= tmp->parent->data ? tmp->parent->left = 0 : tmp->parent->right = 0;
	
	// Case only one son (left or right)
	else if (tmp->left && !tmp->right)
	{
		tmp->data <= tmp->parent->data ? tmp->parent->left = tmp->left : tmp->parent->right = tmp->left;
		tmp->left->parent = tmp->parent;
	}
	else if (!tmp->left && tmp->right)
	{
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
	
	if (deallocate)
		delete tmp;

	return 1;	
}
