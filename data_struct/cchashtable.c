#include "cchashtable.h"
#include "common.h"
#include <stdio.h> 
#include <string.h> 

#define INITIAL_SIZE 119
int HtClearData(CC_HASH_TABLE_DATA ** Data, int Size, int Count)
{
	if (NULL == Data || Size < 0 || Count < 0 || Count > Size)
	{
		return -1;
	}

	CC_HASH_TABLE_DATA *data = *Data;

	int count = 0;
	for (int i = 0; count < Count; i++)
	{
		if (NULL != (data[i].Key))
		{
			data[i].Key = NULL;
			data[i].Value = -1;
			free(data[i].Key);
			
			count++;
		}
	}

	free(*Data);
	*Data = NULL;

	return 0;
}

int HtHashFunction(char *key, int size) {
	int hash = 0;
	for (int i = 0; key[i] != 0; i += 2) {
		hash += 7 * key[i];
	}

	return (hash + key[1] % 7) % size;
}

int HtHashFunction2(char *key, int size, int k) 
{
	int hash = k * 7;
	for (int i = 0; key[i] != 0; i++) {
		hash += 13 * key[i] + 19 * key[i] * key[i];
	}

	return (hash + key[1] % 7 + (key[3] >> 3)) % size;
}
int HtCreate(CC_HASH_TABLE **HashTable)
{
	CC_HASH_TABLE *hash = NULL;
	if (NULL == HashTable) 
	{
		return -1;
	}
	hash = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));
	if (NULL == hash) 
	{
		return -1;
	}
	hash->Size = INITIAL_SIZE;
	hash->Count = 0;
	hash->Data = (CC_HASH_TABLE_DATA*)malloc(INITIAL_SIZE * sizeof(CC_HASH_TABLE_DATA));
	for (int i = 0; i < INITIAL_SIZE; i++) 
	{
		hash->Data[i].Value = -1;
		//hash->Data[i].Key = (char*)malloc(10 * sizeof(char));
	}
	*HashTable = hash;
    return 0;
}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
	if (NULL == HashTable)
	{
		return -1;
	}

	if (HtClear(*HashTable) != 0)
	{
		return -1;
	}

	free(*HashTable);

	*HashTable = NULL;
	return 0;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
	if (NULL == HashTable || NULL == Key)
	{
		return -1;
	}

	if (HashTable->Size == 0)
	{
			return -1;
	}
	int value = HtHashFunction(Key, HashTable->Size);
	if (HashTable->Data[value].Value != -1)
	{
		int k = 0;
		//printf("Collision %s \n", Key);
		while (HashTable->Data[value].Value != -1)
		{
			value = HtHashFunction2(Key, HashTable->Size, k);
			k++;
		}
		//rehash
		HashTable->Data[value].Value = Value;
		HashTable->Data[value].Key = Key;
		return 0;
	}
	else {
		HashTable->Data[value].Value = Value;
		HashTable->Data[value].Key = Key;
	}
	HashTable->Count++;
    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
	if (NULL == HashTable || NULL == Key || HashTable->Size == 0)
	{
		return -1;
	}
	int val = HtHashFunction(Key, HashTable->Size);
	if (HashTable->Data[val].Value == -1)
	{
		return -1;
	}
    *Value = HashTable->Data[val].Value;
	return 0;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
	if (NULL == HashTable || NULL == Key || HashTable->Size == 0)
	{
		return -1;
	}
	int val = HtHashFunction(Key, HashTable->Size);
	if (HashTable->Data[val].Value == -1)
	{
		return -1;
	}
	HashTable->Data[val].Value = -1;
    return 0;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
	if (NULL == HashTable || NULL == Key || HashTable->Size == 0)
	{
		return -1;
	}
	int val = HtHashFunction(Key, HashTable->Size);
	if (HashTable->Data[val].Value == -1)
	{
		return 0;
	}
    return 1;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{

	if (NULL == HashTable)
	{
		return -1;
	}
	if (NULL == Iterator)
	{
		return -1;
	}
	if (NULL == Key)
	{
		return -1;
	}

	CC_HASH_TABLE_ITERATOR *iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
	if (NULL == iterator)
	{
		return -1;
	}

	memset(iterator, 0, sizeof(*iterator));

	iterator->HashTable = HashTable;
	iterator->CurrentIndex = -1;


	if (HashTable->Count == 0)
	{
		return -2;
	}
	// FIND THE FIRST KEY AND SET Key
	int i;
	for (i = 0; ; i++)
	{
		if (HashTable->Data[i].Value != -1)
		{
			break;
		}
	}
	iterator->CurrentIndex = i;
	//strcpy_s(*Key, sizeof(iterator->HashTable->Data[iterator->currentIndex].Key), iterator->HashTable->Data[iterator->currentIndex].Key);
	*Key = iterator->HashTable->Data[iterator->CurrentIndex].Key;
	*Iterator = iterator;
	return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
	if (NULL == Iterator)
	{
		return -1;
	}
	if (NULL == Iterator->HashTable)
	{
		return -1;
	}
	int i;
	for (i = Iterator->CurrentIndex + 1; ; i++)
	{
		if (Iterator->HashTable->Data[i].Value != -1)
		{
			break;
		}
	}
	Iterator->CurrentIndex = i;
	*Key = Iterator->HashTable->Data[Iterator->CurrentIndex].Key;
	return 0;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
	if (NULL == *Iterator)
	{
		return -1;
	}
	*Iterator = NULL;
	free(*Iterator);
	return 0;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
	if (NULL == HashTable)
	{
		return -1;
	}

	if (NULL != HashTable->Data)
	{
		if (0 != HtClearData(&HashTable->Data, HashTable->Size, HashTable->Count))
		{
			return -1;
		}
	}

	//HashTable->Size = 0;
	HashTable->Count = 0;
	return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
	if (NULL == HashTable)
	{
		return -1;
	}

	return HashTable->Count;
}
