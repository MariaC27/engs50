/* applytest.c --- 
 * 
 * 
 * Author: Miles B. Hudgins / Justin Sapun
 * Created: Tues Jan 24 15:07:10 2023 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include "list.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


car_t* make_car(car_t* next, char* plate, double price, int year){
  car_t *retp = malloc(sizeof(car_t));
  retp->next = next;
  strcpy(retp->plate, plate);
  retp->price = price;
  retp->year = year;

  return retp;
}

void decrease_price(car_t *car){
	car->price = car->price -1000;
}

int main(void){

	int prices[5] = {30000, 20000, 10000, 50000, 12000};	
  	car_t *car5 = make_car(NULL, "IDN502", prices[4], 2006);
	car_t *car4 = make_car(NULL, "APB469", prices[3], 2005);
	car_t *car3 = make_car(NULL, "GTF401", prices[2], 2004);
	car_t *car2 = make_car(NULL, "GRP452", prices[1], 2003);
	car_t *car1 = make_car(NULL, "IGV501", prices[0], 2014);
	
	lput(car5);
	lput(car4);
	lput(car3);
	lput(car2);
	lput(car1);
	
	lapply(decrease_price);


	if (car1->price!=prices[0]-1000 ||
		car2->price!=prices[1]-1000 ||
		car3->price!=prices[2]-1000 ||
		car4->price!=prices[3]-1000 ||
		car5->price!=prices[4]-1000){
		printf("Fail: did not properly complete apply test\n");
		return 1;
	}

	free(car1);
	free(car2);
	free(car3);
	free(car4);
	free(car5);

	return 0;
}

