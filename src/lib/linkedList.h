/*
 * list
 *
 *  Created on: 21 de mar de 2019
 *      Author: André Furlan
 */

#ifndef LIB_LINKEDLIST_
#define LIB_LINKEDLIST_

typedef struct li {
	double* value;
	struct li* next;
	struct li* previous;
} listItem;

typedef struct l {
	int* size;
	struct li* last;
	struct li* first;
} list;

/**
 * Creates a list and returns a pointer
 * to the first item
 */
list *createList();

char empty(list *list);

/*
 * If you want that the list
 * behave like an stack use this
 */
listItem *pop(list *list);
listItem *peek(list *list);
listItem *push(list *list, listItem *item);

/*
 * If you want that the list behaves like a regular
 * list use this
 */
listItem *addNextItem(list *list, listItem *item);
listItem *findOneByIndex(list *list, int index);
listItem *findOneByValue(list *list, double value);
listItem *addAfter(list *list, int index, listItem *item);

void clearList(list *list);
void joinLists(list* list1, list* list2);
void deleteByIndex(list *list, int index);
void swapItems(list *list, int indexOne, int indexTwo);

/*
 * Use this if you want that the list
 * behaves like a binary tree
 */
void clearBtree(listItem *bTreeRoot);
void addBtreeLeaf(listItem *bTreeRoot, listItem *item);
void removeBTreeItem(listItem *bTreeRoot, double value);

listItem *addBTreeItem(listItem *bTreeRoot, double value);
listItem *findBtreeItem(listItem *bTreeRoot, double value);

// Recursive methods
void showAllInOrderRecursive(listItem *bTreeRoot);
void showAllPreOrderRecursive(listItem *bTreeRoot);
void showAllPostOrderRecursive(listItem *bTreeRoot);

// Iterative methods
void showAllInOrderIterative(listItem *bTreeRoot);
void showAllPreOrderIterative(listItem *bTreeRoot);
void showAllPostOrderIterative(listItem *bTreeRoot);

/*
 * You can use this for all types
 */
void showAll(list *list);
listItem *createItem(double value);

#endif /* LIB_LINKEDLIST_ */
