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

listItem *pop(list *list);
listItem *peek(list *list);
listItem *push(list *list, double value);

listItem *addNextItem(list *list, double value);
listItem *findOneByIndex(list *list, int index);
listItem *findOneByValue(list *list, double value);
listItem *addAfter(list *list, int index, double value);

void showAll(list *list);
void clearList(list *list);
void joinLists(list* list1, list* list2);
void deleteByIndex(list *list, int index);
void swapItems(list *list, int indexOne, int indexTwo);

#endif /* LIB_LINKEDLIST_ */
