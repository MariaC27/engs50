/* list.c --- implements the interface list.h
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Fri Jan 20 15:08:23 2023 (-0500)
 * Version: 1.0
 * 
 * Description: implements the interface list.h 
 * Justin - added line 25, need to transfer next pointer as well 01/23/2023
 */

#include "list.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static car_t *front=NULL;

int32_t lput(car_t *cp){ // place a car at the beginning of the list
	car_t *temp = malloc(sizeof(car_t));
	strcpy(temp->plate, cp->plate);
	temp->year = cp->year;
	temp->price = cp->price;
	temp->next = cp->next; 
	
	
	if(front==NULL){ // empty list
		front = temp;
	}
	else{ // non empty list
	  temp->next = front; 
		front = temp;
	}
	if ((front)==NULL)
		return 1;
	return 0;
}

car_t *lget(void){ //remove and return the first car in the list
	if ((front)==NULL){
		return NULL; 
	}

	car_t *temp = front; // stores first node to temp var

	front = (front)->next; // move front to next node

	return temp; // returns old first node
}


void lapply(void (*fn)(car_t *cp)){ // apply a function to every car in the list
	car_t *p;

	for (p=front; p!=NULL; p=p->next){
		fn(p);
	}
}

car_t *lremove(char *platep){ //find, remove, and return car with matching plate
	car_t *p, *f;
	car_t *temp;

	for (p=front; p!=NULL; p=p->next){
		if (strcmp(p->plate, platep)==0){ // to do - check syntax
			f->next = p->next;
			temp = p;
		}
		f=p;
	}

	return temp;
}
