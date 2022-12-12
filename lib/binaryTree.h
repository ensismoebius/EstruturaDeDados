/*
 * binaryTree.h
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */

#ifndef LIB_BINARYTREE_H_
#define LIB_BINARYTREE_H_
#include "linkedList.h"
/*
 * Use this if you want that the list
 * behaves like a binary tree
 */
void clearBtree(listItem* binaryTreeRoot);
listItem* addBtreeLeaf(listItem* binaryTreeRoot, listItem* item);
listItem* addBinaryTreeItem(listItem* binaryTreeRoot, double value);
listItem* findBtreeItem(listItem* binaryTreeRoot, double value);
listItem* deleteBinaryTreeItem(listItem* binaryTreeRoot, double value);

// Recursive methods
void showAllInOrderRecursive(listItem* binaryTreeRoot);
void showAllPreOrderRecursive(listItem* binaryTreeRoot);
void showAllPostOrderRecursive(listItem* binaryTreeRoot);

// Iterative methods
void showAllInOrderIterative(listItem* binaryTreeRoot);
void showAllPreOrderIterative(listItem* binaryTreeRoot);
void showAllPostOrderIterative(listItem* binaryTreeRoot);

#endif /* LIB_BINARYTREE_H_ */
