/*
 * ktree.h
 *
 *  Created on: 30 de jun de 2019
 *      Author: ensis
 */

#ifndef LIB_KTREE_H_
#define LIB_KTREE_H_

#include "linkedList.h"

char exists(listItem* root, double* point, unsigned int dimension);
char arePointsSame(double* point1, double* point2, unsigned int dimension);

listItem* createKtreeItem(double* value, unsigned int valueLenght);
listItem* addKtreeItem(listItem* kTreeRoot, double* value, unsigned int valueLenght, unsigned int dimension);

listItem* getNearestKtreeItem(listItem* kTreeRoot, double* value, unsigned int valueLenght, unsigned int dimension);
#endif /* LIB_KTREE_H_ */
