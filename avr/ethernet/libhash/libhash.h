#ifndef HASHH
#define HASHH true
#ifdef __cplusplus
extern "C" {
#endif


#define HASHKEYSIZE 10 

/**
 * A struct that holds the data inside the hash
 *
 * This struct is a linked list that holds the
 * data for each collision on the hash
 */
struct hashIndex
{
	struct hashIndex *next;

	void *data;
	char *key;
};
/*just create a nice little data type that we can access */
/*easily.*/
typedef struct hashIndex **hIndex;


/*FAKE CLASSES*/

	/*CLASS hashObject*/
	/*{*/
		/*STRUCTURE*/
		/**
		 * This is a hash storage class
		 *
		 * This allows one to make an index of data by storing
		 * random data against a key. Very simple to use:<br/>
		 * 	<b>hshObj myHash = newHashObject();</b>
		 *
		 * @author Daine Mamacos <daine.mamacos@complinet.com>
		 */
		struct hashObject
		{
			struct hashIndex **hashData;

			unsigned int (*hashKey)(char *, int32_t, int32_t);	
			void (*addIndex)(struct hashObject *, char *, int, void *);
			void (*addIndexString)(struct hashObject *, char *, void *);
			void *(*findIndex)(struct hashObject *, char *, int);
			void *(*findIndexString)(struct hashObject *, char *);
			void (*destruct)(struct hashObject *);
		};
		/*use a nice little handle*/
		typedef struct hashObject *hshObj;
	
		/*CONSTRUCTOR*/
		hshObj newHashObject();

		/*METHODS*/
		unsigned int hashKey(char *, int32_t, int32_t);
		/**
		 * This method adds an index to the hash. You pass a pointer to the data
		 * you want to store in the hash.<br/>
		 * eg:<br/>
		 * 	<b>myHash->addIndex(myHash, (char *)&myKeyAsInt, sizeof(int), myData);</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* &myKeyAsInt - This is the key, as an integer, it can really be anything you want, just cast it correctly
		 * @param int sizeof(int) - This is the size of the key, here it's an integer, hence sizeof(int).
		 * @param void* myData - This is the data you want to point to, it can be anything
		 */
		void addIndex(hshObj, char *, int, void *);
		/**
		 * This method also adds an index to the hash, but it takes a string as the key.
		 * You pass a pointer to the data you want to store.<br/>
		 * eg:<br/>
		 * 	<b>myHash->addIndexString(myHash, "myDataInTheHash", myData);</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* "myDataInTheHash" - The key as a string. it MUST be null terminated otherwise it will break things in a nasty way
		 * @param void* myData - This is the data you want to point to, it can be anything
		 */
		void addIndexString(hshObj, char *, void *);
		/**
		 * This method finds an index against the hash and returns a pointer to the data<br/>
		 * eg:<br/>
		 * 	<b>myData = myHash->findIndex(myHash, (char *)&myKeyAsInt, sizeof(int));</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* &myKeyAsInt - This is the key, as an integer, it can really be anything you want, just cast it correctly
		 * @param int sizeof(int) - This is the size of the key, here it's an integer, hence sizeof(int).
		 */
		void *findIndex(hshObj, char *, int);
		/**
		 * This method finds an index against the hash and returns a pointer to the data,
		 * but takes a string as the key.<br/>
		 * eg:<br/>
		 * 	<b>myData = myHash->findIndex(myHash, "myDataInTheHash");</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* "myDataInTheHash" - The key as a string. it MUST be null terminated otherwise it will break things in a nasty way
		 */
		void *findIndexString(hshObj, char *);
		/**
		 * NOTE: NOT IMPLIMENTED YET!
		 * This method deletes a hash entry from the index and frees up it's memory inheranty.<br/>
		 * eg:<br/>
		 * 	<b>myHash->deleteIndex(myHash, (char *)&myKeyAsInt, sizeof(int));</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* &myKeyAsInt - This is the key, as an integer, it can really be anything you want, just cast it correctly
		 * @param int sizeof(int) - This is the size of the key, here it's an integer, hence sizeof(int).
		 */
		void deleteIndex(hshObj, char *, int);
		/**
		 * NOTE: NOT IMPLIMENTED YET!
		 * This method deletes a hash entry from the index and frees up it's memory inheranty,
		 * but takes a string as they key.<br/>
		 * eg:<br/>
		 * 	<b>myHash->deleteIndexString(myHash, "myDataInTheHash");</b>
		 *
		 * @param hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 * @param char* "myDataInTheHash" - The key as a string. it MUST be null terminated otherwise it will break things in a nasty way
		 */
		void deleteIndexString(hshObj, char *);
		/**
		 * This is just the class destructor, this *MUST* be called manually if you want 
		 * no memory leaks. It is your responsibility to free the data pointed to by the
		 * hash, as it does not copy the data in any way. The keys are copied and managed
		 * however, so no need to worry about those.<br/>
		 * eg:<br/>
		 * 	<b>myHash->destruct(myHash);</b>
		 *
		 * @param  hshObj myHash - This is a required features since this is NOT C++, but fake objects made user friendly
		 */
		void hashDestruct(hshObj);
	/*}*/

#ifdef __cplusplus
}
#endif
#endif
