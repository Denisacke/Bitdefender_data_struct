#include "ccvector.h"
#include "common.h"
#include "string.h"
#include <stdio.h>
#define INITIAL_SIZE    100

int VecRealloc(CC_VECTOR *Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}
	
	int size = Vector->Size * 2;
	
	//int *array = (int *)realloc(Vector->Array, sizeof(int) * size);
	int *array = (int *)malloc(sizeof(int) * size);
	for (int i = 0; i < Vector->Size; i++)
		*(array + i) = *(Vector->Array + i);
	if (NULL == array)
	{
		return -1;
	}
	free(Vector->Array);
	Vector->Array = array;
	Vector->Size = size;
	return 0;
}
int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }
	vec->Array = NULL;
    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
		//REALLOC
		VecRealloc(Vector);
    }
    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
		//REALLOC
		VecRealloc(Vector);
    }

    for (int i = Vector->Count - 1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
		//REALLOC
		VecRealloc(Vector);
    }

    for (int i = Vector->Count - 1; i >= Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index + 1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
	if (NULL == Vector)
	{
		return -1;
	}
	if (Index < 0 || Index > Vector->Count || !Vector->Count)
	{
		return -1;
	}

	for (int i = Index; i < Vector->Count - 1; i++)
	{
		Vector->Array[i] = Vector->Array[i + 1];
	}
	Vector->Count--;
    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{

	if (NULL == Vector)
	{
		return -1;
	}

	if (Index < 0 || Index > Vector->Count || !Vector->Count)
	{
		return -1;
	}

	*Value = Vector->Array[Index];
	return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
	CC_VECTOR *vec = Vector;

	if (NULL == Vector)
	{
		return -1;
	}
	vec->Array = NULL;
	free(vec->Array);

	Vector->Count = 0;

	return 0;
}

int VecSort(CC_VECTOR *Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}
	for(int i = 0; i < Vector->Count - 1; i++)
		for(int j = i + 1; j < Vector->Count; j++)
			if (Vector->Array[i] < Vector->Array[j]) 
			{
				int aux = Vector->Array[i];
				Vector->Array[i] = Vector->Array[j];
				Vector->Array[j] = aux;
			}
    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
	if (NULL == SrcVector)
	{
		return -1;
	}
	if (NULL == DestVector)
	{
		return -1;
	}
	if (DestVector->Count + SrcVector->Count > DestVector->Size)
	{
		//REALLOC
		VecRealloc(DestVector);
	}
	for (int i = 0; i < SrcVector->Count; i++)
		VecInsertTail(DestVector, SrcVector->Array[i]);
    return 0;
}
