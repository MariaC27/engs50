/* list.c --- implements the interface list.h
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Fri Jan 20 15:08:23 2023 (-0500)
 * Version: 1.0
 * 
 * Description: implements the interface list.h 
 * Justin - added line 25, need to transfer next pointer as well 01/23/2023
 * Justin - added line 67, need to convert pointer to car object 01/24/2023
 */

#include "list.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static car_t *front=NULL;
static car_t *back=NULL;



/*id print_car(car_t *car){
  printf("plate: %s\nprice: %f\nyear %i\n\n", car->plate, car->price, car->year);
}



  void print_all(){
	for(car_t *f = front; f != NULL; f = f->next){
		print_car(f);
	}
	}*/

int32_t lput(car_t *cp){ // place a car at the beginning of the list	
	if(front==NULL){ // empty list
		front = cp;
		back = cp;
	}
	else{ // non empty list
	  cp->next = front; 
		front = cp;
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
	car_t *temp = NULL;

	for (p=front; p!=NULL; p=p->next){
		car_t node = *p;
		if (strcmp(node.plate, platep)==0){ // to do - check syntax
			if(p == back){
				f->next = NULL;
				back = f;
				return p;
			}
			else if(p ==front){
				front = p->next;
				return p;
			}
			else{
				f->next = p->next;
				temp = p;
				return temp; // pretty sure this is needed
			}
		}
		f=p;
	}
	return temp;

	
}
