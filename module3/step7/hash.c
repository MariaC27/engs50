/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "hash.h"

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */

#define MAXTABLESIZE 20
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;

  if (len <= 0 || data == NULL)
    return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

struct hashtable_t{
	queue_t *table[MAXTABLESIZE];
	uint32_t size;
};

//open a new table with size hsize
hashtable_t *hopen(uint32_t hsize){
	if(hsize > MAXTABLESIZE){
		printf("Table size too large. Max size is %i\n\n", MAXTABLESIZE);
		return NULL;
	}

	struct hashtable_t *hasher = (struct hashtable_t*)malloc(sizeof(struct hashtable_t));
	hasher->size = hsize;
	for(int i = 0; i < hsize; i++){
		hasher->table[i] = qopen();
	}
	return hasher;
}

//close all of the chains in the hash table that is pointed to by htb
void hclose(hashtable_t *htp){
	struct hashtable_t* h = htp;
	for(int i = 0; i < h->size; i++){
		qclose(h->table[i]);
	}

	free(h);
}


//put node ep into hashtable pointed to by htp with key key and key length keylen
int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){
	struct hashtable_t* h = htp;
	uint32_t table_position = SuperFastHash(key, keylen, h->size);
	qput(h->table[table_position], (struct Node *)ep);
	return 0;
}



/* happly -- applies a function to every entry in hash table */
void happly(hashtable_t *htp, void (*fn)(void* ep)){
	struct hashtable_t* h = htp;

	for(int i = 0; i < MAXTABLESIZE; i++){
		qapply(h->table[i], fn);
	}
}

/* hsearch -- searchs for an entry under a designated key using a
 * designated search fn -- returns a pointer to the entry or NULL if
 * not found
 */
void *hsearch(hashtable_t *htp,
        bool (*searchfn)(void* elementp, const void* searchkeyp),
        const char *key,
							int32_t keylen){
	struct hashtable_t* h = htp;

	uint32_t table_position = SuperFastHash(key, keylen, h->size);
	void *n = qsearch(h->table[table_position], searchfn, key);
	return n;
}

void *hremove(hashtable_t *htp,
        bool (*searchfn)(void* elementp, const void* searchkeyp),
        const char *key,
							int32_t keylen){
	struct hashtable_t* h = htp;

	uint32_t table_position = SuperFastHash(key, keylen, h->size);
  void *n = qremove(h->table[table_position], searchfn, key);
  return n;
}
