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
listItem *push(list *list, double value);

/*
 * If you want that the list behaves like a regular
 * list use this
 */
listItem *addNextItem(list *list, double value);
listItem *findOneByIndex(list *list, int index);
listItem *findOneByValue(list *list, double value);
listItem *addAfter(list *list, int index, double value);

void clearList(list *list);
void joinLists(list* list1, list* list2);
void deleteByIndex(list *list, int index);
void swapItems(list *list, int indexOne, int indexTwo);

/*
 * Use this if you want that the list
 * behaves like a binary tree
 */
listItem *addBTreeItem(list *list, double value);
listItem *findBtreeItem(list *list, double index);
listItem *removeBTreeItem(list *list, double value);

void showAllInOrderRecursive(list *list);
void showAllPreOrderRecursive(list *list);
void showAllPostOrderRecursive(list *list);

void showAllInOrderIteractive(list *list);
void showAllPreOrderIteractive(list *list);
void showAllPostOrderIteractive(list *list);

/*
 * You can use this for all types
 */
void showAll(list *list);

#endif /* LIB_LINKEDLIST_ */
