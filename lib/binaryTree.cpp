/*
 * binaryTree.c
 *
 *  Created on: 27 de mai de 2019
 *      Author: ensis
 */
#include "binaryTree.h"
#include "linkedList.h"
#include "stack.h"
#include <iostream>

static listItem* rotateCounterClockwise(listItem* oldRoot)
{
    listItem* newRoot;
    listItem* temp;

    // do the rotations
    newRoot = oldRoot->right;
    temp = newRoot->left;
    newRoot->left = oldRoot;
    oldRoot->right = temp;

    // update balance factors
    newRoot->left->auxiliaryData -= 2; // updates old root
    newRoot->auxiliaryData -= 1; // update new root

    return newRoot;
}

static listItem* rotateClockwise(listItem* oldRoot)
{
    listItem* newRoot;
    listItem* temp;

    newRoot = oldRoot->left;

    temp = newRoot->right;

    newRoot->right = oldRoot;
    oldRoot->left = temp;

    // update balance factors
    newRoot->left->auxiliaryData += 2; // updates old root
    newRoot->auxiliaryData += 1; // update new root

    return newRoot;
}

static listItem* doMaintance(listItem* binaryTreeRoot)
{

    char height = binaryTreeRoot->auxiliaryData;
    char heightLeft = binaryTreeRoot->left == NULL ? 0 : binaryTreeRoot->left->auxiliaryData;
    char heightRight = binaryTreeRoot->right == NULL ? 0 : binaryTreeRoot->right->auxiliaryData;

    // balance factor is negative
    if (height > 0 && heightRight > 0) {
        // rotate to left
        std::cout << "to the left" << std::endl;
        binaryTreeRoot = rotateCounterClockwise(binaryTreeRoot);
    }

    if (height < 0 && heightLeft < 0) {
        // rotate to the right
        std::cout << "to the right" << std::endl;
        binaryTreeRoot = rotateClockwise(binaryTreeRoot);
    }

    if (height < 0 && heightLeft > 0) {
        // double rotate: left and right
        std::cout << "to the left and right" << std::endl;
        binaryTreeRoot->left = rotateCounterClockwise(binaryTreeRoot->left);
        binaryTreeRoot = rotateClockwise(binaryTreeRoot);
    }

    if (height > 0 && heightLeft < 0) {
        // double rotate: right and left
        std::cout << "to the right and left" << std::endl;
        binaryTreeRoot->right = rotateClockwise(binaryTreeRoot->right);
        binaryTreeRoot = rotateCounterClockwise(binaryTreeRoot);
    }

    return binaryTreeRoot;
}

listItem* addBinaryTreeItem(listItem* binaryTreeRoot, double value)
{

    // There is no item in binary tree, create the root
    if (binaryTreeRoot == NULL) {
        std::cout << "Null list!!";
        return NULL;
    }

    // Create new item
    listItem* newItem = createItem(value);

    // There is already some items add to the final
    binaryTreeRoot = addBtreeLeaf(binaryTreeRoot, newItem);

    return binaryTreeRoot;
}
listItem* findBtreeItem(listItem* binaryTreeRoot, double value)
{

    // We got it!!
    if (*binaryTreeRoot->value == value)
        return binaryTreeRoot;

    // Not yet: Trying another branches
    if (value > *binaryTreeRoot->value) {
        return findBtreeItem(binaryTreeRoot->right, value);
    } else {
        return findBtreeItem(binaryTreeRoot->left, value);
    }

    // Nothing found!
    return NULL;
}

listItem* findSuitableReplacementValue(listItem* node, char* comesFromLeft, char* comesFromRight)
{

    // finding the minimum at right
    int rightDepth = 0;
    listItem* rightSucessor = node->right;
    while (rightSucessor->left != NULL) {
        rightSucessor = rightSucessor->left;
        rightDepth++;
    }

    // finding the maximum at left
    int leftDepth = 0;
    listItem* leftSucessor = node->left;
    while (leftSucessor->right != NULL) {
        leftSucessor = leftSucessor->right;
        leftDepth++;
    }

    if (rightDepth >= leftDepth) {
        *comesFromLeft = 0;
        *comesFromRight = 1;
        return rightSucessor;
    }

    *comesFromLeft = 1;
    *comesFromRight = 0;
    return leftSucessor;
}

listItem* deleteBinaryTreeItem(listItem* binaryTreeRoot, double value)
{

    if (binaryTreeRoot == NULL)
        return NULL;

    // the value is at left
    if (value < *binaryTreeRoot->value) {
        binaryTreeRoot->left = deleteBinaryTreeItem(binaryTreeRoot->left, value);
        binaryTreeRoot->auxiliaryData++;
        return binaryTreeRoot;
    }

    // the value is at right
    if (value > *binaryTreeRoot->value) {
        binaryTreeRoot->right = deleteBinaryTreeItem(binaryTreeRoot->right, value);
        binaryTreeRoot->auxiliaryData--;
        return binaryTreeRoot;
    }

    if (value != *binaryTreeRoot->value)
        return binaryTreeRoot;

    // got it! lets delete it

    // its a leaf
    if (binaryTreeRoot->left == NULL && binaryTreeRoot->right == NULL) {
        free(binaryTreeRoot->value);
        free(binaryTreeRoot);
        binaryTreeRoot = NULL;
        return binaryTreeRoot;
    }

    // its a branch with one child at right
    if (binaryTreeRoot->left == NULL) {
        listItem* nodeWillBeRemoved = binaryTreeRoot;
        binaryTreeRoot = binaryTreeRoot->right;

        free(nodeWillBeRemoved->value);
        free(nodeWillBeRemoved);
        nodeWillBeRemoved = NULL;

        return binaryTreeRoot;
    }

    // its a branch with one child at left
    if (binaryTreeRoot->right == NULL) {
        listItem* nodeWillBeRemoved = binaryTreeRoot;
        binaryTreeRoot = binaryTreeRoot->left;

        free(nodeWillBeRemoved->value);
        free(nodeWillBeRemoved);
        nodeWillBeRemoved = NULL;

        return binaryTreeRoot;
    }

    // its a branch with two children
    char comesFromLeft, comesFromRight;

    listItem* sucessor = findSuitableReplacementValue(binaryTreeRoot, &comesFromLeft, &comesFromRight);
    *binaryTreeRoot->value = *sucessor->value;

    if (comesFromLeft) {
        binaryTreeRoot->left = deleteBinaryTreeItem(binaryTreeRoot->left, *sucessor->value);
        return binaryTreeRoot;
    }

    if (comesFromRight) {
        binaryTreeRoot->right = deleteBinaryTreeItem(binaryTreeRoot->right, *sucessor->value);
    }
    return binaryTreeRoot;
}

/**
 * Don't use this, instead use addBinaryTreeItem
 * @see addBinaryTreeItem
 */
listItem* addBtreeLeaf(listItem* binaryTreeRoot, listItem* item)
{

    if (*binaryTreeRoot->value == *item->value) {
        std::cout << "Can't add existing values!";
        return binaryTreeRoot;
    }

    if (*item->value > *binaryTreeRoot->value) {
        if (binaryTreeRoot->right == NULL) {
            binaryTreeRoot->right = item;
            binaryTreeRoot->auxiliaryData++;
            return binaryTreeRoot;
        }

        binaryTreeRoot->right = addBtreeLeaf(binaryTreeRoot->right, item);
        binaryTreeRoot->auxiliaryData++;

        // Maintain as an AVL
        if (binaryTreeRoot->auxiliaryData > 1) {
            binaryTreeRoot = doMaintance(binaryTreeRoot);
        }

        return binaryTreeRoot;
    }

    if (*item->value < *binaryTreeRoot->value) {
        if (binaryTreeRoot->left == NULL) {
            binaryTreeRoot->left = item;
            binaryTreeRoot->auxiliaryData--;
            return binaryTreeRoot;
        }

        binaryTreeRoot->left = addBtreeLeaf(binaryTreeRoot->left, item);
        binaryTreeRoot->auxiliaryData--;

        // Maintain as an AVL
        if (binaryTreeRoot->auxiliaryData < -1) {
            binaryTreeRoot = doMaintance(binaryTreeRoot);
        }

        return binaryTreeRoot;
    }

    return binaryTreeRoot;
}

void showAllInOrderRecursive(listItem* binaryTreeRoot)
{
    if (binaryTreeRoot == NULL)
        return;
    showAllInOrderRecursive(binaryTreeRoot->left);
    std::cout << *binaryTreeRoot->value << std::endl;
    showAllInOrderRecursive(binaryTreeRoot->right);
}
void showAllPreOrderRecursive(listItem* binaryTreeRoot)
{
    if (binaryTreeRoot == NULL)
        return;
    std::cout << *binaryTreeRoot->value << std::endl;
    showAllPreOrderRecursive(binaryTreeRoot->left);
    showAllPreOrderRecursive(binaryTreeRoot->right);
}
void showAllPostOrderRecursive(listItem* binaryTreeRoot)
{
    if (binaryTreeRoot == NULL)
        return;
    showAllPostOrderRecursive(binaryTreeRoot->left);
    showAllPostOrderRecursive(binaryTreeRoot->right);
    std::cout << *binaryTreeRoot->value << std::endl;
}

void showAllInOrderIterative(listItem* binaryTreeRoot)
{

    list* pointersStack = createList();

    do {
        while (binaryTreeRoot != NULL) {
            push(pointersStack, createItem((long)binaryTreeRoot));
            binaryTreeRoot = binaryTreeRoot->left;
        }

        if (!empty(pointersStack)) {

            // Retrieves the listItem with pointer number
            listItem* i = pop(pointersStack);

            std::cout << *binaryTreeRoot->value << std::endl;

            binaryTreeRoot = binaryTreeRoot->right;

            // Free memory
            free(i);
        }

    } while (!empty(pointersStack) || binaryTreeRoot != NULL);
}
void showAllPreOrderIterative(listItem* binaryTreeRoot)
{

    list* pointersStack = createList();

    do {
        while (binaryTreeRoot != NULL) {
            push(pointersStack, createItem((long)binaryTreeRoot));
            std::cout << *binaryTreeRoot->value << std::endl;
            binaryTreeRoot = binaryTreeRoot->left;
        }

        if (!empty(pointersStack)) {

            // Retrieves the listItem with pointer number
            listItem* i = pop(pointersStack);

            binaryTreeRoot = binaryTreeRoot->right;

            // Free memory
            free(i);
        }

    } while (!empty(pointersStack) || binaryTreeRoot != NULL);
}
void showAllPostOrderIterative(listItem* binaryTreeRoot)
{

    list* pointersStack = createList();
    listItem* previous = NULL;

    do {
        while (binaryTreeRoot != NULL) {
            push(pointersStack, createItem((long)binaryTreeRoot));
            binaryTreeRoot = binaryTreeRoot->left;
        }

        while (binaryTreeRoot == NULL && !empty(pointersStack)) {

            // Retrieves the listItem with pointer number
            listItem* i = peek(pointersStack);

            if (binaryTreeRoot->right == NULL || binaryTreeRoot->right == previous) {
                std::cout << *binaryTreeRoot->value << std::endl;
                pop(pointersStack);
                previous = binaryTreeRoot;
                binaryTreeRoot = NULL;
            } else {
                binaryTreeRoot = binaryTreeRoot->right;
            }
        }

    } while (!empty(pointersStack));
}
