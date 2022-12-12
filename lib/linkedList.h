/*
 * list
 *
 *  Created on: 21 de mar de 2019
 *      Author: André Furlan
 */

#ifndef LIB_LINKEDLIST_
#define LIB_LINKEDLIST_

typedef struct li {
    char auxiliaryData;
	double* value;
	struct li* right;
	struct li* left;
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
list* createList();

char empty(list* list);

/*
 * If you want that the list behaves like a regular
 * list use this
 */
listItem* createItem(double value);
listItem* findOneByIndex(list* list, int index);
listItem* addNextItem(list* list, listItem* item);
listItem* findOneByValue(list* list, double value);
listItem* addAfter(list *list, int index, listItem *item);

void clearList(list* list);
void joinLists(list* list1, list* list2);
void deleteByIndex(list* list, int index);
void swapItems(list* list, int indexOne, int indexTwo);
void showAll(list* list);

#endif /* LIB_LINKEDLIST_ */
