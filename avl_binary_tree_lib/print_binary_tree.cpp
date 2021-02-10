/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary_tree.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:59:31 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/10 11:11:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

std::string toString(int i)
{
   std::stringstream ss;
   ss << i;
   return ss.str();
}

unsigned int countWordsInString(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), 
						std::istream_iterator<std::string>());
}

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

int printLevel(Node *root, std::string* buff, int actualHeight, int printHeight)
{
	// We reached a NULL, returning
	if (!root)
	{
		// If the NULL node level is inferior to the level we try to print,
		// adding 2 ^ (printHeight - actualHeight) nodes to the buffer
		// (represented by '|' character)
		if (actualHeight <= printHeight)
		{
			for (int i = pow(2, printHeight - actualHeight); i > 0; --i)
				*buff += "| ";
		}
		return actualHeight - 1;
	}

	// Adding the node to print to the buffer
	if (actualHeight == printHeight)
		*buff += toString(root->data) + " ";

	// Exploring left side of the actual node, then right side
	int leftHeight = printLevel(root->left, buff, actualHeight + 1, printHeight);
	int rightHeight = printLevel(root->right, buff, actualHeight + 1, printHeight);

	return leftHeight > rightHeight ? leftHeight : rightHeight;
}

void printBuff(const std::string& buff, int width, int nbNodes)
{
	int nbNodesPrinted = 0;

	// Calculating number of spaces that will be printed between each nodes
	size_t nbOfSpaces = std::count(buff.begin(), buff.end(), ' ');
	size_t widthSpace = (width - nbNodes * 5) / nbOfSpaces;

	// If number of total characters that will be printed (nodes + space separators)
	// will be inf to total width, we will add padding spaces between left and right branch
	int paddingSpace = width - (widthSpace * nbOfSpaces + nbNodes * 5);

	for (std::string::const_iterator it = buff.begin(); it != buff.end(); ++it)
	{
		// Delimiting nodes with equal number of spaces
		if (*it == ' ')
			{ std::cout.width(widthSpace);		std::cout << ""; }
		else
		{
			// Creating a string with the number to print (or empty if it's a non existing node
			// that we flagged with '|' character in printLevel func)
			std::string nb;
			while (it != buff.end() && *it != ' ')
				if (*it++ != '|')
					nb += *(it - 1);
					
			// Printing the node (handle numbers from -99 to 999, for width(3))
			std::cout << "[";	std::cout.width(3);		std::cout << nb << "]";

			// Repositionning iterator on first space we met in while loop (or end)
			--it;

			// If we printed half of nodes (so left branch), we add padding spaces
			++nbNodesPrinted;
			if (nbNodesPrinted == nbNodes / 2)
				{ std::cout.width(paddingSpace);		std::cout << ""; }
		}
	}
	std::cout << std::endl;
}

void printTree(Node *root, int height)
{
	if (!root)
	{
		std::cout << "The tree is empty\n";
		return;
	}
	
	// Calculating total width of last line (each node take 5 characters "[xxx]"
	// and are separated by 2 spaces, + 2 spaces at the beginning of the line and
	// 2 other spaces at the end)
	int width = pow(2, height) * 7 + 2 + 2;
	
	for (int i = 0; i <= height; ++i)
	{
		// Space at the beginning of the line to match last space that will be add
		// after last node
		std::string buff(" ");
		printLevel(root, &buff, 0, i);
		printBuff(buff, width, pow(2, i));
	}
}
