#include "lib/linkedList.h"

int main(int argc, char **argv) {

	listItem *root = createItem('e');

	addBTreeItem(root, 'b');
	addBTreeItem(root, 'a');
	addBTreeItem(root, 'c');
	addBTreeItem(root, 'd');
	addBTreeItem(root, 'g');
	addBTreeItem(root, 'f');
	addBTreeItem(root, 'h');
	addBTreeItem(root, 'i');

	showAllPostOrderIterative(root);




	return 0;
}
