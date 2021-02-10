/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:24:12 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/10 17:12:00 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "../templates/stl_like.hpp"

/**
*	The element stocked in the AVL binary tree.
*
*	@param data		The data that is used for comparison between each node. There is 
*					no duplicate of this data in the tree.
*	@param parent	A pointer to a parent node.
*	@param left		A pointer to the left son of this node, the data' son will be inferior 
*					to this node' data.
*	@param right	A pointer to the right son of this node, the data' son will be inferior 
*					to this node' data.
*/
struct Node
{
	int		data;
	Node*	parent;
	Node*	left;
	Node*	right;
};


/* ------------------------------------------------------------- */
/* ------------------ create_binary_tree.cpp ------------------- */

/**
*	Creates a new node and assign data. left and right node ptr are NULL.
*
*	@param data		The content of the created node.
*	@return			The newly created node.
*/
Node* createNode(int data);

/**
*	Searches data in the tree and returns the element if it finds data.
*
*	@param root		Will start to look in the tree for the element from this node.
*	@param data		The data to search.
*	@param return	The element containing the data in the tree. NULL if no match occured for data.
*/
Node* searchNode(Node* root, int data);

/**
*	Searches for the element with the highest data in the tree.
*
*	@param root		First node of the tree.
*	@param return	The element containing the highest data in the tree.
*/
Node* searchMaxNode(Node *root);

/**
*	Searches for the element with the lowest data in the tree.
*
*	@param root		First node of the tree.
*	@param return	The element containing the lowest data in the tree.
*/
Node* searchMinNode(Node *root);

/**
*	Inserts data in the tree or a specific subtree by adding a new element, and 
*	then equilibrates the AVL tree if necessary. If element is already present, 
*	does nothing and return NULL.
*
*	@param root			First node of the tree.
*	@param insertPos	The starting node for the insertion in a specific subtree (will start to look for
*						a place for data from this node). If insertPos is root node, then it's an insertion
*						in the whole tree.
*	@param data			The data to insert in the tree.
*	@param return		The element inserted in the tree. NULL if the element already exist in the tree. 
*/
Node* insertNode(Node** root, Node* insertPos, int data);

/**
*	Deletes the node that matches data from the tree or a specific subtree, and then equilibrates the 
*	AVL tree if necessary. If element is missing, this function does nothing.
*
*	@param root			First node of the tree.
*	@param deletePos	The starting node for the deletion in a specific subtree (will start to look for
*						the data to delete from this node). If deletePos is root node, then it will looks 
*						for the element to delete in the whole tree.
*	@param data			The data to delete in the tree.
*	@param deallocate	Set it to true if the node to delete was allocated on the heap, false otherwise.
*	@param return		True if a deletion occured, false otherwise. 
*/
bool deleteNode(Node** root, Node* deletePos, int data, bool deallocate);


/* ------------------------------------------------------------- */
/* -------------------- balance_avl_tree.cpp ------------------- */

/**
*	Compares the heights of left and right subtrees.
*
*	@param node	His left and right subtrees will be compare.
*	@return		Difference between left and right subtrees. Will be negative if right
*				subtree > left subtree.
*/
int balanceOfSubtrees(Node* node);

/**
*	Does a right rotation between a node and his left child. The left child will go up
*	and take the position of this node; and this node will become the right child of the node
*	going up.
*
*	@param root				First node of the tree.
*	@param nodeGoingDown	Rotation will occured around this node.
*/
void rotateRight(Node** root, Node* nodeGoingDown);

/**
*	Does a left rotation between a node and his right child. The right child will go up
*	and take the position of this node; and this node will become the left child of the node
*	going up.
*
*	@param root				First node of the tree.
*	@param nodeGoingDown	Rotation will occured around this node.
*/
void rotateLeft(Node** root, Node* nodeGoingDown);

/**
*	Starts from a node in the AVL tree, and will check for this node and all the parent's node
*	until root if their balance (height of left and right subtree) is correct. If not, a rotation
*	(left or right) around the unbalanced node will occur in order restore the balance of the tree.
*
*	@param root	First node of the tree.
*	@param node	Will check the balance's node, and will check every parent until reaching root.
*/
void balanceTheTree(Node** root, Node* node);


/* ------------------------------------------------------------- */
/* ------------------- print_binary_tree.cpp ------------------- */

/**
*	Converts an int to a string.
*
*	@param str		The number to convert.
*	@return			The newly string containing the int.
*/
std::string toString(int i);

/**
*	Counts the number of words in a string, separated by spaces (whitespaces are not 
*	considered as separators).
*
*	@param str		The string containing the words.
*	@return			The number of words separated by a space.
*/
unsigned int countWordsInString(std::string const& str);

/**
*	Calculates the tree's height.
*
*	@param root		The root of the tree (start with first node, then call itself with left
*					and right node' sons until meeting leaf).
*	@param height	The heigth of the actual node. Increases this param by 1 each time 
*					it's calling itself on a node' son.
*	@param return	The height of the tree (-1 if empty, 0 if only root node).
*/
int heightTree(Node *root, int height);


/**
*	Fills a buffer with all the nodes->data for a certain deep in the tree.
*
*	@param root			The root of the tree (should be the first node).
*	@param buff			The buffer that will be filled with nodes.
*	@param actualHeight	The heigth of the actual node. Increases this param by 1 each time 
*						it's calling itself on a node' son.
*	@param printHeight	The height level that will be filled in the buffer.
*	@param return		The height of the tree (-1 if empty, 0 if only root node).
*/
int printLevel(Node *root, std::string* buff, int actualHeight, int printHeight);

/**
*	Prints the buffer that was filled with printLevel function. Can only print numbers
*	from -99 to 999 (width of 3).
*
*	@param buff		The buffer previously filled with printLevel.
*	@param width	The total width of the full line that will be printed.
*	@param nbNodes	Number of nodes inside the buffer.
*/
void printBuff(const std::string& buff, int width, int nbNodes);

/**
*	Prints a binary tree containing int as data, from numbers -99 to 999 (represents a width 
*	of 3).
*
*	@param root		First node of the tree.
*	@param height	Height of the tree.
*/
void printTree(Node *root, int height);


#endif