/*
 * binaryTree.h
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */

#ifndef LIB_BINARYTREE_H_
#define LIB_BINARYTREE_H_

/*
 * Use this if you want that the list
 * behaves like a binary tree
 */
void clearBtree(listItem* bTreeRoot);
listItem* addBtreeLeaf(listItem* bTreeRoot, listItem* item);
listItem* addBTreeItem(listItem* bTreeRoot, double value);
listItem* findBtreeItem(listItem* bTreeRoot, double value);
listItem* deleteBTreeItem(listItem* bTreeRoot, double value);

// Recursive methods
void showAllInOrderRecursive(listItem* bTreeRoot);
void showAllPreOrderRecursive(listItem* bTreeRoot);
void showAllPostOrderRecursive(listItem* bTreeRoot);

// Iterative methods
void showAllInOrderIterative(listItem* bTreeRoot);
void showAllPreOrderIterative(listItem* bTreeRoot);
void showAllPostOrderIterative(listItem* bTreeRoot);

#endif /* LIB_BINARYTREE_H_ */
