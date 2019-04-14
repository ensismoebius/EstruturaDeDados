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
	item->next = NULL;
	item->previous = list->last;

	if (list->last != NULL) list->last->next = item;

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
		l = l->next;
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
		pointer = pointer->next;
	}

	return pointer;
}

/**
 * Returns the item given the value
 */
listItem *findOneByValue(list *list, double value) {

	listItem* pointer = list->first;

	while (pointer != NULL && *pointer->value != value) {
		pointer = pointer->next;
	}

	return pointer;
}

/**
 * Delete an item given its index
 */
void deleteByIndex(list *list, int index) {
	listItem* item = findOneByIndex(list, index);

	*list->size = *list->size - 1;

	if (item->previous != NULL) {
		item->previous->next = item->next;
	}

	if (item->next != NULL) {
		item->next->previous = item->previous;
	}

	if (item == list->first) {
		list->first = item->next;
	}

	if (item == list->last) {
		list->last = item->previous;
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

		item->next = current;
		current->previous = item;

		list->first = item;
		*list->size = *list->size + 1;

		return item;
	}

	listItem* current = findOneByIndex(list, index);

	if (current == NULL) return NULL;

	// the backup of the next item
	listItem* currentNextBackup = current->next;

	current->next = item;

	item->next = currentNextBackup;
	item->previous = current;

	if (currentNextBackup != NULL) {
		currentNextBackup->previous = item;
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

	if (one->next != NULL) {
		one->next->previous = two;
	}

	if (two->previous != NULL) {
		two->previous->next = one;
	}

	if (two->next != NULL) {
		two->next->previous = one;
	}

	if (one->previous != NULL) {
		one->previous->next = two;
	}

	if (one->next == two || two->next == one) {

		one->next = two->next;
		two->next = one;

		two->previous = one->previous;
		one->previous = two;
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

	listItem* item = one->next;
	one->next = two->next;
	two->next = item;

	item = two->previous;
	two->previous = one->previous;
	one->previous = item;
}

/**
 * Join list2 and list1, they become one forever S2...
 */
void joinLists(list* list1, list* list2) {

	if (list1->last == NULL || list2->first == NULL) {
		return;
	}

	list1->last->next = list2->first;
	list2->first->previous = list1->last;

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

	if (item->previous != NULL) {
		list->last = item->previous;
		item->previous->next = NULL;
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
		b = l->previous;

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
		findBtreeItem(bTreeRoot->next, value);
	} else {
		findBtreeItem(bTreeRoot->previous, value);
	}

	// Nothing found!
	return NULL;
}
void removeBTreeItem(listItem *bTreeRoot, double value) {

	int leftDepth = 0;
	int rightDepth = 0;

	// finding the minimum at right
	listItem* rightNext = bTreeRoot->next;
	while (rightNext->previous != NULL) {
		rightDepth++;
	}

	// finding the maximum at left
	listItem* leftNext = bTreeRoot->previous;
	while (leftNext->next != NULL) {
		leftNext = leftNext->next;
		leftDepth++;
	}

	if (leftNext > rightNext) {
		//grab node from left
		return;
	}

	//grab node from right
	return;

	return NULL;
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
		if (bTreeRoot->next == NULL) {
			bTreeRoot->next = item;
			return;
		}

		addBtreeLeaf(bTreeRoot->next, item);
		return;
	}

	if (*item->value < *bTreeRoot->value) {
		if (bTreeRoot->previous == NULL) {
			bTreeRoot->previous = item;
			return;
		}

		addBtreeLeaf(bTreeRoot->previous, item);
		return;
	}

}

void showAllInOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->previous);
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->next);
}
void showAllPreOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	printf("%f\n", *bTreeRoot->value);
	showAllInOrderRecursive(bTreeRoot->previous);
	showAllInOrderRecursive(bTreeRoot->next);
}
void showAllPostOrderRecursive(listItem *bTreeRoot) {
	if (bTreeRoot == NULL) return;
	showAllInOrderRecursive(bTreeRoot->previous);
	showAllInOrderRecursive(bTreeRoot->next);
	printf("%f\n", *bTreeRoot->value);
}

void showAllInOrderIterative(listItem *bTreeRoot) {

	list *pointersStack = createList();

	do {
		while (bTreeRoot != NULL) {
			push(pointersStack, createItem((long) bTreeRoot));
			bTreeRoot = bTreeRoot->previous;
		}

		if (!empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = pop(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			printf("%f\n", *bTreeRoot->value);

			bTreeRoot = bTreeRoot->next;

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
			bTreeRoot = bTreeRoot->previous;
		}

		if (!empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = pop(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			bTreeRoot = bTreeRoot->next;

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
			bTreeRoot = bTreeRoot->previous;
		}

		while (bTreeRoot == NULL && !empty(pointersStack)) {

			// Retrieves the listItem with pointer number
			listItem* i = peek(pointersStack);

			// Retrieves the listItem itself
			bTreeRoot = (void*) (long) *i->value;

			if (bTreeRoot->next == NULL || bTreeRoot->next == previous) {
				printf("%f\n", *bTreeRoot->value);
				pop(pointersStack);
				previous = bTreeRoot;
				bTreeRoot = NULL;
			} else {
				bTreeRoot = bTreeRoot->next;
			}
		}

	} while (!empty(pointersStack));
}
