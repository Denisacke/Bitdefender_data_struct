#include "ccheap.h"
#include "common.h"
#include "stdio.h"
#define INITIAL_SIZE    100
void HpHeapifyMin(int v[], int n, int i) {

	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && v[l] > v[smallest])
		smallest = l;


	if (r < n && v[r] > v[smallest])
		smallest = r;
	if (smallest != i) {

		int aux = v[i];
		v[i] = v[smallest];
		v[smallest] = aux;
		HpHeapifyMin(v, n, smallest);
	}
}

void HpHeapifyMax(int v[], int n, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && v[l] > v[largest])
		largest = l;


	if (r < n && v[r] > v[largest])
		largest = r;
	if (largest != i) {

		int aux = v[i];
		v[i] = v[largest];
		v[largest] = aux;
		HpHeapifyMax(v, n, largest);
	}
}

void HpBuildHeapBU(int v[], int n, CC_HEAP_TYPE type) {
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		if (type == MIN_HEAP)
		{
			HpHeapifyMin(v, n, i);
		}
		else
		{
			HpHeapifyMax(v, n, i);
		}
	}
		
}

void HpHeapSortBU(int v[], int n, CC_HEAP_TYPE type) {

	HpBuildHeapBU(v, n, type);


	for (int i = n - 1; i >= 0; i--) {
		int aux = v[0];
		v[0] = v[i];
		v[i] = aux;
		

		if (type == MIN_HEAP)
			HpHeapifyMin(v, i, 0);
		else
			HpHeapifyMax(v, i, 0);
	}
}

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MaxHeap)
	{
		return -1;
	}
	CC_HEAP* heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
	if (VecCreate(&heap->HeapVec) != 0)
	{
		return -1;
	}
	heap->Type = MAX_HEAP;
	heap->HeapVec = InitialElements;
	heap->HeapVec->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
	if (NULL != heap->HeapVec)
	{
		HpHeapSortBU(heap->HeapVec->Array, heap->HeapVec->Size, heap->Type);
		heap->HeapVec->Size = INITIAL_SIZE;
		heap->HeapVec->Count = InitialElements->Count;
	}
	else
	{
		heap->HeapVec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
		heap->HeapVec->Count = 0;
		heap->HeapVec->Size = INITIAL_SIZE;
	}
	*MaxHeap = heap;
    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MinHeap)
	{
		return -1;
	}
	CC_HEAP* heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
	if (VecCreate(&heap->HeapVec) != 0)
	{
		return -1;
	}
	heap->Type = MIN_HEAP;
	heap->HeapVec = InitialElements;
	
	if (NULL != heap->HeapVec)
	{
		HpHeapSortBU(heap->HeapVec->Array, heap->HeapVec->Size, heap->Type);
		heap->HeapVec->Size = INITIAL_SIZE;
		heap->HeapVec->Count = InitialElements->Count;
	}
	else
	{
		heap->HeapVec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
		heap->HeapVec->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
		heap->HeapVec->Count = 0;
		heap->HeapVec->Size = INITIAL_SIZE;
	}
	*MinHeap = heap;
	return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
	if (NULL == Heap)
	{
		return -1;
	}

	if (NULL != (*Heap)->HeapVec)
	{
		CC_VECTOR* aux = (*Heap)->HeapVec;
		if (VecDestroy(&aux) != 0)
		{
			return -1;
		}
	}

	free(*Heap);
	*Heap = NULL;
	return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}

	if (VecInsertTail(Heap->HeapVec, Value) != 0)
	{
		return -1;
	}
	HpHeapSortBU(Heap->HeapVec->Array, Heap->HeapVec->Count, Heap->Type);

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}
	for (int i = 0; i < Heap->HeapVec->Count; i++)
	{
		if (Heap->HeapVec->Array[i] == Value)
		{
			VecRemoveByIndex(Heap->HeapVec, i);
		}
	}
	HpHeapSortBU(Heap->HeapVec->Array, Heap->HeapVec->Count, Heap->Type);
    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}
	*ExtremeValue = Heap->HeapVec->Array[0];

    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}
	*ExtremeValue = Heap->HeapVec->Array[0];
	for (int i = 0; i < Heap->HeapVec->Count; i++)
	{
		if (Heap->HeapVec->Array[i] == *ExtremeValue)
		{
			VecRemoveByIndex(Heap->HeapVec, i);
		}
	}
	HpHeapSortBU(Heap->HeapVec->Array, Heap->HeapVec->Count, Heap->Type);
	return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}
    return VecGetCount(Heap->HeapVec);
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == Heap->HeapVec)
	{
		return -1;
	}
	for (int i = 0; i < Heap->HeapVec->Count; i++)
	{
		if (VecInsertTail(SortedVector, Heap->HeapVec->Array[i]) != 0)
		{
			return -1;
		}
	}
	for(int i = 0; i < VecGetCount(SortedVector) - 1; i++)
		for (int j = i + 1; j < VecGetCount(SortedVector); j++) 
		{
			if (SortedVector->Array[i] > SortedVector->Array[j])
			{
				int aux = SortedVector->Array[i];
				SortedVector->Array[i] = SortedVector->Array[j];
				SortedVector->Array[j] = aux;
			}
		}
    return 0;
}
