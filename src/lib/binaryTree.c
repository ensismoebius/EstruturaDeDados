/*
 * binaryTree.c
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "linkedList.h"
#include "binaryTree.h"
static listItem* rotateCounterClockwise(listItem* oldRoot) {
	listItem* newRoot;
	listItem* temp;

	// do the rotations
	newRoot = oldRoot->right;
	temp = newRoot->left;
	newRoot->left = oldRoot;
	oldRoot->right = temp;

	// update balance factors
	newRoot->left->fatball -= 2; // updates old root
	newRoot->fatball -= 1; // update new root

	return newRoot;
}

static listItem* rotateClockwise(listItem* oldRoot) {
	listItem* newRoot;
	listItem* temp;

	newRoot = oldRoot->left;

	temp = newRoot->right;

	newRoot->right = oldRoot;
	oldRoot->left = temp;

	// update balance factors
	newRoot->left->fatball += 2; // updates old root
	newRoot->fatball += 1; // update new root

	return newRoot;
}

static listItem* doMaintance(listItem* bTreeRoot) {

	char fatball = bTreeRoot->fatball;
	char fatballLeft = bTreeRoot->left == NULL ? 0 : bTreeRoot->left->fatball;
	char fatballRight = bTreeRoot->right == NULL ? 0 : bTreeRoot->right->fatball;

	// balance factor is negative
	if (fatball > 0 && fatballRight > 0) {
		// rotate to left
		printf("to the left");
		bTreeRoot = rotateCounterClockwise(bTreeRoot);
	}

	if (fatball < 0 && fatballLeft < 0) {
		// rotate to the right
		printf("to the right");
		bTreeRoot = rotateClockwise(bTreeRoot);
	}

	if (fatball < 0 && fatballLeft > 0) {
		// double rotate: left and right
		printf("to the left and right");
		bTreeRoot->left = rotateCounterClockwise(bTreeRoot->left);
		bTreeRoot = rotateClockwise(bTreeRoot);
	}

	if (fatball > 0 && fatballLeft < 0) {
		// double rotate: right and left
		printf("to the right and left");
		bTreeRoot->right = rotateClockwise(bTreeRoot->right);
		bTreeRoot = rotateCounterClockwise(bTreeRoot);
	}

	return bTreeRoot;
}

listItem* addBinaryTreeItem(listItem* bTreeRoot, double value) {

	// There is no item in binary tree, create the root
	if (bTreeRoot == NULL) {
		printf("Null list!!");
		return NULL;
	}

	// Create new item
	listItem* newItem = createItem(value);

	// There is already some items add to the final
	bTreeRoot = addBtreeLeaf(bTreeRoot, newItem);

	return bTreeRoot;
}
listItem* findBtreeItem(listItem* bTreeRoot, double value) {

	// We got it!!
	if (*bTreeRoot->value == value) return bTreeRoot;

	// Not yet: Trying another branches
	if (value > *bTreeRoot->value) {
		return findBtreeItem(bTreeRoot->right, value);
	} else {
		return findBtreeItem(bTreeRoot->left, value);
	}

	// Nothing found!
	return NULL;
}

listItem* findSuitableReplacementValue(listItem* node, char* comesFromLeft, char* comesFromRight) {

	// finding the minimum at right
	int rightDepth = 0;
	listItem* rightSucessor = node->right;
	while (rightSucessor->left != NULL) {
		rightSucessor = rightSucessor->left;
		rightDepth++;
	}

	// finding the maximum at left
	int leftDepth = 0;
	listItem* leftSucessor = node->left;
	while (leftSucessor->right != NULL) {
		leftSucessor = leftSucessor->right;
		leftDepth++;
	}

	if (rightDepth >= leftDepth) {
		*comesFromLeft = 0;
		*comesFromRight = 1;
		return rightSucessor;
	}

	*comesFromLeft = 1;
	*comesFromRight = 0;
	return leftSucessor;
}

listItem* deleteBinaryTreeItem(listItem* bTreeRoot, double value) {

	if (bTreeRoot == NULL) return NULL;

	// the value is at left
	if (value < *bTreeRoot->value) {
		bTreeRoot->left = deleteBinaryTreeItem(bTreeRoot->left, value);
		bTreeRoot->fatball++;
		return bTreeRoot;
	}

	// the value is at right
	if (value > *bTreeRoot->value) {
		bTreeRoot->right = deleteBinaryTreeItem(bTreeRoot->right, value);
		bTreeRoot->fatball--;
		return bTreeRoot;
	}

	if (value != *bTreeRoot->value) return bTreeRoot;

	// got it! lets delete it

	// its a leaf
	if (bTreeRoot->left == NULL && bTreeRoot->right == NULL) {
		free(bTreeRoot->value);
		free(bTreeRoot);
		bTreeRoot = NULL;
		return bTreeRoot;
	}

	// its a branch with one child at right
	if (bTreeRoot->left == NULL) {
		listItem* nodeWillBeRemoved = bTreeRoot;
		bTreeRoot = bTreeRoot->right;

		free(nodeWillBeRemoved->value);
		free(nodeWillBeRemoved);
		nodeWillBeRemoved = NULL;

		return bTreeRoot;
	}

	// its a branch with one child at left
	if (bTreeRoot->right == NULL) {
		listItem* nodeWillBeRemoved = bTreeRoot;
		bTreeRoot = bTreeRoot->left;

		free(nodeWillBeRemoved->value);
		free(nodeWillBeRemoved);
		nodeWillBeRemoved = NULL;

		return bTreeRoot;
	}

	// its a branch with two children
	char comesFromLeft, comesFromRight;

	listItem* sucessor = findSuitableReplacementValue(bTreeRoot, &comesFromLeft, &comesFromRight);
	*bTreeRoot->value = *sucessor->value;

	if (comesFromLeft) {
		bTreeRoot->left = deleteBinaryTreeItem(bTreeRoot->left, *sucessor->value);
		return bTreeRoot;
	}

	if (comesFromRight) {
		bTreeRoot->right = deleteBinaryTreeItem(bTreeRoot->right, *sucessor->value);
	}
	return bTreeRoot;
}

/**
 * Don't use this, instead use addBinaryTreeItem
 * @see addBinaryTreeItem
 */
listItem* addBtreeLeaf(listItem* bTreeRoot, listItem* item) {

	if (*bTreeRoot->value == *item->value) {
		printf("Can't add existing values!");
		return bTreeRoot;
	}

	if (*item->value > *bTreeRoot->value) {
		if (bTreeRoot->right == NULL) {
			bTreeRoot->right = item;
			bTreeRoot->fatball++;
			return bTreeRoot;
		}

		bTreeRoot->right = addBtreeLeaf(bTreeRoot->right, item);
		bTreeRoot->fatball++;

		// Maintain as an AVL
		if (bTreeRoot->fatball > 1) {
			bTreeRoot = doMaintance(bTreeRoot);
		}

		return bTreeRoot;
	}

	if (*item->value < *bTreeRoot->value) {
		if (bTreeRoot->left == NULL) {
			bTreeRoot->left = item;
			bTreeRoot->fatball--;
			return bTreeRoot;

		}

		bTreeRoot->left = addBtreeLeaf(bTreeRoot->left, item);
		bTreeRoot->fatball--;

		// Maintain as an AVL
		if (bTreeRoot->fatball < -1) {
			bTreeRoot = doMaintance(bTreeRoot);
		}

		return bTreeRoot;
	}

	return bTreeRoot;
}

void showAllInOrderRecursive(listItem* bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->left);
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->right);
}
void showAllPreOrderRecursive(listItem* bTreeRoot) {
	if (bTreeRoot == NULL) return;
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->left);
	showAllInOrderRecursive(bTreeRoot->right);
}
void showAllPostOrderRecursive(listItem* bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->left);
	showAllInOrderRecursive(bTreeRoot->right);
	printf("%f\n", *bTreeRoot->value);
}

void showAllInOrderIterative(listItem* bTreeRoot) {

	list *pointersStack = createList();

	do {
		while (bTreeRoot != NULL) {
			push(pointersStack, createItem((long) bTreeRoot));
			bTreeRoot = bTreeRoot->left;
		}

		if (!empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = pop(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			printf("%f\n", *bTreeRoot->value);

			bTreeRoot = bTreeRoot->right;

			// Free memory
			free(i);
		}

	} while (!empty(pointersStack) || bTreeRoot != NULL);
}
void showAllPreOrderIterative(listItem* bTreeRoot) {

	list* pointersStack = createList();

	do {
		while (bTreeRoot != NULL) {
			push(pointersStack, createItem((long) bTreeRoot));
			printf("%f\n", *bTreeRoot->value);
			bTreeRoot = bTreeRoot->left;
		}

		if (!empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = pop(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			bTreeRoot = bTreeRoot->right;

			// Free memory
			free(i);
		}

	} while (!empty(pointersStack) || bTreeRoot != NULL);
}
void showAllPostOrderIterative(listItem* bTreeRoot) {

	list* pointersStack = createList();
	listItem* previous = NULL;

	do {
		while (bTreeRoot != NULL) {
			push(pointersStack, createItem((long) bTreeRoot));
			bTreeRoot = bTreeRoot->left;
		}

		while (bTreeRoot == NULL && !empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = peek(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			if (bTreeRoot->right == NULL || bTreeRoot->right == previous) {
				printf("%f\n", *bTreeRoot->value);
				pop(pointersStack);
				previous = bTreeRoot;
				bTreeRoot = NULL;
			} else {
				bTreeRoot = bTreeRoot->right;
			}
		}

	} while (!empty(pointersStack));
}

