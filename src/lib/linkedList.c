#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "linkedList.h"

listItem* rotateCounterClockwise(listItem* oldRoot) {
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

listItem* rotateClockwise(listItem* oldRoot) {
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

listItem* doMaintance(listItem* bTreeRoot) {

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

/**
 * Creates an listItem and returns a pointer to it
 */
listItem *createItem(double value) {
	listItem *newItem = malloc(sizeof(listItem));
	newItem->value = malloc(sizeof(double));
	newItem->fatball = 0;
	*newItem->value = value;
	return newItem;
}

/**
 * Creates a list and returns a pointer to it
 */
list *createList() {

	list *l = malloc(sizeof(list));
	l->first = NULL;
	l->last = NULL;
	l->size = malloc(sizeof(int));
	*l->size = 0;

	return l;
}

/**
 * The list is empty?
 */
char empty(list *list) {
	return list->first == NULL;
}

/**
 * Adds an item to the list and returns
 * a pointer to the added value
 */
listItem* addNextItem(list* list, listItem* item) {

	// "Puts" the item at the end
	item->right = NULL;
	item->left = list->last;

	if (list->last != NULL) list->last->right = item;

	if (list->first == NULL) list->first = item;

	list->last = item;

	// add one to size
	*list->size += 1;

	return item;
}

/**
 * Show all items within a nice format
 */
void showAll(list* list) {

	if (list->size == 0) {
		printf("Empty list\n");
		return;
	}

	listItem* l = list->first;
	do {
		printf("Item %f\n", *l->value);
		l = l->right;
	} while (l != NULL);
}

/**
 * Returns the item given the index
 */
listItem* findOneByIndex(list* list, int index) {
	if (*list->size <= index || index < 0) {
		printf("Index out of the bounds");
		exit(1);
	}

	if (index == 0) return list->first;
	if (index == *list->size - 1) return list->last;

	listItem* pointer = list->first;

	while (index--) {
		pointer = pointer->right;
	}

	return pointer;
}

/**
 * Returns the item given the value
 */
listItem* findOneByValue(list* list, double value) {

	listItem* pointer = list->first;

	while (pointer != NULL && *pointer->value != value) {
		pointer = pointer->right;
	}

	return pointer;
}

/**
 * Delete an item given its index
 */
void deleteByIndex(list *list, int index) {
	listItem* item = findOneByIndex(list, index);

	*list->size = *list->size - 1;

	if (item->left != NULL) {
		item->left->right = item->right;
	}

	if (item->right != NULL) {
		item->right->left = item->left;
	}

	if (item == list->first) {
		list->first = item->right;
	}

	if (item == list->last) {
		list->last = item->left;
	}
	free(item->value);
	free(item);
}

/**
 * Insert an item after another one given its index
 * @index -1 inserts before the first item
 */
listItem* addAfter(list* list, int index, listItem* item) {

	if (index == -1) {

		listItem* current = findOneByIndex(list, 0);

		item->right = current;
		current->left = item;

		list->first = item;
		*list->size = *list->size + 1;

		return item;
	}

	listItem* current = findOneByIndex(list, index);

	if (current == NULL) return NULL;

	// the backup of the next item
	listItem* currentNextBackup = current->right;

	current->right = item;

	item->right = currentNextBackup;
	item->left = current;

	if (currentNextBackup != NULL) {
		currentNextBackup->left = item;
	}

	*list->size = *list->size + 1;
	return item;
}

/**
 * Swap items given its indexes
 */
void swapItems(list* list, int indexA, int indexB) {
	listItem* a = findOneByIndex(list, indexA);
	listItem* b = findOneByIndex(list, indexB);

	double aValue = *a->value;

	*a->value = *b->value;
	*b->value = aValue;
}

/**
 * Join list2 and list1, they become one forever S2...
 */
void joinLists(list* list1, list* list2) {

	if (list1->last == NULL || list2->first == NULL) {
		return;
	}

	list1->last->right = list2->first;
	list2->first->left = list1->last;

	list1->last = list2->last;
	list2->first = list1->first;

	*list1->size += *list2->size;

	free(list2->size);

	list2->size = list1->size;
}

listItem* push(list* list, listItem* item) {
	return addNextItem(list, item);
}

listItem* pop(list* list) {
	listItem* item = list->last;

	if (item == NULL) return NULL;

	if (item->left != NULL) {
		list->last = item->left;
		item->left->right = NULL;
	} else {
		list->last = list->first = NULL;
	}

// item->previous = NULL;
	*list->size -= 1;

	return item;
}

listItem* peek(list* list) {
	return list->last;
}

/**
 * Erase entire list
 */
void clearList(list* list) {

	if (list == NULL) {
		return;
	}

	listItem* l = list->last;
	listItem* b = NULL;

	while (l != NULL) {
		b = l->left;

		free(l->value);
		free(l);

		l = b;
	}

	*list->size = 0;
	list->first = list->last = NULL;
}

listItem* addBTreeItem(listItem* bTreeRoot, double value) {

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

listItem* deleteBTreeItem(listItem* bTreeRoot, double value) {

	if (bTreeRoot == NULL) return NULL;

// the value is at left
	if (value < *bTreeRoot->value) {
		bTreeRoot->left = deleteBTreeItem(bTreeRoot->left, value);
		bTreeRoot->fatball++;
		return bTreeRoot;
	}

// the value is at right
	if (value > *bTreeRoot->value) {
		bTreeRoot->right = deleteBTreeItem(bTreeRoot->right, value);
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
		bTreeRoot->left = deleteBTreeItem(bTreeRoot->left, *sucessor->value);
		return bTreeRoot;
	}

	if (comesFromRight) {
		bTreeRoot->right = deleteBTreeItem(bTreeRoot->right, *sucessor->value);
	}
	return bTreeRoot;
}

/**
 * Don't use this, instead use addBTreeItem
 * @see addBTreeItem
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

// If you want the list behaves like a heap:

static int getHeapParentIndex(int index) {
	return (index - 1) / 2;
}

static int getHeapLeftChildIndex(int index) {
	return index * 2 + 1;
}

static int getHeapRightChildIndex(int index) {
	return index * 2 + 2;
}

static char hasHeapLeftChild(int index, list* heap) {
	return getHeapLeftChildIndex(index) < *heap->size;
}

static char hasHeapRightChild(int index, list* heap) {
	return getHeapRightChildIndex(index) < *heap->size;
}

static char hasHeapParent(int index, list* heap) {
	return getHeapParentIndex(index) >= 0;
}

static listItem* getHeapParent(int index, list* heap) {
	return findOneByIndex(heap, getHeapParentIndex(index));
}
static listItem* getHeapLeftChild(int index, list* heap) {
	return findOneByIndex(heap, getHeapLeftChildIndex(index));
}
static listItem* getHeapRightChild(int index, list* heap) {
	return findOneByIndex(heap, getHeapRightChildIndex(index));
}

void heapfyUp(list* heap) {
	int index = *heap->size - 1;

	while (hasHeapParent(index, heap) && *getHeapParent(index, heap)->value > *findOneByIndex(heap, index)->value) {
		swapItems(heap, index, getHeapParentIndex(index));
		index = getHeapParentIndex(index);
	}
}

void heapfyDown(list* heap) {
	int index = 0;

	while (hasHeapLeftChild(index, heap)) {
		int smallerChildIndex = getHeapLeftChildIndex(index);

		if (hasHeapRightChild(index, heap) && *getHeapRightChild(index, heap)->value < *getHeapLeftChild(index, heap)->value) {
			smallerChildIndex = getHeapRightChildIndex(index);
		}

		if (*findOneByIndex(heap, index)->value < *findOneByIndex(heap, smallerChildIndex)->value) {
			break;
		} else {
			swapItems(heap, index, smallerChildIndex);
		}
		index = smallerChildIndex;
	}
}

void heapAdd(double value, list* heap) {
	addNextItem(heap, createItem(value));
	heapfyUp(heap);
}

listItem* heapPeek(list* heap) {
	if (*heap->size == 0) {
		printf("The heap is empty");
		return 0;
	}
	return findOneByIndex(heap, 0);
}
listItem* heapPop(list* heap) {
	if (heap->size == 0) return NULL;

	listItem* item = createItem(*heap->first->value);

	swapItems(heap, 0, *heap->size - 1);
	deleteByIndex(heap, *heap->size - 1);

	heapfyDown(heap);
	return item;
}
