#include "lib/linkedList.h"

//typedef struct lttr {
//	char value;
//	unsigned int amount;
//} letter;
//
//unsigned int g(char value) {
//	return (int) value;
//}
//
//unsigned int h(char* value, int mapSize) {
//	unsigned int wordLength = strlen(value);
//	unsigned int gfirst = g(value[0]);
//	unsigned int glast = g(value[wordLength - 1]);
//
//	return (wordLength + gfirst + glast) % mapSize;
//}
//
//void addLetterOcurrency(char letterCode, letter *list, unsigned int letterListSize, int *counter) {
//	unsigned int index;
//
//	for (index = 0; index < letterListSize; index++) {
//		if (list[index].value == letterCode) {
//			list[index].amount++;
//			return;
//		}
//	}
//
//	index--;
//	while (list[index].value != '\0')
//		index--;
//
//	list[index].amount = 1;
//	list[index].value = letterCode;
//	*counter = *counter + 1;
//}
//
//letter *createListOfLetters(int amountOfWords) {
//
//	// Give to us the amount of maximum needed positions
//	amountOfWords = (amountOfWords * 2) < 128 ? (amountOfWords * 2) : 128;
//
//	letter listOfLetters[amountOfWords];
//
//	// initializes the array
//	for (int i = 0; i < amountOfWords * 2; i++) {
//		listOfLetters[i].value = '\0';
//		listOfLetters[i].amount = 0;
//	}
//
//	return listOfLetters;
//}

int main(int argc, char **argv) {

//	const int wordsLength = 5;
//
//	int listOfLettersOccupied = 0;
//
//	char *listOfWords[wordsLength];
//	listOfWords[0] = "Andre";
//	listOfWords[1] = "Furlan";
//	listOfWords[2] = "Camila";
//	listOfWords[3] = "Rodrigues";
//	listOfWords[4] = "Oliveira";
//
//	letter *listOfLetters = createListOfLetters(wordsLength);
//
//	for (int i = 0; i < 5; i++) {
//		char* word = listOfWords[i];
//		char first = tolower(word[0]);
//		char last = tolower(word[strlen(word) - 1]);
//
//		addLetterOcurrency(first, listOfLetters, 10, &listOfLettersOccupied);
//		addLetterOcurrency(last, listOfLetters, 10, &listOfLettersOccupied);
//	}

	listItem *root = createItem(0);

	root = addBTreeItem(root, 1);
	root = addBTreeItem(root, 2);
	root = addBTreeItem(root, 3);
	root = addBTreeItem(root, 4);
	root = addBTreeItem(root, 5);
	root = addBTreeItem(root, 6);
	root = addBTreeItem(root, 7);
	root = addBTreeItem(root, 8);
	root = addBTreeItem(root, 9);

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

	showAllInOrderRecursive(root);

//	char texto[] = "((1+2)*4)-11";
//	float result = evaluateExpression(texto, strlen(texto));
//	printf("%f", result);

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
