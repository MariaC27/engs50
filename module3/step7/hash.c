/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <hash.h>
#include <stdio.h>

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */

#define MAXTABLESIZE 20
typedef struct hashtable {
	queue_t *table[MAXTABLESIZE];
	int size;
}hashtable_t;

//open a new table with size hsize
hashtable_t *hopen(uint32_t hsize){
	if(hsize > MAXTABLESIZE){
		printf("Table size too large. Max size is %i\n\n", MAXTABLESIZE);
		return NULL;
	}

	hashtable_t hasher;
	hasher.size = hsize;
	for(int i = 0; i < hsize; i++){
		hasher.table[i] = qopen();
	}
	return &hasher;
}

//close all of the chains in the hash table that is pointed to by htb
void *hclose(hashtable_t *htb){
	for(int i = 0; i < htb->size; i++){
		qclose(htb->table[i]);
	}
}


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

