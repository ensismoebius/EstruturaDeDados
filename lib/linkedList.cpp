#include "linkedList.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Creates an listItem and returns a pointer to it
 */
listItem* createItem(double value)
{
    listItem* newItem = new listItem;
    newItem->value = new double;
    newItem->auxiliaryData = 0;
    *newItem->value = value;
    return newItem;
}

/**
 * Creates a list and returns a pointer to it
 */
list* createList()
{

    list* l = new list;
    l->first = NULL;
    l->last = NULL;
    l->size = new int;
    *l->size = 0;

    return l;
}

/**
 * The list is empty?
 */
char empty(list* list)
{
    return list->first == NULL;
}

/**
 * Adds an item to the list and returns
 * a pointer to the added value
 */
listItem* addNextItem(list* list, listItem* item)
{

    // "Puts" the item at the end
    item->right = NULL;
    item->left = list->last;

    if (list->last != NULL)
        list->last->right = item;

    if (list->first == NULL)
        list->first = item;

    list->last = item;

    // add one to size
    *list->size += 1;

    return item;
}

/**
 * Show all items within a nice format
 */
void showAll(list* list)
{

    if (list->size == 0) {
        printf("Empty list\n");
        return;
    }

    listItem* l = list->first;
    do {
        printf("Item %f\n", *l->value);
        l = l->right;
    } while (l != NULL);
}

/**
 * Returns the item given the index
 */
listItem* findOneByIndex(list* list, int index)
{
    if (*list->size <= index || index < 0) {
        printf("Index out of the bounds");
        exit(1);
    }

    if (index == 0)
        return list->first;
    if (index == *list->size - 1)
        return list->last;

    listItem* pointer = list->first;

    while (index--) {
        pointer = pointer->right;
    }

    return pointer;
}

/**
 * Returns the item given the value
 */
listItem* findOneByValue(list* list, double value)
{

    listItem* pointer = list->first;

    while (pointer != NULL && *pointer->value != value) {
        pointer = pointer->right;
    }

    return pointer;
}

/**
 * Delete an item given its index
 */
void deleteByIndex(list* list, int index)
{
    listItem* item = findOneByIndex(list, index);

    *list->size = *list->size - 1;

    if (item->left != NULL) {
        item->left->right = item->right;
    }

    if (item->right != NULL) {
        item->right->left = item->left;
    }

    if (item == list->first) {
        list->first = item->right;
    }

    if (item == list->last) {
        list->last = item->left;
    }
    free(item->value);
    free(item);
}

/**
 * Insert an item after another one given its index
 * @index -1 inserts before the first item
 */
listItem* addAfter(list* list, int index, listItem* item)
{

    if (index == -1) {

        listItem* current = findOneByIndex(list, 0);

        item->right = current;
        current->left = item;

        list->first = item;
        *list->size = *list->size + 1;

        return item;
    }

    listItem* current = findOneByIndex(list, index);

    if (current == NULL)
        return NULL;

    // the backup of the next item
    listItem* currentNextBackup = current->right;

    current->right = item;

    item->right = currentNextBackup;
    item->left = current;

    if (currentNextBackup != NULL) {
        currentNextBackup->left = item;
    }

    *list->size = *list->size + 1;
    return item;
}

/**
 * Swap items given its indexes
 */
void swapItems(list* list, int indexA, int indexB)
{
    listItem* a = findOneByIndex(list, indexA);
    listItem* b = findOneByIndex(list, indexB);

    double aValue = *a->value;

    *a->value = *b->value;
    *b->value = aValue;
}

/**
 * Join list2 and list1, they become one forever S2...
 */
void joinLists(list* list1, list* list2)
{

    if (list1->last == NULL || list2->first == NULL) {
        return;
    }

    list1->last->right = list2->first;
    list2->first->left = list1->last;

    list1->last = list2->last;
    list2->first = list1->first;

    *list1->size += *list2->size;

    free(list2->size);

    list2->size = list1->size;
}

/**
 * Erase entire list
 */
void clearList(list* list)
{

    if (list == NULL) {
        return;
    }

    listItem* l = list->last;
    listItem* b = NULL;

    while (l != NULL) {
        b = l->left;

        free(l->value);
        free(l);

        l = b;
    }

    *list->size = 0;
    list->first = list->last = NULL;
}
