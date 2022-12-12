/*
 * heap.c
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

// If you want the list behaves like a heap:
static int getHeapParentIndex(int index) {
	return (index - 1) / 2;
}

static int getHeapLeftChildIndex(int index) {
	return index * 2 + 1;
}

static int getHeapRightChildIndex(int index) {
	return index * 2 + 2;
}

static char hasHeapLeftChild(int index, list* heap) {
	return getHeapLeftChildIndex(index) < *heap->size;
}

static char hasHeapRightChild(int index, list* heap) {
	return getHeapRightChildIndex(index) < *heap->size;
}

static char hasHeapParent(int index, list* heap) {
	return getHeapParentIndex(index) >= 0;
}

static listItem* getHeapParent(int index, list* heap) {
	return findOneByIndex(heap, getHeapParentIndex(index));
}
static listItem* getHeapLeftChild(int index, list* heap) {
	return findOneByIndex(heap, getHeapLeftChildIndex(index));
}
static listItem* getHeapRightChild(int index, list* heap) {
	return findOneByIndex(heap, getHeapRightChildIndex(index));
}

void heapfyUp(list* heap) {
	int index = *heap->size - 1;

	while (hasHeapParent(index, heap) && *getHeapParent(index, heap)->value > *findOneByIndex(heap, index)->value) {
		swapItems(heap, index, getHeapParentIndex(index));
		index = getHeapParentIndex(index);
	}
}

void heapfyDown(list* heap) {
	int index = 0;

	while (hasHeapLeftChild(index, heap)) {
		int smallerChildIndex = getHeapLeftChildIndex(index);

		if (hasHeapRightChild(index, heap) && *getHeapRightChild(index, heap)->value < *getHeapLeftChild(index, heap)->value) {
			smallerChildIndex = getHeapRightChildIndex(index);
		}

		if (*findOneByIndex(heap, index)->value < *findOneByIndex(heap, smallerChildIndex)->value) {
			break;
		} else {
			swapItems(heap, index, smallerChildIndex);
		}
		index = smallerChildIndex;
	}
}

void heapAdd(double value, list* heap) {
	addNextItem(heap, createItem(value));
	heapfyUp(heap);
}

listItem* heapPeek(list* heap) {
	if (*heap->size == 0) {
		printf("The heap is empty");
		return 0;
	}
	return findOneByIndex(heap, 0);
}
listItem* heapPop(list* heap) {
	if (heap->size == 0) return NULL;

	listItem* item = createItem(*heap->first->value);

	swapItems(heap, 0, *heap->size - 1);
	deleteByIndex(heap, *heap->size - 1);

	heapfyDown(heap);
	return item;
}

void heapSort(float* array, unsigned int length) {
	list* heap = createList();

	for (unsigned int i = 0; i < length; i++) {
		heapAdd(array[i], heap);
	}

	for (unsigned int i = 0; i < length; i++) {
		array[i] = (float) *heapPeek(heap)->value;
		swapItems(heap, 0, *heap->size - 1);
		deleteByIndex(heap, *heap->size - 1);
		heapfyDown(heap);
	}

	clearList(heap);
}

