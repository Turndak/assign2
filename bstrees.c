#include "integer.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
	bst *a = newBST(displayInteger, compareInteger);
	insertBST(a, newInteger(1));
	insertBST(a, newInteger(0));
	insertBST(a, newInteger(8));
	insertBST(a, newInteger(7));
	insertBST(a, newInteger(9));
	insertBST(a, newInteger(2));
	insertBST(a, newInteger(4));
	insertBST(a, newInteger(3));
	insertBST(a, newInteger(5));
	insertBST(a, newInteger(6));
	displayBST(stdout,a);
	//printf("\n");
	//statisticsBST(a,stdout);

	int x = findBST(a, newInteger(2));
	printf("1 if found: %d\n", x);

	bstNode *z = findBSTNode(a, newInteger(1));
	fprintf(stdout, "value of found node: ");
	a->display(stdout, z->value);
	printf("\n");

	printf("Size of BST: %d\n", sizeBST(a));
	statisticsBST(a, stdout);

	bstNode *f;
	f = swapToLeafBSTNode(z);
	displayBST(stdout,a);

	printf("\n");

	pruneBSTNode(a, f);
	displayBST(stdout,a);

	printf("\nSize of BST: %d\n", sizeBST(a));

}