#include "bst.h"
#include "queue.h"
#include <stdio.h>

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

}

int findBST(bst *tree,void *value)
{ //returns 1 if found, 0 otherwise

}

bstNode *findBSTNode(bst *tree,void *value)
{ //returns 0 if not found

}

bstNode *swapToLeafBSTNode(bstNode *n)
{ //returns leaf node holding the original value

}

void pruneBSTNode(bst *, bstNode *n)
{ //disconnects n from tree

}

int sizeBST(bst *)
{

}

void statisticsBST(bst *tree,FILE *fp)
{ //displays min and max depths

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
		//fprintf(fp,"%d: ", breadthLevel);
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
			//fprintf(fp, "%d: ", breadthLevel);
			tree->display(fp, x->value);
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
					fprintf(fp, "("); 
					tree->display(fp, x->parent->value);
					fprintf(fp, ")-l "); 
				}
				else
				{
					fprintf(fp, "("); 
					tree->display(fp, x->parent->value);
					fprintf(fp, ")-r "); 
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
