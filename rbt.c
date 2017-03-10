#include "rbt.h"

typedef struct rbtValue//abstraction_level++
{
	void *value;
	int freq;
	int color;
	void (*display)(FILE *, void *);
	int (* compare)(void *, void *);
} rbtValue;

static rbtValue *newRBT_value(void (*disp)(FILE *,void *),int (*comp)(void *,void *))
{
	rbtValue *new_node = malloc(sizeof(vbstValue));
	new_node->value = NULL;
	new_node->freq = 1;
	new_node->color = 0;
	new_node->display = disp;
	new_node->compare = comp;

	return new_node;
}

static void displayRBT_value(FILE *fp, void *value)
{
	rbtValue *x = value;
	x->display(fp, x->value);//displays node value
	if(x->freq > 1) //gives freq value at output
	{
		fprintf(fp, "-%d", x->freq);
	}
	
	if (b->color == 0)
	{
		fprintf(fp, "-B");
	}
	else
	{
		fprintf(fp, "-R");
	}
}

static int compareRBT_value(void *x, void *y)
{
	rbtValue *ex = x;
	rbtValue *wy = y;
	int result = ex->compare(ex->value, wy->value);
	return result;
}

static int colorRBT(bstNode *b)
{
	if (b== 0)
	{
		return 0;
	}
	else
	{
		return ((rbtValue *) b->value)->color;
	}
}

rbt *newRBT(void (*disp)(FILE *fp,void *),int (*comp)(void *,void *))
{
	rbt *items = malloc(sizeof(rbt));
	items->tree = newBST(displayRBT_value, compareRBT_value);
	items->display = disp;
	items->compare = comp;
	items->size = 0;
	items->words = 0;
	items->color = 0;
	return items;
}

static int rightChild(bstNode *n)
{
	if(n == n->parent->right)
	{
		return n;
	}
}

static int leftChild(bstNode *n)
{
	if(n == n->parent->left)
	{
		return n;
	}
}

static bstNode *Uncle(bstNode *n)
{
	if(rightChild(n->parent))
	{
		return n->parent->parent->left; //granparents left child is uncle 
	}
	else
	{
		return n->parent->parent->right; //grandparents right child is uncle
	}
}

static int linear(bstNode *n)
{
	if(n == n->parent->right && n->parent == n->parent->parent->right)
	{
		return 1;//right linear
	}
	else if(n == n->parent->left && n->parent == n->parent->parent->left)
	{
		return -1;//left linear
	}
	else
	{
		return 0;//NOT linear
	}
}

static void rotate(bst *btree, bstNode *n)
{

}

static void insertionFixUp(bst *btree, bstNode *n)
{
	while (n == tree->root || colorRBT(n->parent) == 1)
	{
		if (colorRBT(Uncle(n)) == 1)//if uncle is red
		{
			bstNode *unc = Uncle(n);
			((rbtValue *) n->parent->value)->color = 0;//color parent black
			((rbtValue *) unc->value)->color = 0;//color uncle black
			((rbtValue *) n->parent->parent->value)->color = 1;//color grandparent red

			n = n->parent->parent->;
		}
		else
		{
			if(linear(n) == 0)//if n is not a linear order
			{	
				bstNode *oldN = n;
				bstNode *oldP = n->parent;
				rotate(btree, n);
				n = oldP;
				n->parent = oldN;
			}
			((rbtValue *) n->parent->value)->color = 0;//color parent black
			((rbtValue *) n->parent->parent->value)->color = 1;//color grandparent red
			rotate(b, n->parent);
		}
		((rbtValue *) btree->root->value)->color = 0;//color uncle black
	}
}

void insertRBT(rbt *tree,void *value)
{
	rbtValue *new_node = newRBT_value(tree->display, tree->compare);//new value
	new_node->value = value;//set value

	bstNode *search = findBSTNode(tree->tree, new_node);//search in trees tree for node existence

	if (search == 0)
	{
		insertBST(tree->tree, new_node);
		insertionFixUp(tree->tree, new_node);
		tree->size++;
		tree->words++;
	}
	else //if value is found don't insert it but update the freq and the word count
	{
		tree->words++;//don't insert, but it is an additional word
		
		//need to update frequecy of found value
		//bstnode does not have freq, so cast it to a vbst val
		((rbtValue *)(search->value))->freq++;
	}


}

int findRBT(rbt *tree,void *value)
{

}

void deleteRBT(rbt *,void *)
{
	printf("I'm here to drink milk and write code, and I'm all out of milk\n");
}

int sizeRBT(rbt *tree)
{
	return tree->size;
}

int wordsRBT(rbt *tree)
{
	return tree->words;
}

void statisticsRBT(rbt *tree,FILE *fp)
{
	return statisticsBST(tree->tree, fp);
}

void displayRBT(FILE *fp,rbt *tree)
{
	displayBST(fp, tree->tree);
}
