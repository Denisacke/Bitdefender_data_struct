#include <stdio.h>
#include <stdlib.h>
#include "ccvector.h"
#include "ccstack.h"
#include "cchashtable.h"
#include "ccheap.h"
#include "cctree.h"

int TestVector();
int TestStack();
int TestHashTable();
int TestHeap();
int TestTree();

void RunTests();

int main(void)
{
    RunTests();
    return 0;
}

void RunTests()
{
    /// NOTE: The tests provided here are by no means exhaustive and are only
    /// provided as a starting point (not all functions are tested, not all use cases
    /// and failure scenarios are covered). You are encouraged to expand these tests
    /// to include missing scenarios.
    if (0 == TestVector())
    {
        printf("Vector test passed\n\n");
    }
    else
    {
        printf("Vector test failed\n\n");
    }

    if (0 == TestStack())
    {
        printf("Stack test passed\n\n");
    }
    else
    {
        printf("Stack test failed\n\n");
    }

    if (0 == TestHashTable())
    {
        printf("HashTable test passed\n\n");
    }
    else
    {
        printf("HashTable test failed\n\n");
    }

    if (0 == TestHeap())
    {
        printf("Heap test passed\n\n");
    }
    else
    {
        printf("Heap test failed\n\n");
    }

    if (0 == TestTree())
    {
        printf("Tree test passed\n\n");
    }
    else
    {
        printf("Tree test failed\n\n");
    }
}


int TestTree()
{
    int retVal = -1;
    CC_TREE* usedTree = NULL;

    retVal = TreeCreate(&usedTree);
    if (0 != retVal)
    {
        printf("TreeCreate failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }
	retVal = TreeInsert(usedTree, 30);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 45);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 50);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 60);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 10);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 5);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 2);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	
	retVal = TreeInsert(usedTree, 55);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	retVal = TreeInsert(usedTree, 67);
	if (0 != retVal)
	{
		printf("TreeInsert failed!\n");
		goto cleanup;
	}
	printf("%d\n", usedTree->Root->Right->Left->Right->Value);
	if (1 != TreeContains(usedTree, 55))
	{
		printf("TreeContains invalid return value after remove!\n");
		retVal = -1;
		goto cleanup;
	}
	int value = 0;
	if (TreeGetNthPreorder(usedTree, 5, &value) != 0) {
		printf("Couldn't get preorder :(\n");
		goto cleanup;
	}
	printf("value:%d\n", value);
	if (TreeRemove(usedTree, 67) != 0) {
		printf("Node removal failed :(\n");
		goto cleanup;
	}
	if (TreeRemove(usedTree, 60) != 0) {
		printf("Node removal failed :(\n");
		goto cleanup;
	}
	if (TreeRemove(usedTree, 10) != 0) {
		printf("Node removal failed :(\n");
		goto cleanup;
	}
	printf("%d\n", usedTree->Root->Left->Left->Left->Value);

cleanup:
    if (NULL != usedTree)
    {
        if (0 != TreeDestroy(&usedTree))
        {
            printf("TreeDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}
              
int TestHeap()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HEAP* usedHeap = NULL;

    retVal = HpCreateMinHeap(&usedHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMinHeap failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 20);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    if (2 != HpGetElementCount(usedHeap))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpGetExtreme(usedHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!\n");
        goto cleanup;
    }

    if (10 != foundVal)
    {
        printf("Invalid minimum value returned!");
        retVal = -1;
        goto cleanup;
    }
	retVal = HpInsert(usedHeap, 5);
	if (0 != retVal)
	{
		printf("HpInsert failed!\n");
		goto cleanup;
	}
	retVal = HpGetExtreme(usedHeap, &foundVal);
	if (0 != retVal)
	{
		printf("HpGetExtreme failed!\n");
		goto cleanup;
	}

	if (5 != foundVal)
	{
		printf("Invalid minimum value returned!");
		retVal = -1;
		goto cleanup;
	}
	if (HpRemove(usedHeap, 10) != 0) {
		printf("Remove failed\n");
		goto cleanup;
	}
	if (HpRemove(usedHeap, 5) != 0) {
		printf("Remove failed\n");
		goto cleanup;
	}
	retVal = HpGetExtreme(usedHeap, &foundVal);
	if (0 != retVal)
	{
		printf("HpGetExtreme failed!\n");
		goto cleanup;
	}

	if (20 != foundVal)
	{
		printf("Invalid minimum value returned!");
		retVal = -1;
		goto cleanup;
	}
	retVal = HpInsert(usedHeap, 5);
	if (0 != retVal)
	{
		printf("HpInsert failed!\n");
		goto cleanup;
	}
	retVal = HpInsert(usedHeap, 10);
	if (0 != retVal)
	{
		printf("HpInsert failed!\n");
		goto cleanup;
	}
	CC_VECTOR *aux;
	VecCreate(&aux);
	if (HpSortToVector(usedHeap, aux) != 0) {
		printf("HpSort failed :( \n");
		goto cleanup;
	}
	printf("Sorted Array values\n");
	for (int i = 0; i < aux->Count; i++)
		printf("%d ", aux->Array[i]);
	printf("\n");
	VecDestroy(&aux);

cleanup:
    if (NULL != usedHeap)
    {
        if (0 != HpDestroy(&usedHeap))
        {
            printf("HpDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHashTable()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HASH_TABLE* usedTable = NULL;
	CC_HASH_TABLE_ITERATOR* usedIterator;
	usedIterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
	char *key = (char*)malloc(20 * sizeof(char));
	
    retVal = HtCreate(&usedTable);
    if (0 != retVal)
    {
        printf("HtCreate failed!\n");
        goto cleanup;
    }

    retVal = HtSetKeyValue(usedTable, "mere", 20);
    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!\n");
        goto cleanup;
    }

    if (1 != HtHasKey(usedTable, "mere"))
    {
        printf("Invalid answer to HtHasKey!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (0 != retVal)
    {
        printf("HtGetKeyValue failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after get!\n");
        retVal = -1;
        goto cleanup;
    }
	retVal = HtSetKeyValue(usedTable, "ananas", 35);
	if (0 != retVal)
	{
		printf("HtSetKeyValue failed!\n");
		goto cleanup;
	}
	retVal = HtSetKeyValue(usedTable, "pere", 2);
	if (0 != retVal)
	{
		printf("HtSetKeyValue failed!\n");
		goto cleanup;
	}
	retVal = HtSetKeyValue(usedTable, "apanas", 17);
	if (0 != retVal)
	{
		printf("HtSetKeyValue failed!\n");
		goto cleanup;
	}
	retVal = HtGetFirstKey(usedTable, &usedIterator, &key);
	if (0 != retVal)
	{
		printf("Iterator doesn't work\n %d\n", retVal);
		retVal = -1;
		goto cleanup;
	}
	printf("%s\n", key);
	
	retVal = HtGetNextKey(usedIterator, &key);
	if (0 != retVal)
	{
		printf("HtGetNextKey failed!\n");
		goto cleanup;
	}
	printf("%s\n", key);
	key = NULL;
	free(key);
	if (HtReleaseIterator(&usedIterator) != 0) {
		printf("Couldn't release Iterator :(");
		goto cleanup;
	}
	if (HtClear(usedTable) != 0) {
		printf("Couldn't clear HashTable :(\n");
		goto cleanup;
	}
cleanup:
    if (NULL != usedTable)
    {
        if (0 != HtDestroy(&usedTable))
        {
            printf("HtDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestStack()
{
    int retVal = -1;
    int foundVal = -1;
    CC_STACK* usedStack = NULL;

    retVal = StCreate(&usedStack);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPop(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPop failed!\n");
        goto cleanup;
    }

    if (foundVal != 10)
    {
        printf("Invalid value after pop!\n");
        retVal = -1;
        goto cleanup;
    }
	retVal = StPush(usedStack, 70);
	if (0 != retVal)
	{
		printf("StPush failed!\n");
		goto cleanup;
	}
	retVal = StPush(usedStack, 40);
	if (0 != retVal)
	{
		printf("StPush failed!\n");
		goto cleanup;
	}
	retVal = StPop(usedStack, &foundVal);
	if (0 != retVal)
	{
		printf("StPop failed!\n");
		goto cleanup;
	}

	if (foundVal != 40)
	{
		printf("Invalid value after pop!\n");
		retVal = -1;
		goto cleanup;
	}
	retVal = StPop(usedStack, &foundVal);
	if (0 != retVal)
	{
		printf("StPop failed!\n");
		goto cleanup;
	}

	if (foundVal != 70)
	{
		printf("Invalid value after pop!\n");
		retVal = -1;
		goto cleanup;
	}
	if (StGetCount(usedStack) != 0) {
		printf("Count doesn't work :(\n");
		goto cleanup;
	}
	CC_STACK *auxStack;
	StCreate(&auxStack);
	StPush(auxStack, 55);
	StPush(auxStack, 12);
	StPush(auxStack, 7);
	StPush(auxStack, 31);
	printf("Stack size: %d \n", auxStack->Size);
	for (int i = 0; i < 100; i++)
		StPush(auxStack, i);
	printf("Stack size: %d \n", auxStack->Size);
	StDestroy(&auxStack);
cleanup:
    if (NULL != usedStack)
    {
        if (0 != StDestroy(&usedStack))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestVector()
{
    int retVal = -1;
    int foundVal = 0;
    CC_VECTOR* usedVector = NULL;
    
    retVal = VecCreate(&usedVector);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector, 10);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    if (VecGetCount(usedVector) != 2)
    {
        printf("Invalid count returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector, 0, 20);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }

    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector, 0, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value found at position 0\n");
        retVal = -1;
        goto cleanup;
    }
	for (int i = 0; i < 112; i++) {
		VecInsertTail(usedVector, i);
	}
	VecSort(usedVector);

	if (200 != usedVector->Size) {
		printf("VecRealloc failed\n");
		goto cleanup;
	}

    /*retVal = VecClear(usedVector);
    if (0 != retVal)
    {
        printf("VecClear failed!\n");
        goto cleanup;
    }

    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear\n");
        retVal = -1;
        goto cleanup;
    }*/
	CC_VECTOR* auxVector = NULL;
	VecCreate(&auxVector);
	retVal = VecCreate(&auxVector);
	if (0 != retVal)
	{
		printf("VecCreate failed!\n");
		goto cleanup;
	}

	if (114 != VecGetCount(usedVector))
	{
		printf("Invalid count after clear..count is %d\n", VecGetCount(usedVector));
		retVal = -1;
		goto cleanup;
	}

	retVal = VecInsertTail(auxVector, 7);
	if (0 != retVal)
	{
		printf("VecInsertTail failed!\n");
		goto cleanup;
	}
	if (114 != VecGetCount(usedVector))
	{
		printf("Invalid count after clear..count is %d\n", VecGetCount(usedVector));
		retVal = -1;
		goto cleanup;
	}
	VecAppend(usedVector, auxVector);
	if (115 != VecGetCount(usedVector))
	{
		printf("Invalid count after clear..count is %d\n", VecGetCount(usedVector));
		retVal = -1;
		goto cleanup;
	}
	VecRemoveByIndex(usedVector, 0);
	VecDestroy(&auxVector);
cleanup:
    if (NULL != usedVector)
    {
        if (0 != VecDestroy(&usedVector))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}