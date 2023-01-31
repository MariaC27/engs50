/* queue.c --- implements the interface queue.h
 * 
 * Author: Justin Sapun
 * Created: Wed Jan 26 
 * Description: Queue data structure created with linked list approach 
 */

#include "queue.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {	
	struct Node *data;
    struct Node* next;
} Node_t;

struct queue_t {
	struct Node* front;
	struct Node* back;
};

/* create an empty queue */
queue_t* qopen(void) { // Open Queue without nodes
	struct queue_t* tmp = (struct queue_t*)malloc(sizeof(struct queue_t));
	tmp->front = NULL;
	tmp->back = NULL;
	return tmp;
}

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp) { // deallocate queue
	struct queue_t* q = qp;

	for (Node_t* current=q->front; current!=NULL;){
		Node_t* tmp = current->next;
		free(current);
		current = tmp;
	}
	free(q);
}

/* put element at the end of the queue*/
int32_t qput(queue_t *qp, void *elementp){ 
	struct queue_t* q = qp;

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
	if (q->front == NULL) // fail if queue is still empty
		return 1;
	return 0;
}

/* get the first element from queue, removing it from the queue*/
void* qget(queue_t *qp){
	struct queue_t *q = qp;

	if (q->front == NULL) // if empty queue
		return NULL;
	Node_t* tmp = q->front;
	void* elem = tmp->data;
	q->front = tmp->next;
	free(tmp);
	return elem;
}
/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	struct queue_t *q = qp;

	for (Node_t* current=q->front; current!=NULL;current=current->next){
		fn(current->data);
	}
}

/* search a queue using a supplied boolean function --- not sure if works*/
void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){
	struct queue_t *q = qp;

	for (Node_t* current=q->front; current!=NULL;current=current->next){
		if (searchfn(current->data, skeyp))
			return (void *)current->data; // if found
	}
	return NULL; // if not found
}

/* search a queue using a supplied boolean function and remove*/
void* qremove(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){
	struct queue_t *q = qp;
	Node_t* curr;
	Node_t* prev;

	for (curr=q->front; curr!=NULL; curr=curr->next){
		if (searchfn(curr->data, skeyp)) { // check keys

			if(curr == q->back){
				prev->next = NULL;
				q->back = prev;
				void* tmp_data = curr->data;
				free(curr);
				return tmp_data;
			}
			else if(curr == q->front){
				q->front = curr->next;
				void* tmp_data = curr->data;
				free(curr);
				return tmp_data;
			}
			else{
				prev->next = curr->next;
				void* tmp_data = curr->data;
				free(curr);
				return tmp_data; 
			}
		}
		prev=curr;
	}
	return NULL;
}

/* concatenates elements of q2 into q1
q2 is dealocated, closed, and unusable upon completion */
void qconcat(queue_t *q1p, queue_t *q2p){
	struct queue_t *q1 = q1p;
	struct queue_t *q2 = q2p;

	q1->back->next = q2->front;
	q1->back = q2->back;

	free(q2);
}
