#include "lib/list"

int main(int argc, char **argv) {

	list* list = createList(10.0);
	addNextItem(list, 11.0);
	addNextItem(list, 12.0);
	addNextItem(list, 13.0);
	addNextItem(list, 14.0);
	addAfter(list, -1, 9.0);
	addNextItem(list, 16.0);
	addNextItem(list, 17.0);
	addAfter(list, 5, 15.0);

	//	listItem* k = findOneByValue(list, 12.0);
	//	deleteByIndex(list, 1);
	//	swapItems(list, 3, 0);

	showAll(list);

	return 0;
}
