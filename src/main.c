#include "lib/linkedList.h"

int main(int argc, char **argv) {

	listItem *root = createItem(10);

	addBTreeItem(root, 11);
	addBTreeItem(root, 9);
	addBTreeItem(root, 12);
	addBTreeItem(root, 8);
	addBTreeItem(root, 13);
	addBTreeItem(root, 7);
	addBTreeItem(root, 14);
	addBTreeItem(root, 6);
	addBTreeItem(root, 15);
	addBTreeItem(root, 5);

	showAllPostOrderRecursive(root);

	return 0;
}
