/*
 * ktree.c
 *
 *  Created on: 30 de jun de 2019
 *      Author: ensis
 */

#include "ktree.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

listItem* createKtreeItem(double* value, unsigned int valueLenght)
{
    listItem* newItem = new listItem;
    newItem->value = new double;
    newItem->auxiliaryData = 0;

    for (unsigned int i = 0; i < valueLenght; i++) {
        newItem->value[i] = value[i];
    }
    return newItem;
}

static listItem* insert(listItem* kTreeRoot, double* value, unsigned int valueLenght, unsigned int dimension, unsigned int depth)
{
    if (kTreeRoot == NULL) {
        printf("Null list!!");
        return NULL;
    }

    // cmpIndex = 0 is x
    // cmpIndex = 1 is y
    unsigned cmpIndex = depth % dimension;

    if (value[cmpIndex] < kTreeRoot->value[cmpIndex]) {
        kTreeRoot->left = insert(kTreeRoot->left, value, valueLenght, dimension, depth + 1);
    } else {
        kTreeRoot->right = insert(kTreeRoot->right, value, valueLenght, dimension, depth + 1);
    }

    return kTreeRoot;
}
double euclidianDistance(double* point1, double* point2, unsigned int dimension)
{
    double sum = 0;

    for (unsigned int i = 0; i < dimension; i++) {
        sum += pow(point1[i] - point2[i], 2);
    }

    return sqrt(sum);
}
listItem* getNearestKtreeItem(listItem* kTreeRoot, double* value, unsigned int valueLenght, unsigned int dimension)
{

    listItem* candidate;
    double candidateRadius;

    listItem* result = kTreeRoot;
    double resultRadius = euclidianDistance(value, kTreeRoot->value, dimension);

    double leftRadius;
    double rightRadius;

    do {
        leftRadius = kTreeRoot->left == NULL ? LONG_MAX : euclidianDistance(value, kTreeRoot->left->value, dimension);
        rightRadius = kTreeRoot->right == NULL ? LONG_MAX : euclidianDistance(value, kTreeRoot->right->value, dimension);

        if (leftRadius < rightRadius) {
            candidateRadius = leftRadius;
            candidate = kTreeRoot->left;
        } else {
            candidateRadius = rightRadius;
            candidate = kTreeRoot->right;
        }

        if (candidateRadius < resultRadius) {
            kTreeRoot = candidate;

            result = candidate;
            resultRadius = candidateRadius;
        } else {
            break;
        }

    } while (kTreeRoot != NULL);

    return result;
}

listItem* addKtreeItem(listItem* kTreeRoot, double* value, unsigned int valueLenght, unsigned int dimension)
{
    return insert(kTreeRoot, value, valueLenght, dimension, 0);
}

char arePointsSame(double* point1, double* point2, unsigned int dimension)
{
    for (unsigned int i = 0; i < dimension; ++i)
        if (point1[i] != point2[i])
            return 0;

    return 1;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
char searchRec(listItem* root, double* point, unsigned int depth, unsigned int dimension)
{
    // Base cases
    if (root == NULL)
        return 0;
    if (arePointsSame(root->value, point, dimension))
        return 1;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % dimension;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->value[cd])
        return searchRec(root->left, point, depth + 1, dimension);

    return searchRec(root->right, point, depth + 1, dimension);
}

char exists(listItem* root, double* point, unsigned int dimension)
{
    // Pass current depth as 0
    return searchRec(root, point, 0, dimension);
}
