/* lqueue.c --- implements the interface lqueue.h
 * 
 * Author: Justin Sapun
 * Created: 02/24/2023 
 * Description: Locked Queue data structure created with linked list approach 
 */

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
	struct lqueue_t* tmp = (struct lqueue_t*)malloc(sizeof(struct lqueue_t));
	tmp->front = NULL;
	tmp->back = NULL;

	// Create mutex
	pthread_mutex_init(&m, NULL);

	return tmp;
}

/* deallocate a queue, frees everything in it */
void lqclose(lqueue_t *lqp) { // deallocate queue
	struct lqueue_t* q = lqp;

	pthread_mutex_lock(&m);
	
	for (Node_t* current=q->front; current!=NULL;){
		Node_t* tmp = current->next;
		free(current);
		current = tmp;
	}
	// Destroy mutex
	pthread_mutex_unlock(&m);
	pthread_mutex_destroy(&m);
	
	free(q);
}

/* put element at the end of the queue*/
int32_t lqput(lqueue_t *lqp, void *elementp){ 
	struct lqueue_t* q = lqp;

	// Lock and Unlock mutex
	pthread_mutex_lock(&m);
	
	if (q->front == NULL) { 	// adding to empty queue
		q->front = (struct Node *)malloc(sizeof(Node_t));	// space
		q->front->data = (struct Node *)elementp;			// add elements to node
		q->front->next = NULL; 	// no next node
		q->back = q->front; 	// no next node
	}
	else { 						// adding to non-empty queue
		q->back->next = (struct Node *)malloc(sizeof(Node_t)); 
		q->back->next->data = (struct Node *)elementp; 			
        q->back->next->next = NULL;
        q->back = q->back->next;
	}
	
	if (q->front == NULL){ // fail if queue is still empty
		pthread_mutex_unlock(&m);
		return 1;
	}
	pthread_mutex_unlock(&m);
	return 0;
}

/* get the first element from queue, removing it from the queue*/
void* lqget(lqueue_t *lqp){
	struct lqueue_t *q = lqp;

	pthread_mutex_lock(&m);

	if (q->front == NULL) // if empty queue
		return NULL;
	Node_t* tmp = q->front;
	void* elem = tmp->data;
	q->front = tmp->next;
	free(tmp);

	pthread_mutex_unlock(&m);
	
	return elem;
}
/* apply a function to every element of the queue */
void lqapply(lqueue_t *lqp, void (*fn)(void* elementp)){
	struct lqueue_t *q = lqp;
	
	pthread_mutex_lock(&m);

	//delay(2000); // for testing purposes
	
	for (Node_t* current=q->front; current!=NULL;current=current->next){
		fn(current->data);
	}
	pthread_mutex_unlock(&m);
}

void* lqsearch(lqueue_t *lqp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){
	struct lqueue_t *q = lqp;

	pthread_mutex_lock(&m);

	for (Node_t* current=q->front; current!=NULL;current=current->next){
		if (searchfn(current->data, skeyp)){
			pthread_mutex_unlock(&m);
			return (void *)current->data; // if found
		}
	}

	pthread_mutex_unlock(&m);
	
	return NULL; // if not found
}
