/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "queue.h"
#include "lhash.h"
#include <pthread.h>


pthread_mutex_t m;

void delay(int number_of_seconds){
  // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


//open a new table with size hsize
hashtable_t *lhopen(uint32_t hsize){
	// Create mutex
  pthread_mutex_init(&m, NULL);
	return hopen(hsize);;
}

//close all of the chains in the hash table that is pointed to by htb
void lhclose(hashtable_t *lhtp){
	pthread_mutex_lock(&m);
	hclose(lhtp);
	pthread_mutex_unlock(&m);
	pthread_mutex_destroy(&m);
}


//put node ep into hashtable pointed to by htp with key key and key length keylen
int32_t lhput(lhashtable_t *lhtp, void *ep, const char *key, int keylen){
	pthread_mutex_lock(&m);
	hput(lhtp, ep, key, keylen);
	pthread_mutex_unlock(&m);
	return 0;
}

/* happly -- applies a function to every entry in hash table */
void lhapply(lhashtable_t *lhtp, void (*fn)(void* ep)){
	pthread_mutex_lock(&m);
	happly(lhtp, fn);
	pthread_mutex_unlock(&m);
}

/* hsearch -- searchs for an entry under a designated key using a
 * designated search fn -- returns a pointer to the entry or NULL if
 * not found
 */
void *lhsearch(lhashtable_t *lhtp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen){
	pthread_mutex_lock(&m);
	void *n = hsearch(lhtp, searchfn, key, keylen);
	pthread_mutex_unlock(&m);
	return n;
}

void *lhremove(lhashtable_t *lhtp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen){
	pthread_mutex_lock(&m);
	void* n = hremove(lhtp, searchfn, key, keylen);
	pthread_mutex_unlock(&m);
	return n;
}
