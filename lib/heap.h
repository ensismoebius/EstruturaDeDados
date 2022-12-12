/*
 * heap.h
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */

#ifndef LIB_HEAP_H_
#define LIB_HEAP_H_
#include "linkedList.h"
/*
 * Use this if you want that the list
 * behaves like a heap
 */
listItem* heapPop(list* heap);
listItem* heapPeek(list* heap);
void heapSort(float* array, unsigned int length);
void heapAdd(double value, list* heap);
void heapfyDown(list* heap);
void heapfyUp(list* heap);

#endif /* LIB_HEAP_H_ */
