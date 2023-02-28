/* lqueue.c --- implements the interface lqueue.h
 * 
 * Author: Justin Sapun
 * Created: 02/24/2023 
 * Description: Locked Queue data structure created with linked list approach 
 */

#include "queue.h"
#include "lqueue.h"
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


pthread_mutex_t m;

typedef struct Node {	
	struct Node *data;
    struct Node* next;
} Node_t;

struct lqueue_t {
	struct Node* front;
	struct Node* back;
};


void delay(int number_of_seconds){
	// Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


/* create an empty queue */
lqueue_t* lqopen(void) { // Open Queue without nodes
	pthread_mutex_init(&m, NULL);
	return qopen();
}

/* deallocate a queue, frees everything in it */
void lqclose(lqueue_t *lqp) { // deallocate queue
	pthread_mutex_lock(&m);
	qclose(lqp);
	pthread_mutex_unlock(&m);
	pthread_mutex_destroy(&m);
}

/* put element at the end of the queue*/
int32_t lqput(lqueue_t *lqp, void *elementp){ 
	pthread_mutex_lock(&m);
	qput(lqp, elementp);
	pthread_mutex_unlock(&m);
	return 0;
}

/* get the first element from queue, removing it from the queue*/
void* lqget(lqueue_t *lqp){
	pthread_mutex_lock(&m);
	void *elem = qget(lqp);
	pthread_mutex_unlock(&m);
	return elem;
}
/* apply a function to every element of the queue */
void lqapply(lqueue_t *lqp, void (*fn)(void* elementp)){
	pthread_mutex_lock(&m);
	qapply(lqp, fn);
	pthread_mutex_unlock(&m);
}

void* lqsearch(lqueue_t *lqp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){
	//pthread_mutex_lock(&m);
	void *ret = qsearch(lqp, searchfn, skeyp);
	//pthread_mutex_unlock(&m);
	return ret; // if not found
}
