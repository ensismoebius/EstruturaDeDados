/*
 * stack.h
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */

#ifndef LIB_STACK_H_
#define LIB_STACK_H_
#include "linkedList.h"
/*
 * If you want that the list
 * behave like an stack use this
 */
listItem* pop(list* list);
listItem* peek(list* list);
listItem* push(list* list, listItem* item);

#endif /* LIB_STACK_H_ */
