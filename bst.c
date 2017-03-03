#include "bst.h"
#include "queue.h"
#include <stdio.h>

#define min(a,b) (a<b?a:b)//min macro
#define max(a,b) (a>b?a:b)//max macro

bst *newBST(void (*d)(FILE *,void *),int (*comparator)(void *,void *))
{ 
	bst *items = malloc(sizeof(bst));
	items->root = 0;
	items->display = d;
	items->compare = comparator;
	return items;
}

bstNode *insertBST(bst *tree,void *value)
{ //returns inserted node
	bstNode *new_node = malloc(sizeof(bstNode));
	new_node->value = value;
	new_node->left = new_node->right = new_node->parent = 0;

	bstNode *helper_1 = tree->root; //helper function with the root
	bstNode *helper_2 = NULL;

	while(helper_1 != NULL)
	{
		helper_2 = helper_1;
		if(tree->compare(new_node->value, helper_1->value) < 0)
		{
			helper_1 = helper_1->left;
		}
		else
		{
			helper_1 = helper_1->right;
		}
	}

	new_node->parent = helper_2;
	if (helper_2 == NULL)
	{
		tree->root = new_node; //tree was empty
		new_node->parent = new_node; //point the root to itself if tree was empty
	}
	else if(tree->compare(new_node->value, helper_2->value) < 0)
	{
		helper_2->left = new_node;
	}
	else
	{
		helper_2->right = new_node;
	}
	++tree->size;
}

int findBST(bst *tree,void *value)
{ //returns 1 if found, 0 otherwise

	bstNode *x = tree->root;

	if (x == NULL)
	{
		return 0;
	}

	while (x != NULL)
	{
		if(tree->compare(x->value, value) == 0)
		{
			return 1;
		}
		else if(tree->compare(x->value, value) < 0)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}

}

bstNode *findBSTNode(bst *tree,void *value)
{ //returns 0 if not found

	bstNode *x = tree->root;

	if (x == NULL)
	{
		return 0;
	}

	while (x != NULL)
	{
		if(tree->compare(x->value, value) == 0)
		{
			return x;
		}
		else if(tree->compare(x->value, value) < 0)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}
}

bstNode *swapToLeafBSTNode(bstNode *n)
{ //returns leaf node holding the original value
	bstNode *hold = n;
	void *tmp;

	if (n->left == NULL && n->right == NULL)//if it's already a leaf
	{
		return n;
	}
	else if(n->left != NULL)//if n has a left child
	{
		hold = n->left;	//hold value for later swap
		while (hold->right != NULL)//after going left, search all the way right
		{						//only gets us part way in some cases, need recursive call
			hold = hold->right;
		}
		//after you've reached the end of the left childs rightmost child
		//swap the original value for the value in the leaf
		tmp = n->value;
		n->value = hold->value;
		hold->value = tmp;
		swapToLeafBSTNode(hold);//recursive call to go all the way to the leaf
	}
	else
	{
		hold = n->right;
		while(hold->left != NULL)
		{
			hold = hold->left;
		}
		tmp = n->value;
		n->value = hold->value;
		hold->value = tmp;
		swapToLeafBSTNode(hold);
	}
}

void pruneBSTNode(bst *tree, bstNode *n)
{ //disconnects n from tree
	if (n == tree->root && tree->root->left == NULL && tree->root->right == NULL)
	{
		tree->root = NULL;
	}
	if(n->left == NULL && n->right == NULL)
	{
		if(n->parent->left == n)
		{
			n->parent->left = NULL;
		}
		else
		{
			n->parent->right = NULL;
		}
	}
	tree->size--;
}

int sizeBST(bst *tree)
{
	return (tree->size);
}

static int maxDepth(bstNode *x)//max helper function
{
	if (x == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(maxDepth(x->left), maxDepth(x->right));
	}
}

static int minDepth(bstNode *x)//min helper function
{
	if(x == NULL)
	{
		return 0;
	}
	else
	{
    	return 1 + min(minDepth(x->left),minDepth(x->right));
	}
}

void statisticsBST(bst *tree,FILE *fp)
{ //displays min and max depths
	bstNode *x = tree->root;

	int min = minDepth(x);
	int max = maxDepth(x);
	fprintf(fp, "min: %d\n", min);
	fprintf(fp, "max: %d\n", max);
}

void displayBST(FILE *fp,bst *tree)
{ //displays tree, calls display function to display node value
	
	queue *newQ = newQueue(tree->display);
	enqueue(newQ, tree->root);//enqueue root and a null character to represent firts level
	enqueue(newQ, NULL);

	bstNode *x = malloc(sizeof(bstNode));

	int breadthLevel = 0;
	fprintf(fp, "%d: ", breadthLevel);

	if(tree->root == NULL)
	{
		return;
	}

	while (sizeQueue(newQ)) //while the queue is not empty 
	{
		x = dequeue(newQ); //begin dequeue
		if(sizeQueue(newQ) == 0)
		{
			fprintf(fp, "\n");
			break;
		}

		else if(x == NULL)	//if the dequeue value is null
		{
			fprintf(fp,"\n");
			enqueue(newQ, NULL);	//enqueue null to represent end of level
			breadthLevel++;
			fprintf(fp, "%d: ", breadthLevel);
		}

		else
		{
			if(x->left == NULL && x->right == NULL)
			{
				fprintf(fp, "=");
			}
			
			fprintf(fp, "\"");
			tree->display(fp, x->value);
			fprintf(fp, "\"");

			if(x == tree->root)
			{
				fprintf(fp, "("); 
				tree->display(fp, x->parent->value);
				fprintf(fp, ")- ");
			}
			else if(x->parent != NULL)
			{
				if(tree->compare(x->value, x->parent->value)<0)
				{
					fprintf(fp, "(\""); 
					tree->display(fp, x->parent->value);
					fprintf(fp, "\")-l "); 
				}
				else
				{
					fprintf(fp, "(\""); 
					tree->display(fp, x->parent->value);
					fprintf(fp, "\")-r "); 
				}

			}

			if(x->left != NULL)
			{
				enqueue(newQ, x->left);
			}
			if(x->right != NULL)
			{
				enqueue(newQ, x->right);
			}
		}
	}
}
