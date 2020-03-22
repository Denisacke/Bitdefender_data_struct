#include "ccstack.h"
#include "common.h"
#define INITIAL_SIZE  100

int StRealloc(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}

	int size = Stack->Size * 2;

	//int *array = (int *)realloc(Vector->Array, sizeof(int) * size);
	int *array = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < Stack->Size; i++)
		*(array + i) = *(Stack->Items + i);
	if (NULL == array)
	{
		return -1;
	}
	free(Stack->Items);
	Stack->Items = array;
	Stack->Size = size;
	return 0;
}
int StCreate(CC_STACK **Stack)
{
	CC_STACK *st = NULL;
	if (NULL == Stack)
	{
		return -1;
	}
	st = (CC_STACK*)malloc(sizeof(CC_STACK));
	if (NULL == st)
	{
		return -1;
	}
	st->Count = 0;
	st->Size = INITIAL_SIZE;
	st->Items = (int*)malloc(sizeof(int) * INITIAL_SIZE);
	if (NULL == st->Items)
	{
		//free(st);
		return -1;
	}

	*Stack = st;

	return 0;
 
}

int StDestroy(CC_STACK **Stack)
{
	CC_STACK *st = *Stack;

	if (NULL == Stack)
	{
		return -1;
	}
	st->Count = 0;
	free(st->Items);
	free(st);
	*Stack = NULL;

	return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
	if (NULL == Stack)
	{
		return -1;
	}

	if (Stack->Count >= Stack->Size)
	{ 
		StRealloc(Stack);
	}

	Stack->Items[Stack->Count] = Value;
	Stack->Count++;

	return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		return -1;
	}

	if (!Stack->Count)
	{
		return -1;
	}
	*Value = Stack->Items[Stack->Count - 1];
	Stack->Count--;

	return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		*Value = -1;
		return -1;
	}
	if (!Stack->Count)
	{
		*Value = -1;
		return -1;
	}
	*Value = Stack->Items[Stack->Count - 1];
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
	if (!Stack->Count)
	{
		return 1;
	}
	else
		if(Stack->Count)
		{
			return 0;
		}
		
    return -1;
}

int StGetCount(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
    return Stack->Count;
}

int StClear(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
	Stack->Items = NULL;
	free(Stack->Items);
	Stack->Count = 0;
    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
	if (NULL == Stack || NULL == StackToPush)
	{
		return -1;
	}
	for (int i = 0; i < StackToPush->Count; i++)
	{
		StPush(Stack, StackToPush->Items[i]);
	}
	StClear(StackToPush);
	return 0;
}
