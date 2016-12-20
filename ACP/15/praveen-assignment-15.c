/******************************************************************************/
/*****************************  prologue  *************************************/
/*                                                                            */
/*    University of California Extension, Santa Cruz                          */
/*                                                                            */
/*    Advanced C Programming                                                  */
/*                                                                            */
/*    Instructor: Rajainder A. Yeldandi                                       */
/*                                                                            */
/*    Author: Praveen Mhapsekar                                               */
/*                                                                            */
/*    Assignment Number: 15                                                   */
/*                                                                            */
/*    Topic: Hashing                                                          */
/*                                                                            */
/*    File name:  praveen-assignment-15.c                                     */
/*                                                                            */
/*    Date: 12/19/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*	   Implement a hash table of size 15. Use the Separate Chaining for       */
/*	   collisions. Give your input file of 100 records with keys.             */
/*     Use the structure of {key,	record, next} for the linked nodes.       */
/*	   Hint: You can use the routines 	discussed in the class and expand     */
/*	         them to work for you.                                            */
/******************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#define MAX_INPUT_KEY 100
#define MAX_KEY_SIZE 16
#define MAX_REC_SIZE 16
#define HASH_TABLE_SIZE 15

typedef struct kvTuple {
  char key[MAX_KEY_SIZE];
  char rec[MAX_REC_SIZE];
} kvTuple_t;

typedef struct hashEntry {
	char   *key;
	char   *rec;
	struct hashEntry *nxt;
} hashEntry_t;

typedef struct hashTable {
	int size;
    hashEntry_t **hashTable;	
} hashTable_t;

/*
 * Create hashTable
 */
hashTable_t *
hashTableCreate(int size)
{
	hashTable_t *ht = NULL;
	int i;

	if (size < 1) return NULL;

	ht = malloc(sizeof(hashTable_t));
	if (ht == NULL) return NULL;

	ht->hashTable = malloc(sizeof(hashEntry_t *) * size);
    if (ht->hashTable == NULL) return NULL;	 

	/* Initialize hashTable default entries */
	for (i = 0; i < size; i++) {
		ht->hashTable[i] = NULL;
	}

	ht->size = size;

	return ht;	
}

/*
 * Generate hashKey from given key
 */
int 
hashTableHashKey(hashTable_t *ht, char *key) 
{
	unsigned int hashVal = 0;
	int i = strlen(key);

	while (hashVal < UINT_MAX && i) {
		hashVal = hashVal << 8;
		hashVal += key[i--];
	}

	return hashVal % ht->size;
}

/*
 * Create <key rec> pair
 */
hashEntry_t *
hashTablePair(char *key, char *rec)
{
	hashEntry_t *kvPair;

	if ((kvPair = malloc(sizeof(hashEntry_t))) == NULL)  return NULL;
	if ((kvPair->key = strdup(key)) == NULL) return NULL;
	if ((kvPair->rec = strdup(rec)) == NULL) return NULL;

	kvPair->nxt = NULL;

	return kvPair;
}

/*
 * Insert <key, rec> pair in hashTable
 */
void 
hashTableInsert(hashTable_t *hashtable, char *key, char *rec)
{
	int hashKey = 0;
	hashEntry_t *kvPair = NULL;
	hashEntry_t *next = NULL;
	hashEntry_t *last = NULL;

	hashKey = hashTableHashKey(hashtable, key);
	next = hashtable->hashTable[hashKey];
	printf("Inserting [ key = \"%s\", rec = \"%s\" ] hashKey = %d\n", key, rec, hashKey);

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->nxt;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		free(next->rec);
		next->rec = strdup(rec);
	} else {
		kvPair = hashTablePair(key, rec);
		if (next == hashtable->hashTable[hashKey]) {
			kvPair->nxt = next;
			hashtable->hashTable[hashKey] = kvPair;
		} else if (next == NULL) {
			last->nxt = kvPair;
		} else  {
			kvPair->nxt = next;
			last->nxt = kvPair;
		}
	}
}

/*
 *  Lookup & fetch key from hashTable
 */
char *
hashTableGet(hashTable_t *hashtable, char *key) 
{
	int hashKey = 0;
	hashEntry_t *pair;

	printf("Lookingup [ key = \"%s\" ]", key);
	hashKey = hashTableHashKey(hashtable, key);
	pair = hashtable->hashTable[hashKey];

	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
		pair = pair->nxt;
	}

	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
		printf(" Lookup failure\n");
		return NULL;
	} else {
		printf(" Lookup success [Val = \"%s\" ]\n", pair->rec);
		return pair->rec;
	}
}

/*
 *  Read input from the user
 */
void
readInput(int i, kvTuple_t *kvt)
{
	 printf("\n----------- %d ----------------\n", i);
     printf("key:");
     fgets(kvt->key, MAX_KEY_SIZE, stdin); 
	 kvt->key[strcspn(kvt->key, "\n")] = 0;
     printf ("Rec:");
     fgets(kvt->rec, MAX_REC_SIZE, stdin); 
	 kvt->rec[strcspn(kvt->rec, "\n")] = 0;
	 printf("\n");
}

int
main(void) 
{
    int i;
    int k = 0; 
	hashTable_t *hashtable = hashTableCreate(HASH_TABLE_SIZE);
    kvTuple_t kvTuple;
    kvTuple_t sampleKey[HASH_TABLE_SIZE/10];  /* Save some key for retrival later */

	for (i = 0; i < MAX_INPUT_KEY; i++) {
		/* Read input */
		readInput(i, &kvTuple);
		/* Insert record in hashTable */
		hashTableInsert(hashtable, kvTuple.key, kvTuple.rec);
		/* Compute & Print LoadFactor */
		printf("%d Records inserted, current Loadfactor = %d\n", i, i/HASH_TABLE_SIZE);

		/* Store sample keys for retrival later */
		if ((i % 10) == 0) {
			strcpy(sampleKey[k++].key, kvTuple.key);
		}
	}

	k--;
	/* Retrive and print saved keys */
	printf("\n\nRetriviving keys from hash table \n");
	printf("----------------------------------\n");
    while (k) {
		hashTableGet(hashtable, sampleKey[k--].key);
	}

	return 0;
}
