#include <string.h>
#include <stdlib.h>
#include <avr/io.h>

/*my own defines and structures*/
#include "libhash.h"

hshObj newHashObject()
{

	hshObj returnHash = malloc(sizeof(struct hashObject));


	returnHash->hashData = (struct hashIndex **)malloc(HASHKEYSIZE * sizeof(struct hashIndex *));

	/*make all the pointers null pointers*/
	int i;
	for(i = 0; i < HASHKEYSIZE; i ++)
	{
		returnHash->hashData[i] = NULL;
	}

	/*make sure my methods belong to me.*/
	returnHash->hashKey = hashKey;
	returnHash->addIndex = addIndex;
	returnHash->addIndexString = addIndexString;
	returnHash->findIndex = findIndex;
	returnHash->findIndexString = findIndexString;
	returnHash->destruct = hashDestruct;

	return returnHash;
}

/*I hope this takes care of memory for the mean time*/
void hashDestruct(hshObj this)
{
	int i;
	for(i = 0; i < HASHKEYSIZE; i ++)
	{
		/*handle to work with*/
		struct hashIndex *indexHash = this->hashData[i];
		while(indexHash)
		{
			struct hashIndex *oldToFree = indexHash;
			indexHash = indexHash->next;

			/*free up the key strings*/
			free(oldToFree->key);
			/*free up each hash node instance*/
			free(oldToFree);
		}
	}
	/*free up the array reference in the object*/
	free(this->hashData);
	/*free up the object ittself*/
	free(this);
}

/*this takes a NULL terminated string*/
ptType findIndexString(hshObj this, char *key)
{
	return this->findIndex(this, key, strlen(key));
}

ptType findIndex(hshObj this, char *key, int keyLength)
{
	/*give us a handle to work with.*/
	struct hashIndex *indexHash = this->hashData[this->hashKey(key, keyLength, HASHKEYSIZE)];

	ptType retData = NULL;

	/*loop through the linked list the hash address points to*/
	while(indexHash)
	{
		if(memcmp(indexHash->key, key, keyLength) == 0)
		{
			retData = indexHash->data;
			break;
		}
		indexHash = indexHash->next;
	}
	return retData;
}

/*this takes a NULL terminated string*/
void addIndexString(hshObj this, char *key, ptType data)
{
	return this->addIndex(this, key, strlen(key), data);
}

void addIndex(hshObj this, char *key, int keyLength, ptType data)
{
	/*prcalculate the value we are looking for in the hash*/
	/*this makes sense from a performance point of view*/
	unsigned int hashKeyValue = this->hashKey(key, keyLength, HASHKEYSIZE);

	/*if this index has a null entry, make one*/
	if(!this->hashData[hashKeyValue])
	{
		/*Create an initial hash index entry*/
		struct hashIndex *temp = this->hashData[hashKeyValue] = (struct hashIndex *)malloc(sizeof(struct hashIndex));

		/*make the index aware of it's own key index*/
		temp->key = (char *)malloc(keyLength);
		memcpy(temp->key, key, keyLength);

		temp->data = data;
		temp->next = NULL;
	}
	/*if it has data associated with that key lets link another one to the old one.*/
	else
	{
		/*give us a temporary index key to work with*/
		struct hashIndex *temp = this->hashData[hashKeyValue];
		struct hashIndex *test = temp;


		int keyExists = 0;
		/*loop through the structure to see if we have have an existing key*/
		/*and replace the data with the new data*/
		while(test)
		{
			if(memcmp(test->key, key, keyLength) == 0)
			{
				test->data = data;
				keyExists = 1;
			}
			test = test->next;
		}
		if(!keyExists)
		{
			/*get to the end of the linked list for the particular index*/
			while(temp->next)
			{
				temp = temp->next;
			}
	
			/*create a new hash index on the same key, but link it to the */
			temp->next = (struct hashIndex *)malloc(sizeof(struct hashIndex));
	
			/*make the index aware of it's own key index*/
			temp->next->key = (char *)malloc(keyLength);
			memcpy(temp->next->key, key, keyLength);
	
			/*give it some data*/
			temp->next->data = data;

			temp->next->next = NULL;
		}
	}
}



/** 
* sdbm-algorithm for string-hashcode 
* @return hashcode for string, integer.
*/
unsigned int hashKey(char *key, int32_t keyLength, int32_t size) 
{
	return 0;
	uint32_t hash = 0;
	int32_t i;
	
	for(i = 0; i < keyLength; i ++)
	{
		hash = *(key + i) + (hash << 6) + (hash << 16) - hash;
	}
	return hash % size;
}
