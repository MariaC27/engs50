/* gettest.c --- 
 * 
 * 
 * Author: Justin Sapun
 * Created: Sun Jan 23
 * Version: 
 * 
 * Description: 
 */

#include "list.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


car_t* make_car(car_t* next, char* plate, double price, int year){
  car_t *retp = malloc(sizeof(car_t));
  retp->next = next;
  strcpy(retp->plate, plate);
  retp->price = price;
  retp->year = year;

  return retp;
}


int main(void){	
	car_t *car1 = make_car(NULL, "SL5117", 30000 , 2014); // add to empty list test 

	int32_t empty_list_result = lput(car1);
	if (empty_list_result != 0){
		printf("Did not correctly add to empty list\n");
		return 1; // exit
	}

	car_t *car2 = make_car(NULL, "GRP452", 30000, 2003);
  	car_t *car3 = make_car(NULL, "PPP444", 33050, 2020);
  	car_t *car4 = make_car(NULL, "5624FG", 25000, 2004);
  	car_t *car5 = make_car(NULL, "94L72D", 10000, 1993);


  	int32_t t2 = lput(car2);
  	int32_t t3 = lput(car3);
  	int32_t t4 = lput(car4);
  	int32_t t5 = lput(car5);

	int32_t t_total = t2+t3+t4+t5;

	if (t_total != 0){
		printf("Did not correctly add to non-empty list\n");
		return 1;
	}

	lget();					// didn't intalize others because of unused warning
	car_t *car7p = lget();
	lget();
	lget();
	car_t *car10p = lget(); // remove last element, actual end is here
	car_t *car11p = lget(); // remove from empty list

	car_t car7 = *car7p; // intalize back to car_t

	if (strcmp(car7.plate, car4->plate)){ // check is same cars came back in correct order
		printf("Failed to remove a car correctly\n");
		return 1;
	}
	if ((void *)car10p->next != NULL){ // checks if pointer is empty or actual struct is empty
		printf("Failed to remove last car\n");
		return 1;
	}
	if ((void *)car11p != NULL) { // checks if pointer is empty or actual struct is empty
		printf("Failed to fail when removing from empty list\n");
		return 1;	
	}

	free(car1);
	free(car2);
	free(car3);
	free(car4);
	free(car5);
	
	return 0;
}
