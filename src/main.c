#include <stdio.h>

#include "lib/calculator.h"

int main(int argc, char **argv) {

	char texto[] = "(1+2)*4";

	float result = evaluateExpression(texto, 6);

	printf("%f", result);
//	trim(texto);
//	puts(texto);

//	list* list2 = createList();
//	list* list1 = createList();
//	list* list3 = createList();
//
//	addNextItem(list1, 10.0);
//	addNextItem(list1, 11.0);
//	addNextItem(list1, 12.0);
//	addNextItem(list1, 13.0);
//	addNextItem(list1, 14.0);
//	addAfter(list1, -1, 9.0);
//	addNextItem(list1, 16.0);
//	addNextItem(list1, 17.0);
//	addAfter(list1, 5, 15.0);
//
//	addNextItem(list2, 0.0);
//	addNextItem(list2, 1.0);
//	addNextItem(list2, 2.0);
//	addNextItem(list2, 3.0);
//	addNextItem(list2, 4.0);
//	addNextItem(list2, 5.0);
//	addNextItem(list2, 6.0);
//	addNextItem(list2, 7.0);
//	addNextItem(list2, 8.0);
//
//	joinLists(list2, list1);
//	listItem* k = findOneByValue(list, 12.0);
//	deleteByIndex(list, 1);
//	swapItems(list, 3, 0);

//	showAll(list1);

//	push(list3, 100.0);
//	push(list3, 101.0);
//	push(list3, 102.0);
//	push(list3, 103.0);
//	push(list3, 104.0);
//	push(list3, 105.0);
//
//	pop(list3);
//	pop(list3);
//	pop(list3);
//
//	showAll(list3);
//
//	clearList(list3);
//
//	showAll(list3);
	return 0;
}
