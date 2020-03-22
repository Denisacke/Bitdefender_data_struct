#include "cctree.h"
#include "common.h"
#include <stdio.h>


int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int TreeCreateNode(CC_TREE_NODE **Node, int Value)
{

	CC_TREE_NODE *node = (CC_TREE_NODE *)malloc(sizeof(CC_TREE_NODE));

	if (NULL == node)
	{
		*Node = NULL;
		return -1;
	}

	node->Left = NULL;
	node->Right = NULL;
	node->Parent = NULL;
	node->Height = 1;
	node->Value = Value;
	*Node = node;
	return 0;

}

CC_TREE_NODE* TreeRightRotate(CC_TREE_NODE* y)
{
	CC_TREE_NODE* x = y->Left;
	CC_TREE_NODE* T2 = x->Right;

	x->Right = y;
	y->Left = T2;

	if (NULL == x->Left && NULL != x->Right)
	{
		x->Height = x->Right->Height + 1;
	}
	else
		if (NULL == x->Right && NULL != x->Left)
		{
			x->Height = x->Left->Height + 1;
		}	
		else
			if (NULL != x->Right && NULL != x->Left)
			{
				x->Height = Max(x->Left->Height, x->Right->Height) + 1;
			}
			else
				x->Height = 1;
	if (NULL == y->Left && NULL != y->Right)
	{
		y->Height = y->Right->Height + 1;
	}
	else
		if (NULL == y->Right && NULL != y->Left)
		{
			y->Height = y->Left->Height + 1;
		}
		else
			if (NULL != y->Left && NULL != y->Right)
			{
				y->Height = Max(y->Left->Height, y->Right->Height) + 1;
			}
			else
				y->Height = 1;
	x->Parent = y->Parent;
	if (NULL != y->Parent) 
	{
		if (y->Parent->Left == y)
		{
			x->Parent->Left = x;
		}
		else
			if (y->Parent->Right == y)
			{
				x->Parent->Right = x;
			}
				
	}
	
	y->Parent = x;
	return x;
}

CC_TREE_NODE* TreeLeftRotate(CC_TREE_NODE* x)
{
	//printf("left rotate %d\n", x->Value);
	CC_TREE_NODE* y = x->Right;
	CC_TREE_NODE* T2 = y->Left;

	y->Left = x;
	x->Right = T2;
	if (NULL == x->Left && NULL != x->Right)
	{
		x->Height = x->Right->Height + 1;
	}
	else
		if (NULL == x->Right && NULL != x->Left)
		{
			x->Height = x->Left->Height + 1;
		}
		else
			if (NULL != x->Right && NULL != x->Left)
			{
				x->Height = Max(x->Left->Height, x->Right->Height) + 1;
			}
			else
				x->Height = 1;
	if (NULL == y->Left && NULL != y->Right)
	{
		y->Height = y->Right->Height + 1;
	}
	else
		if (NULL == y->Right && NULL != y->Left)
		{
			y->Height = y->Left->Height + 1;
		}
		else
			if (NULL != y->Left && NULL != y->Right)
			{
				y->Height = Max(y->Left->Height, y->Right->Height) + 1;
			}
			else
				y->Height = 1;

	y->Parent = x->Parent;
	if (NULL != x->Parent) 
	{
		if (x->Parent->Left == x)
		{
			y->Parent->Left = y;
		}
		else
			if (x->Parent->Right == x)
			{
				y->Parent->Right = y;
			}
				
	}
	x->Parent = y;

	return y;
}

int TreeGetBalance(CC_TREE_NODE* N)
{
	if (NULL == N)
	{
		return -1;
	}
	int right, left;
	if (NULL == N->Left)
	{
		left = 0;
	}
	else
		left = N->Left->Height;
	if (NULL == N->Right)
	{
		right = 0;
	}
	else
		right = N->Right->Height;
	return left - right;
}
void TreeBalanceHeight(CC_TREE_NODE* node)
{
	if (NULL == node->Left && NULL != node->Right)
	{
		node->Height = node->Right->Height + 1;
	}
	else
		if (NULL != node->Left && NULL == node->Right)
		{
			node->Height = node->Left->Height + 1;
		}
		else
			if (NULL != node->Left && NULL != node->Right)
			{
				node->Height = 1 + Max(node->Left->Height, node->Right->Height);
			}
}
CC_TREE_NODE* TreeRotationCase(CC_TREE_NODE* node, int value)
{
	if (NULL == node->Left && NULL != node->Right)
	{
		node->Height = node->Right->Height + 1;
	}
	else
		if (NULL != node->Left && NULL == node->Right)
		{
			node->Height = node->Left->Height + 1;
		}
		else
			if (NULL != node->Left && NULL != node->Right)
			{
				node->Height = 1 + Max(node->Left->Height, node->Right->Height);
			}
			else
				node->Height = 1;
	int balance = TreeGetBalance(node);

	if (balance > 1 && value < node->Left->Value)
	{
		return TreeRightRotate(node);
	}
		
	if (balance < -1 && value > node->Right->Value)
	{
		return TreeLeftRotate(node);
	}
		
	if (balance > 1 && value > node->Left->Value)
	{
		node->Left = TreeLeftRotate(node->Left);
		return TreeRightRotate(node);
	}

	if (balance < -1 && value < node->Right->Value)
	{
		node->Right = TreeRightRotate(node->Right);
		return TreeLeftRotate(node);
	}

	return node;
}

void TreePostorder(CC_TREE_NODE* node, int *Index, int *Value)
{
	if (NULL == node)
	{
		return;
	}
		

    TreePostorder(node->Left, Index, Value);
	TreePostorder(node->Right, Index, Value);
	if ((*Index) == 1)
	{
		*Value = node->Value;
		(*Index)--;
		return;
	}
	else
		if ((*Index) > 1) {
			(*Index)--;
		}
		else
			return;
	
}
void TreeInorder(CC_TREE_NODE* node, int *Index, int *Value)
{
	if (NULL == node)
		return;
	
	TreeInorder(node->Left, Index, Value);
	if ((*Index) == 1)
	{
		*Value = node->Value;
		(*Index)--;
		return;
	}
	else
		if ((*Index) > 1) 
		{
			(*Index)--;
		}
		else
			return;
	TreeInorder(node->Right, Index, Value);
}

void TreePreorder(CC_TREE_NODE* node, int *Index, int *Value) {

	if (NULL == node)
	{
		return;
	}
	if ((*Index) == 1)
	{
		*Value = node->Value;
		(*Index)--;
		return;
	}
	else
		if ((*Index) > 1) 
		{
			(*Index)--;
		}
		else
			return;
		
    TreePreorder(node->Left, Index, Value);

    TreePreorder(node->Right, Index, Value);
}
void TreeDeleteAllNodes(CC_TREE_NODE *tree)
{
	if (NULL == tree)
		return;

	TreeDeleteAllNodes(tree->Left);
	TreeDeleteAllNodes(tree->Right);
	free(tree);
}

CC_TREE_NODE* TreeSearchNode(CC_TREE_NODE* root, int value)
{
	if (NULL == root)
		return root;
	if (root->Value == value)
	{
		return root;
	}
	if (root->Value < value)
	{
		
		return TreeSearchNode(root->Right, value);
	}
	
	return TreeSearchNode(root->Left, value);
}

CC_TREE_NODE* minValueNode(CC_TREE_NODE* node)
{
	CC_TREE_NODE* current = node;

	while (current && NULL != current->Left)
	{
		current = current->Left;
	}
	return current;
}

CC_TREE_NODE* TreeDeleteNode(CC_TREE_NODE *root, int value)
{

	if (NULL == root)
	{
		return root;
	}

	if (value < root->Value)
	{
		root->Left = TreeDeleteNode(root->Left, value);
	}	
	else 
		if (value > root->Value)
		{
			root->Right = TreeDeleteNode(root->Right, value);
		}
	else
	{
		if (NULL == root->Left)
		{
			CC_TREE_NODE *temp = root->Right;
			free(root);
			return temp;
		}
		else if (NULL == root->Right)
		{
			CC_TREE_NODE *temp = root->Left;
			free(root);
			return temp;
		}
		CC_TREE_NODE* temp = minValueNode(root->Right);

		root->Value = temp->Value;

		root->Right = TreeDeleteNode(root->Right, temp->Value);
	}
	return root;
}


int TreeCreate(CC_TREE **Tree)
{
	if (NULL == Tree)
	{
		return -1;
	}

	CC_TREE *tree = (CC_TREE*)malloc(sizeof(CC_TREE));

	if (NULL == tree)
	{
		*Tree = NULL;
		return -1;
	}

	tree->Count = 0;
	tree->Height = 0;
	tree->Root = NULL;
	
	*Tree = tree;

	return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
	if (NULL == Tree)
	{
		return -1;
	}

	CC_TREE *tree = *Tree;

	TreeDeleteAllNodes(tree->Root);

	free(*Tree);
	*Tree = NULL;

	return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
	if (NULL == Tree)
	{
		return -1;
	}

	CC_TREE_NODE *aux = Tree->Root;
	CC_TREE_NODE *node;
	if (TreeCreateNode(&node, Value) != 0)
	{
		return -1;
	}
	Tree->Count++;
	if (NULL == Tree->Root) 
	{
		Tree->Root = node;
		return 0;
	}
	CC_TREE_NODE *aux2 = aux;
	while (NULL != aux2) 
	{
		if (aux2->Value >= node->Value) 
		{
			aux2 = aux2->Left;
			if (NULL == aux2) {
				node->Parent = aux;
				aux->Left = node;
				while (node != Tree->Root) 
				{
					TreeBalanceHeight(node->Parent);
					node = node->Parent;
				}
				Tree->Root = TreeRotationCase(Tree->Root, Value);
				return 0;
			}
			else 
			{
				aux = TreeRotationCase(aux, Value);
				if (NULL != aux->Left) 
				{
					aux = aux->Left;
				}
					
			}
				
		}	
		else 
		{
			aux2 = aux2->Right;
			if (NULL == aux2) 
			{
				node->Parent = aux;
				aux->Right = node;
				while (node != Tree->Root) 
				{
					TreeBalanceHeight(node->Parent);
					node = node->Parent;
				}
				Tree->Root = TreeRotationCase(Tree->Root, Value);
				return 0;
			}
			else {
				aux = TreeRotationCase(aux, Value);
				if (NULL != aux->Right)
				{
					aux = aux->Right;
				}
					
			}
				
		}
			
	}
	
    return -1;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
	if (NULL == Tree)
	{
		return -1;
	}
	if (Tree->Root->Value == Value) 
	{
		TreeDeleteNode(Tree->Root, Value);
		Tree->Root = NULL;
		Tree->Count--;
		return 0;
	}
	if (NULL == TreeSearchNode(Tree->Root, Value))
	{
		return -1;
	}
	while (NULL != TreeSearchNode(Tree->Root, Value))
	{
		Tree->Count--;
		TreeDeleteNode(Tree->Root, Value);
	}

    return 0;
}

int TreeContains(CC_TREE *Tree, int Value)
{
	if (NULL == Tree)
	{
		return -1;
	}
	if (NULL == TreeSearchNode(Tree->Root, Value))
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}

int TreeGetCount(CC_TREE *Tree)
{
	if (NULL == Tree)
	{
		return -1;
	}
	return Tree->Count;
}

int TreeGetHeight(CC_TREE *Tree)
{
	if (NULL == Tree)
	{
		return -1;
	}
	return Tree->Height;
}

int TreeClear(CC_TREE *Tree)
{
	if (NULL == Tree)
	{
		return -1;
	}

	CC_TREE *tree = Tree;

	TreeDeleteAllNodes(tree->Root);
	return 0;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
	if (NULL == Tree || NULL == Value || Index < 0 || Index >= Tree->Count)
	{
		return -1;
	}
	TreePreorder(Tree->Root, &Index, Value);
	return 0;
	
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
	if (NULL == Tree || NULL == Value || Index < 0 || Index >= Tree->Count)
	{
		return -1;
	}
	TreeInorder(Tree->Root, &Index, Value);
	return 0;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
	if (NULL == Tree || NULL == Value || Index < 0 || Index >= Tree->Count)
	{
		return -1;
	}
	TreePostorder(Tree->Root, &Index, Value);
	return 0;
}

