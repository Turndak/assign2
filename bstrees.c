#include "integer.h"
#include "bst.h"
#include "vbst.h"
#include <stdio.h>
#include <stdlib.h>


// void cleanFile(File *fp, bst *a)
// {
// 	char *str = cleanUp(fp);
// 	while (!feof(fp))
// 	{
// 		cleanUp(str);
// 		insertBST(a, newString(str));
// 		str = cleanUp(fp);
// 	}
// }


void main()
{
	/*bst *a = newBST(displayInteger, compareInteger);
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

	printf("\nSize of BST: %d\n", sizeBST(a));*/


/************************************************************/
	vbst *a = newVBST(displayInteger, compareInteger);
	insertVBST(a, newInteger(0));
	insertVBST(a, newInteger(1));
	insertVBST(a, newInteger(0));
	insertVBST(a, newInteger(8));
	insertVBST(a, newInteger(7));
	insertVBST(a, newInteger(9));
	insertVBST(a, newInteger(2));
	insertVBST(a, newInteger(4));
	insertVBST(a, newInteger(3));
	insertVBST(a, newInteger(5));
	insertVBST(a, newInteger(6));

	displayVBST(stdout, a);

	printf("\nFreq of 0 is: %d\n",findVBST(a, newInteger(0)));

	deleteVBST(a, newInteger(2));

	displayVBST(stdout, a);
	printf("\nFreq of 0 is: %d\n",findVBST(a, newInteger(0)));

	printf("Size: %d\n", sizeVBST(a));
	printf("Words: %d\n", wordsVBST(a));
	statisticsVBST(a, stdout);

}

