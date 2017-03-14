#include "rbt.h"

typedef struct rbtValue//abstraction_level++
{
	void *value;
	int freq;
	int color;
	void (*display)(FILE *, void *);
	int (* compare)(void *, void *);
} rbtValue;



static void displayRBT_value(FILE *fp, void *value)
{
	rbtValue *x = value;
	x->display(fp, x->value);//displays node value
	if(x->freq > 1) //gives freq value at output
	{
		fprintf(fp, "-%d", x->freq);
	}
	
	if (x->color == 0)
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
	if (b == NULL)
	{
		return 0;
	}
	
	return ((rbtValue *) b->value)->color;
}

static rbtValue *newRBT_value(void (*disp)(FILE *,void *),int (*comp)(void *,void *))
{
	rbtValue *new_node = malloc(sizeof(rbtValue));
	new_node->value = NULL;
	new_node->freq = 1;
	new_node->color = 0;
	new_node->display = disp;
	new_node->compare = comp;

	return new_node;
}

rbt *newRBT(void (*disp)(FILE *fp,void *),int (*comp)(void *,void *))
{
	rbt *items = malloc(sizeof(rbt));
	items->tree = newBST(displayRBT_value, compareRBT_value);
	items->display = disp;
	items->compare = comp;
	items->size = 0;
	items->words = 0;
	return items;
}

static int rightChild(bstNode *n)
{
	if(n == n->parent->right)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static int leftChild(bstNode *n)
{
	if(n == n->parent->left)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static bstNode *Uncle(bstNode *n)
{
	if(rightChild(n->parent))
	{
		return n->parent->parent->left; //granparents left child is uncle 
	}
	else if(leftChild(n->parent))
	{
		return n->parent->parent->right; //grandparents right child is uncle
	}
	return 0;
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
     bstNode *left = n->left, *right = n->right;
     bstNode *paren = n->parent, *grand = n->parent->parent;

     // If n is a right child, rotate it left.
     if(rightChild(n)) {
          n->left = paren;
          paren->parent = n;
          paren->right = left;
		if(left != NULL)
		{
			left->parent = paren;
		}

		if(paren == btree->root)
		{
			n->parent = n;
			btree->root = n;
		}
		else
		{
			if(grand->left == paren)
			{
				grand->left = n;
			}
			else
			{
				grand->right = n;
			}

			n->parent = grand;
		}
	}

	else //rotate right
	{
		n->right = paren;
        paren->parent = n;
        paren->left = right;
		if(right != NULL)
		{
			right->parent = paren;
		}

		if(paren == btree->root)
		{
			n->parent = n;
			btree->root = n;
		}
		else
		{
			if(grand->right == paren)
			{
				grand->right = n;
			}
			else
			{
				grand->left = n;
			}

			n->parent = grand;
		}
	}
}

static void insertionFixUp(bst *tree, bstNode *n)
{
	while(1) 
	{
		if(tree->root == n)
		{
			break;
		}
		if(colorRBT(n->parent) == 0) 
		{
			break;
		}
		bstNode *uncle;
		uncle = Uncle(n);
		if(uncle && colorRBT(uncle) == 1) 
		{
		   ((rbtValue *) n->parent->value)->color = 0;
		   ((rbtValue *) uncle->value)->color = 0;
		   ((rbtValue *) n->parent->parent->value)->color = 1;
		   n = n->parent->parent;
		} 
		else 
		{
		   if(linear(n) == 0) 
		   {
		        bstNode *oldP = n->parent;
		        bstNode *oldN = n;
		        rotate(tree, n);
		        n = oldP;
		        n->parent = oldN;
		   }
		   ((rbtValue *) n->parent->value)->color = 0;
		   ((rbtValue *) n->parent->parent->value)->color = 1;
		   rotate(tree, n->parent);
		   break;
		}
	}
	((rbtValue *) tree->root->value)->color = 0;//color uncle black
}

void insertRBT(rbt *tree, void *value)
{
	rbtValue *new_node = newRBT_value(tree->display, tree->compare);//new value
	new_node->value = value;//set value
	bstNode *search = findBSTNode(tree->tree, new_node);//search in trees tree for node existence

	if (search == 0)
	{
		search = insertBST(tree->tree, new_node);
		new_node->color = 1;
		insertionFixUp(tree->tree, search);
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
	rbtValue *new_node = newRBT_value(tree->display, tree->compare);
	new_node->value = value;

	bstNode *search =  findBSTNode(tree->tree, new_node);
	if(search == NULL)
	{
		return 0;
	}
	else
	{
		return ((rbtValue *)(search->value))->freq;
	}
}

/*void deleteRBT(rbt *,void *)
{
	printf("I'm here to drink milk and write code, and I'm all out of milk\n");
}*/

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
