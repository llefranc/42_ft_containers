/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/15 14:31:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

#include "../templates/stl_like.hpp"
#include "../avl_binary_tree_lib/binary_tree.hpp"

#include "../iterators/map_iterator.hpp"

namespace ft
{
	
	template < class Key,                                  		 	// map::key_type
			class T,                           	       			    // map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key, T> >    // map::allocator_type
	> class map
	{
		private:

			struct Node
			{
				ft::pair<const Key, T>	content;
				Node*					parent;
				Node*					left;
				Node*					right;
			};

		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef Key												key_type;
			typedef Compare											key_compare;
			typedef	Alloc											allocator_type;
			typedef	T												mapped_type;
			
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef	long int										difference_type;
			typedef	size_t											size_type;

			typedef	T&												reference;
			typedef	const T&										const_reference;
			typedef	T*												pointer;
			typedef	const T*										const_pointer;
			
			typedef typename ft::map_iterator<Key, T, Compare, Node, false>		iterator;
			typedef typename ft::map_iterator<Key, T, Compare, Node, true>		const_iterator;

			// typedef typename ft::rev_map_iterator<T, Node, false>	reverse_iterator;
			// typedef typename ft::rev_map_iterator<T, Node, true>	const_reverse_iterator;

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			
			// empty (1)	
			explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) :
				_size(0), _allocPair(alloc), _comp(comp)
			{
				_lastElem = createNode(ft::pair<const key_type, mapped_type>());
				_root = _lastElem;
			}

// range (2)	
// template <class InputIterator>
//   map (InputIterator first, InputIterator last,
//        const key_compare& comp = key_compare(),
//        const allocator_type& alloc = allocator_type());
// copy (3)	
// map (const map& x);

// ~map();
// copy (1)	
//  map& operator= (const map& x);



			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin()	{ return iterator(_lastElem->right, _lastElem); }
			const_iterator begin() const	{ return iterator(_lastElem->right, _lastElem); }
			iterator end()		{ return iterator(_lastElem, _lastElem); }
			const_iterator end() const	{ return iterator(_lastElem, _lastElem); }
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;
//  reverse_iterator rend();
// const_reverse_iterator rend() const;

			/* ------------------------------------------------------------- */
			/* -------------------------- CAPACITY ------------------------- */

			/**
			*	@return		True if the list' size is equal to 0.
			*/
			bool empty() const				{ return _size == 0; }

			/**
			*	@return		The size of the list.
			*/
			size_type size() const			{ return _size; }
			
			/**
			*	@return		The max possible size to be allocated.
			*/
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}


			/* ------------------------------------------------------------- */
			/* ---------------------- ELEMENTS ACCESS ---------------------- */	
			// mapped_type& operator[] (const key_type& k);

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */
			// single element (1)	
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				// Searches in the tree if val's key is already present and returns 
				// an iterator to the key inside the tree if it's the case
				Node* elemIsPresent = searchNode(_root, val.first);
				if (elemIsPresent)
					return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem), false);

				// Inserts the pair in the tree and returns an iterator to its position
				return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem), true);
			}
			
			// with hint (2)	
			// iterator insert (iterator position, const value_type& val);
			// range (3)	
			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			// (1)	
			void erase (iterator position)
			{
				deleteNode(position.getNonConstNode(), position->first);
			}
			// (2)	
			// size_type erase (const key_type& k);
			// (3)	
			// 	void erase (iterator first, iterator last);

			// 	void swap (map& x);
			// void clear();


			/* ------------------------------------------------------------- */
			/* ------------------------- OBSERVERS ------------------------- */
			
			// key_compare key_comp() const;
			// value_compare value_comp() const;
			
			
			/* ------------------------------------------------------------- */
			/* ------------------------ OPERATIONS ------------------------- */

			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;
			// size_type count (const key_type& k) const;
			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;

			//  iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;

			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>             equal_range (const key_type& k);


		private:

			Node*					_root;			// Pointer to the first element of the tree (root)
			Node*					_lastElem;		// Pointer to the last elem of the tree
			size_type				_size;			// Number of T values inside the list
			Alloc					_allocPair;		// Copy of allocator_type object
			Compare					_comp;			// Copy of comp key_compare predicate
			std::allocator<Node>	_allocNode;		// Node's allocator


			/* ------------------ AVL BINARY SEARCH TREE ------------------- */
			/* ----------- inserting / deleting inside the tree ------------ */

			/**
			*	Creates a new node and assign pair. left and right node ptr are NULL.
			*
			*	@param pair		The content (as a pair) of the created node.
			*	@return			The newly created node.
			*/
			Node* createNode(const value_type& pair)
			{
				Node* newNode = _allocNode.allocate(1);

				_allocPair.construct(&newNode->content, pair);
				newNode->parent = 0;
				newNode->left = 0;
				newNode->right = 0;

				return newNode;
			}

			/**
			*	Searches key in the tree and returns the element if it finds key.
			*
			*	@param root		Will start to look in the tree for the element from this node.
			*	@param key		The key to search.
			*	@param return	The element containing the key in the tree. NULL if no match occured for key.
			*/
			Node* searchNode(Node* root, key_type key)
			{
				// We reached a leaf
				if (!root)
					return 0;
				
				if (root->content.first == key)
					return root;
				
				// Recursive loop until we find key
				if (root->content.first > key && root->left && root->left != _lastElem)
					return searchNode(root->left, key);
				else if (root->content.first < key && root->right && root->right != _lastElem)
					return searchNode(root->right, key);

				// If we reach this step in the first searchNode func that was called
				// with root (first node of the tree), then element is missing.
				return 0;
			}

			/**
			*	Searches for the element with the highest key in the tree.
			*
			*	@param root		First node of the tree.
			*	@param return	The element containing the highest key in the tree.
			*/
			Node* searchMaxNode(Node *root)
			{
				// Until we meet tree's right extremity and circular link _lastElem
				if (root->right && root->right != _lastElem)
					return searchMaxNode(root->right);
				return root;
			}

			/**
			*	Searches for the element with the lowest key in the tree.
			*
			*	@param root		First node of the tree.
			*	@param return	The element containing the lowest key in the tree.
			*/
			Node* searchMinNode(Node *root)
			{
				// Until we meet tree's left extremity and circular link _lastElem
				if (root->left && root->left != _lastElem)
					return searchMinNode(root->left);
				return root;
			}

			/**
			*	Inserts a pair in the tree or a specific subtree by adding a new element, and 
			*	then equilibrates the AVL tree if necessary. If element is already present, 
			*	does nothing and return NULL.
			*
			*	@param insertPos	The starting node for the insertion in a specific subtree (will start to look for
			*						a place for data from this node). If insertPos is root node, then it's an insertion
			*						in the whole tree.
			*	@param data			The pair to insert in the tree.
			*	@param return		The element inserted in the tree. NULL if the element already exist in the tree. 
			*/
			Node* insertNode(Node* insertPos, const value_type& pair)
			{
				// Case creating first node of the tree
				if (_root == _lastElem)
				{
					_root = createNode(pair);
					
					_root->left = _lastElem;
					_root->right = _lastElem;
					_lastElem->left = _root;
					_lastElem->right = _root;

					return _root;
				}

				// Case key already exist in the tree
				if (insertPos->content.first == pair.first)
					return 0;

				// Recursive loop until we reach a leaf or fake last node (_lastElem)
				if (insertPos->content.first > pair.first && 
						insertPos->left && insertPos->left != _lastElem)
					return insertNode(insertPos->left, pair);
				else if (insertPos->content.first < pair.first && 
						insertPos->right && insertPos->right != _lastElem)
					return insertNode(insertPos->right, pair);

				// If we reach this step, we arrived to a leaf or to the max node / min node 
				// of the tree (they're both linked to _lastElem): inserting new node to his correct position
				Node *newNode = createNode(pair);

				// Case we reached a left or right leaf
				if (insertPos->content.first > newNode->content.first && !insertPos->left)
					insertPos->left = newNode;
				else if (insertPos->content.first < newNode->content.first && !insertPos->right)
					insertPos->right = newNode;

				// Case we reach min node or max node, inserting the node between min / max
				// and lastElem
				else if (insertPos->left && insertPos->content.first > newNode->content.first)
				{
					newNode->left = _lastElem;
					_lastElem->right = newNode;
					insertPos->left = newNode;
				}
				else if (insertPos->right && insertPos->content.first < newNode->content.first)
				{
					newNode->right = _lastElem;
					_lastElem->left = newNode;
					insertPos->right = newNode;
				}
					
				newNode->parent = insertPos;
				++_size;

				// Equilibrating the tree from newNode to root node
				balanceTheTree(&_root, newNode);

				return newNode;
			}

			/**
			*	Deletes the node that matches key from the tree or a specific subtree, and then equilibrates the 
			*	AVL tree if necessary. If element is missing, this function does nothing.
			*
			*	@param deletePos	The starting node for the deletion in a specific subtree (will start to look for
			*						the key to delete from this node). If deletePos is root node, then it will looks 
			*						for the element to delete in the whole tree.
			*	@param key			The key to delete in the tree.
			*	@param return		True if a deletion occured, false otherwise. 
			*/
			bool deleteNode(Node* deletePos, key_type key)
			{
				// Balance node will point to the first node impacted by the deletion (if we delete a node, 
				// it will be the parent node; if we delete root, it will be one of his son). 
				// We will then call balanceTheTree function to equilibrate the AVL tree
				Node* balanceNode = 0;
				
				// The node to delete, looking from deletePos node until we match key
				Node* del = searchNode(deletePos, key);

				// If element isn't present, nothing to delete
				if (!del)
					return false;
				
				/* --------------- CASE DELETING ROOT --------------- */
				// Case the node to delete is the root
				if (!del->parent)
				{
					// Root is the only node in the tree, it will be empty
					if (del->left == _lastElem && del->right == _lastElem)
					{
						_root = 0;
						_lastElem->left = _lastElem;
						_lastElem->right = _lastElem;
					}

					// Case only one son (left or right, need to equilibrate the tree
					// for only root)
					else if (del->left && del->right == _lastElem)
					{
						balanceNode = del->parent;
						_root = del->left;
						del->left->parent = 0;
						
						// Since the tree is AVL, if _root has only one son, this son is 
						// a leaf and has no left and right son. So the new root has to be 
						// llastElem from left and right side, but he's already 
						// linked to inked to _it from one side (in this case, left)
						_lastElem->left = del->left;
						del->left->right = _lastElem;
					}
					else if (del->left == _lastElem && del->right)
					{
						balanceNode = del->parent;
						_root = del->right;
						del->right->parent = 0;

						// Same explanation but with opposite side than just above
						_lastElem->right = del->right;
						del->right->left = _lastElem;
					}
					
					// Case two sons, need to switch the key of the node to delete with the highest key
					// in the left subtree, and to delete the node with this highest key in the left subtree
					else
					{
						Node* maxNode = searchMaxNode(del->left);
						
						// Need to destroy then construct for copying const variable)
						_allocPair.destroy(&del->content);
						_allocPair.construct(&del->content, maxNode->content);
						
						return deleteNode(del->left, maxNode->content.first);
					}
				}


				/* --------------- CASE DELETING NODE --------------- */
				// Case the node to delete is a leaf
				else if ((!del->left || del->left == _lastElem) && (!del->right || del->right == _lastElem))
				{
					balanceNode = del->parent;

					// Case min node / max node, linking differs for _lastElem
					Node* linkToParent = 0;
					if (del->left == _lastElem || del->right == _lastElem)
					{
						linkToParent = _lastElem;
						del->content.first <= del->parent->content.first ?
							_lastElem->right = del->parent : _lastElem->left = del->parent;
					}
						
					del->content.first <= del->parent->content.first ?
						del->parent->left = linkToParent : del->parent->right = linkToParent;
				}
				
				// Case only one son (only left son or only right son)
				else if ((del->left && del->left != _lastElem) && (!del->right || del->right == _lastElem))
				{
					balanceNode = del->parent;

					del->content.first <= del->parent->content.first ?
							del->parent->left = del->left : del->parent->right = del->left;
					del->left->parent = del->parent;

					// Case the node to delete is max node, need to relink _lastElem
					if (del->right == _lastElem)
					{
						_lastElem->left = del->left;
						del->left->right = _lastElem;
					}
				}
				else if ((!del->left || del->left == _lastElem) && del->right && del->right != _lastElem)
				{
					balanceNode = del->parent;

					del->content.first <= del->parent->content.first ?
							del->parent->left = del->right : del->parent->right = del->right;
					del->right->parent = del->parent;
					
					// Case the node to delete is max node, need to relink _lastElem
					if (del->left == _lastElem)
					{
						_lastElem->right = del->right;
						del->right->left = _lastElem;
					}
				}

				// Case two sons, need to switch the key of the node to delete with the highest key
				// in the left subtree, and to delete the node with this highest key in the left subtree
				else
				{
					Node* maxNode = searchMaxNode(del->left);

					// Need to destroy then construct for copying const variable)
					_allocPair.destroy(&del->content);
					_allocPair.construct(&del->content, maxNode->content);
					
					return deleteNode(del->left, maxNode->content.first);
				}

				// Equilibrating the tree from balanceNode to root node
				balanceTheTree(&_root, balanceNode);

				deallocateNode(del);
				return true;
			}

			/**
			*	Calls the destructor of node's content, and then deallocates the node.
			*
			*	@param del	The node to destroy / deallocate.
			*/
			void deallocateNode(Node* del)
			{
				_allocPair.destroy(&del->content);
				_allocNode.deallocate(del, 1);
			}


			/* ------------------ AVL BINARY SEARCH TREE ------------------- */
			/* -------------------- balancing the tree --------------------- */

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

			/**
			*	Does a right rotation between a node and his left child. The left child will go up
			*	and take the position of this node; and this node will become the right child of the node
			*	going up.
			*
			*	@param root				First node of the tree.
			*	@param nodeGoingDown	Rotation will occured around this node.
			*/
			void rotateRight(Node** root, Node* nodeGoingDown)
			{
				//   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
				//
				//
				//               Q                                 P              |
				//              / \     RIGHT ROTATION            / \             |
				//             P   C  ------------------->>>     A   Q            |
				//            / \                                   / \           |
				//           A   B                                 B   C          |

				Node* nodeGoingUp = nodeGoingDown->left;
				
				// Left Q' son become right P' son
				nodeGoingDown->left = nodeGoingUp->right;
				
				// Case right son is NULL to prevent segfault
				if (nodeGoingUp->right)
					nodeGoingUp->right->parent = nodeGoingDown;
				
				// rigth P' son is Q
				nodeGoingUp->right = nodeGoingDown;
				
				// Parent P = Parent Q
				nodeGoingUp->parent = nodeGoingDown->parent;
				
				// Determinating if Q has a parent (if not, Q is root) and if it's the case,
				// determinating if it's left son or right son. Then updating Q's parent with
				// his new son, P node
				if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
					nodeGoingDown->parent->left = nodeGoingUp;
				else if (nodeGoingDown->parent)
					nodeGoingDown->parent->right = nodeGoingUp;
				
				// Parent of Q is now P
				nodeGoingDown->parent = nodeGoingUp;

				// Updating root node if the rotation occured on root
				if (!nodeGoingUp->parent)
					*root = nodeGoingUp;
			}

			/**
			*	Does a left rotation between a node and his right child. The right child will go up
			*	and take the position of this node; and this node will become the left child of the node
			*	going up.
			*
			*	@param root				First node of the tree.
			*	@param nodeGoingDown	Rotation will occured around this node.
			*/
			void rotateLeft(Node** root, Node* nodeGoingDown)
			{
				//   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
				//
				//
				//               Q                                 P              |
				//              / \          LEFT ROTATION        / \             |
				//             P   C    <<<-------------------   A   Q            |
				//            / \                                   / \           |
				//           A   B                                 B   C          |

				Node* nodeGoingUp = nodeGoingDown->right;
				
				// Right P' son become left Q' son
				nodeGoingDown->right = nodeGoingUp->left;

				// Case Q left son is NULL to prevent segfault
				if (nodeGoingUp->left)
					nodeGoingUp->left->parent = nodeGoingDown;
				
				// Left Q' son is now P
				nodeGoingUp->left = nodeGoingDown;
				
				// Parent Q = Parent P
				nodeGoingUp->parent = nodeGoingDown->parent;
				
				// Determinating if P has a parent (if not, P is root) and if it's the case,
				// determinating if it's left son or right son. Then updating P's parent with
				// his new son, Q node
				if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
					nodeGoingDown->parent->left = nodeGoingUp;
				else if (nodeGoingDown->parent)
					nodeGoingDown->parent->right = nodeGoingUp;

				// Parent of P is now Q
				nodeGoingDown->parent = nodeGoingUp;

				// Updating root node if the rotation occured on root
				if (!nodeGoingUp->parent)
					*root = nodeGoingUp;
			}

			/**
			*	Starts from a node in the AVL tree, and will check for this node and all the parent's node
			*	until root if their balance (height of left and right subtree) is correct. If not, a rotation
			*	(left or right) around the unbalanced node will occured in order to restore tree's balance.
			*
			*	@param root	First node of the tree.
			*	@param node	Will check the balance's node, and will check every parent until reaching root.
			*/
			void balanceTheTree(Node** root, Node* node)
			{
				// Checking balance of subtrees every parents of this node until we 
				// reach root node
				while (node)
				{
					int balance;
					
					// Right right case (right subtree is deeper, and right right subtree aswell)
					if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
						rotateLeft(root, node);

					// Right left case (if balance of right node == 0, no difference between right 
					// right case and and right left case)
					else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
					{
						rotateRight(root, node->right);
						rotateLeft(root, node);
					}
					
					// Left left case (opposite of right right case)
					else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
						rotateRight(root, node);

					// Left right case (opposite of right left case)
					else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
					{
						rotateLeft(root, node->left);
						rotateRight(root, node);
					}
					node = node->parent;
				}
			}


			/* ------------------ AVL BINARY SEARCH TREE ------------------- */
			/* -------------- printing the tree for testing ---------------- */

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
				if (!root || root == _lastElem)
					return height - 1;

				// Exploring left side of the actual node, then right side
				int leftHeight = heightTree(root->left, height + 1);
				int rightHeight = heightTree(root->right, height + 1);

				return leftHeight > rightHeight ? leftHeight : rightHeight;
			}

			int printLevel(Node *root, std::string* buff, int actualHeight, int printHeight)
			{
				// We reached a NULL, returning
				if (!root || root == _lastElem)
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
					*buff += toString(root->content.first) + " ";

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
	};
} // namespace ft

#endif