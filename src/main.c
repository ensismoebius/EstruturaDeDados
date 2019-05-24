#include <stdio.h>
#include "lib/linkedList.h"

int main(int argc, char **argv) {

//	listItem *root = createItem(8);
//	root = addBTreeItem(root, 4);
//	root = addBTreeItem(root, 10);
//	root = addBTreeItem(root, 9);
//	root = addBTreeItem(root, 15);
//	root = addBTreeItem(root, 12);

//	root = deleteBTreeItem(root, 5);
//	root = deleteBTreeItem(root, 3);
//	root = deleteBTreeItem(root, 1);
//	root = deleteBTreeItem(root, 7);
//	root = deleteBTreeItem(root, 9);
//	root = deleteBTreeItem(root, 8);
//	root = deleteBTreeItem(root, 11);
//	root = deleteBTreeItem(root, 10);
//
//	root = deleteBTreeItem(root, 14);
//	root = deleteBTreeItem(root, 17);
//	root = deleteBTreeItem(root, 13);
//	root = deleteBTreeItem(root, 13.5);
//	root = deleteBTreeItem(root, 20);
//	root = deleteBTreeItem(root, 18);
//	root = deleteBTreeItem(root, 12);

//	showAllInOrderRecursive(root);

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

//	listItem* heapPop(list* heap);
//	listItem* heapPeek(list* heap);
//	void heapAdd(double value, list* heap);

//TODO implementar o heapsort
//TODO consertar esse heap, tá bugado

	list* heap = createList();

	heapAdd(10, heap);
	heapAdd(30, heap);
	heapAdd(5, heap);
	heapAdd(20, heap);
	heapAdd(15, heap);
	heapAdd(17, heap);
	heapAdd(1, heap);
	heapAdd(3, heap);

	listItem* peeked = heapPeek(heap);
	printf("Top heap item: %lf\n", *peeked->value);

	listItem* poped = heapPop(heap);
	printf("Heap removed item: %lf\n", *poped->value);

	peeked = heapPeek(heap);
	printf("Top heap item: %lf\n", *peeked->value);

	clearList(heap);
	return 0;
}
