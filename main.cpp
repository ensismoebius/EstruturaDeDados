#include "lib/binaryTree.h"
#include "lib/linkedList.h"
#include <iostream>

int main(int argc, char** argv)
{

    listItem* root = createItem(8);
    root = addBinaryTreeItem(root, 1);
    root = addBinaryTreeItem(root, 5);
    root = addBinaryTreeItem(root, 3);
    root = addBinaryTreeItem(root, 4);
    root = addBinaryTreeItem(root, 10);
    root = addBinaryTreeItem(root, 9);
    root = addBinaryTreeItem(root, 15);
    root = addBinaryTreeItem(root, 11);
    root = addBinaryTreeItem(root, 12);
    root = addBinaryTreeItem(root, 7);

    showAllInOrderRecursive(root);
    std::cout << "////////////////////////////////////////////////////" << std::endl;

    root = deleteBinaryTreeItem(root, 5);
    root = deleteBinaryTreeItem(root, 3);
    root = deleteBinaryTreeItem(root, 1);
    root = deleteBinaryTreeItem(root, 7);
    root = deleteBinaryTreeItem(root, 9);
    root = deleteBinaryTreeItem(root, 8);
    root = deleteBinaryTreeItem(root, 11);
    root = deleteBinaryTreeItem(root, 10);

    showAllInOrderRecursive(root);

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

    //	float* array = malloc(sizeof(float) * 8);
    //	array[0] = 10;
    //	array[1] = 30;
    //	array[2] = 5;
    //	array[3] = 20;
    //	array[4] = 15;
    //	array[5] = 17;
    //	array[6] = 1;
    //	array[7] = 3;
    //
    //	heapSort(array, 8);
    //
    //	for (int i = 0; i < 8; i++) {
    //		printf("%f\n", array[i]);
    //	}
    //
    //	list* heap = createList();
    //
    //	heapAdd(10, heap);
    //	heapAdd(30, heap);
    //	heapAdd(5, heap);
    //	heapAdd(20, heap);
    //	heapAdd(15, heap);
    //	heapAdd(17, heap);
    //	heapAdd(1, heap);
    //	heapAdd(3, heap);
    //
    //	listItem* peeked = heapPeek(heap);
    //	printf("Top heap item: %lf\n", *peeked->value);
    //
    //	listItem* poped = heapPop(heap);
    //	printf("Heap removed item: %lf\n", *poped->value);
    //
    //	peeked = heapPeek(heap);
    //	printf("Top heap item: %lf\n", *peeked->value);
    //
    //	clearList(heap);

    return 0;
}
