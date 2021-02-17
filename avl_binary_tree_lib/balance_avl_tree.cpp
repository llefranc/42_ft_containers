/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance_avl_tree.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:36:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/17 10:50:24 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.hpp"

int balanceOfSubtrees(Node* node)
{
    if (!node)
        return 0;
    return heightTree(node->left, 1) - heightTree(node->right, 1);
}

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