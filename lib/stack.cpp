/*
 * stack.c
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */
#include <stdlib.h>
#include "linkedList.h"

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

	*list->size -= 1;

	return item;
}

listItem* peek(list* list) {
	return list->last;
}

