#include "linkedList.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Creates an listItem and returns a pointer to it
 */
listItem *createItem(double value) {
	listItem *newItem = malloc(sizeof(listItem));
	newItem->value = malloc(sizeof(double));
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
listItem *addNextItem(list *list, listItem *item) {

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
void showAll(list *list) {

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
listItem *findOneByIndex(list *list, int index) {
	if (*list->size <= index || index < 0) {
		printf("Index out of the bounds");
		exit(1);
	}

	listItem* pointer = list->first;

	while (index--) {
		pointer = pointer->right;
	}

	return pointer;
}

/**
 * Returns the item given the value
 */
listItem *findOneByValue(list *list, double value) {

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
listItem *addAfter(list *list, int index, listItem *item) {

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
void swapItems(list *list, int indexOne, int indexTwo) {
	listItem* one = findOneByIndex(list, indexOne);
	listItem* two = findOneByIndex(list, indexTwo);

	if (one->right != NULL) {
		one->right->left = two;
	}

	if (two->left != NULL) {
		two->left->right = one;
	}

	if (two->right != NULL) {
		two->right->left = one;
	}

	if (one->left != NULL) {
		one->left->right = two;
	}

	if (one->right == two || two->right == one) {

		one->right = two->right;
		two->right = one;

		two->left = one->left;
		one->left = two;
		return;
	}

	if (one == list->first) {
		list->first = two;
	} else if (two == list->first) {
		list->first = one;
	}

	if (one == list->last) {
		list->last = two;
	} else if (two == list->last) {
		list->last = one;
	}

	listItem* item = one->right;
	one->right = two->right;
	two->right = item;

	item = two->left;
	two->left = one->left;
	one->left = item;
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

listItem *push(list *list, listItem *item) {
	return addNextItem(list, item);
}

listItem *pop(list *list) {
	listItem* item = list->last;

	if (item == NULL) return NULL;

	if (item->left != NULL) {
		list->last = item->left;
		item->left->right = NULL;
	} else {
		list->last = list->first = NULL;
	}

	// item->previous = NULL;
	*list->size += -1;

	return item;
}

listItem *peek(list *list) {
	return list->last;
}

/**
 * Erase entire list
 */
void clearList(list *list) {

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

listItem *addBTreeItem(listItem *bTreeRoot, double value) {

	// Create new item
	listItem* newItem = createItem(value);

	// There is no item in binary tree, create the root
	if (bTreeRoot == NULL) return newItem;

	// There is already some items add to the final
	addBtreeLeaf(bTreeRoot, newItem);

	return newItem;
}
listItem *findBtreeItem(listItem *bTreeRoot, double value) {

	// We got it!!
	if (*bTreeRoot->value == value) return bTreeRoot;

	// Not yet: Trying another branches
	if (value > *bTreeRoot->value) {
		findBtreeItem(bTreeRoot->right, value);
	} else {
		findBtreeItem(bTreeRoot->left, value);
	}

	// Nothing found!
	return NULL;
}
void removeBTreeItem(listItem *bTreeRoot, double value) {

	listItem *node = findBtreeItem(bTreeRoot, value);

	// finding the minimum at right
	int rightDepth = 0;
	listItem* rightParent = node;
	listItem* rightSucessor = node->right;
	while (rightSucessor->left != NULL) {
		rightParent = rightSucessor;
		rightSucessor = rightSucessor->left;
		rightDepth++;
	}

	// finding the maximum at left
	int leftDepth = 0;
	listItem* leftParent = node;
	listItem* leftSucessor = node->left;
	while (leftSucessor->right != NULL) {
		leftParent = leftSucessor;
		leftSucessor = leftSucessor->right;
		leftDepth++;
	}

	if (rightDepth >= leftDepth) {
		//grab node from right

		rightParent->left = rightSucessor->right;

		rightSucessor->left = node->left;
		rightSucessor->right = node->right;

		free(node->value);
		free(node);
		return;
	}

	//grab node from left

	leftParent->right = leftSucessor->left;

	leftSucessor->left = node->left;
	leftSucessor->right = node->right;

	free(node->value);
	free(node);

	node = leftSucessor;
}

/**
 * Don't use this, instead use addBTreeItem
 * @see addBTreeItem
 */
void addBtreeLeaf(listItem *bTreeRoot, listItem *item) {

	if (*bTreeRoot->value == *item->value) {
		printf("Can't add existing values!");
		return;
	}

	if (*item->value > *bTreeRoot->value) {
		if (bTreeRoot->right == NULL) {
			bTreeRoot->right = item;
			return;
		}

		addBtreeLeaf(bTreeRoot->right, item);
		return;
	}

	if (*item->value < *bTreeRoot->value) {
		if (bTreeRoot->left == NULL) {
			bTreeRoot->left = item;
			return;
		}

		addBtreeLeaf(bTreeRoot->left, item);
		return;
	}

}

void showAllInOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->left);
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->right);
}
void showAllPreOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->left);
	showAllInOrderRecursive(bTreeRoot->right);
}
void showAllPostOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->left);
	showAllInOrderRecursive(bTreeRoot->right);
	printf("%f\n", *bTreeRoot->value);
}

void showAllInOrderIterative(listItem *bTreeRoot) {

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
void showAllPreOrderIterative(listItem *bTreeRoot) {

	list *pointersStack = createList();

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
void showAllPostOrderIterative(listItem *bTreeRoot) {

	list *pointersStack = createList();
	listItem *previous = NULL;

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
