/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:24:12 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/08 16:53:25 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

struct Node
{
	int data;
	int balance;
	Node* parent;
	Node* left;
	Node* right;
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
*	Recursive function that recurses by comparing the data of each node with the new node data 
*	and calling itself with left / right side of the node depending on the result of 
*	the comparison, until it meets a leaf. Then inserting the element. If element is already
*	present, do nothing and return NULL.
*
*	@param root		First node of the tree.
*	@param data		The data to insert in the tree.
*	@param return	The element inserted in the tree. NULL if the element already exist in the tree. 
*/
Node* insertNode(Node* root, int data);

/**
*	Searches data in the tree and returns the element if it finds data.
*
*	@param root		First node of the tree.
*	@param data		The data to search.
*	@param return	The element containing the data in the tree. NULL if no match occured for data.
*/
Node* searchNode(Node* root, int data);

/**
*	Searches for the element whith the highest data in the tree.
*
*	@param root		First node of the tree.
*	@param return	The element containing the highest data in the tree.
*/
Node* searchMaxNode(Node *root);

/**
*	Searches for the element whith the lowest data in the tree.
*
*	@param root		First node of the tree.
*	@param return	The element containing the lowest data in the tree.
*/
Node* searchMinNode(Node *root);

/**
*	Deletes a node which matches data.
*
*	@param root		First node of the tree. If he's deleted, root will no point to 
*					the new root.
*	@param data		The data that need to be removed from the tree.
*	@param return	1 if an element matched data and was removed, 0 otherwise.
*/
bool deleteNode(Node** root, int data, bool deallocate);


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
*	Prints a binary tree containing int as data, from -99 to 999 (represents a width)
*	of 3).
*
*	@param root		First node of the tree.
*	@param height	Height of the tree.
*/
void printTree(Node *root, int height);


#endif