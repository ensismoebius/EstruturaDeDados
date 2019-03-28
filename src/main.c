#include "lib/list"

int main(int argc, char **argv) {
	list* list2 = createList(0.0);

	list* list1 = createList(10.0);
	addNextItem(list1, 11.0);
	addNextItem(list1, 12.0);
	addNextItem(list1, 13.0);
	addNextItem(list1, 14.0);
	addAfter(list1, -1, 9.0);
	addNextItem(list1, 16.0);
	addNextItem(list1, 17.0);
	addAfter(list1, 5, 15.0);

	addNextItem(list2, 1.0);
	addNextItem(list2, 2.0);
	addNextItem(list2, 3.0);
	addNextItem(list2, 4.0);
	addNextItem(list2, 5.0);
	addNextItem(list2, 6.0);
	addNextItem(list2, 7.0);
	addNextItem(list2, 8.0);


	joinLists(list2, list1);
	//	listItem* k = findOneByValue(list, 12.0);
	//	deleteByIndex(list, 1);
	//	swapItems(list, 3, 0);

	showAll(list1);

	return 0;
}
