#include "lib/linkedList.h"

int main(int argc, char **argv) {

	listItem *root = createItem(12);

	addBTreeItem(root, 5);
	addBTreeItem(root, 3);
	addBTreeItem(root, 1);
	addBTreeItem(root, 7);
	addBTreeItem(root, 9);
	addBTreeItem(root, 8);
	addBTreeItem(root, 11);
	addBTreeItem(root, 10);

	addBTreeItem(root, 14);
	addBTreeItem(root, 17);
	addBTreeItem(root, 13);
	addBTreeItem(root, 13.5);
	addBTreeItem(root, 20);
	addBTreeItem(root, 18);

	removeBTreeItem(root, 5);

	showAllInOrderRecursive(root);

	return 0;
}
