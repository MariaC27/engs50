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
	printf("car price: %f\n\n", car->price);
	car->price = car->price -1000;
	printf("car price: %f\n\n", car->price);
}

void print_car(car_t *car){
	printf("plate: %s\nprice: %f\nyear %i\n\n", car->plate, car->price, car->year);
}

int main(void){

	int prices[5] = {30000, 20000, 10000, 50000, 12000};	
  car_t *car5 = make_car(NULL, "IDN502", prices[5], 2006);
	car_t *car4 = make_car(NULL, "APB469", prices[4], 2005);
	car_t *car3 = make_car(NULL, "GTF401", prices[3], 2004);
	car_t *car2 = make_car(NULL, "GRP452", prices[2], 2003);
	car_t *car1 = make_car(NULL, "IGV501", prices[1], 2014);
	lput(car5);
	lput(car4);
	lput(car3);
	lput(car2);
	lput(car1);
	
	//	lapply(decrease_price);
	lapply(print_car);

	int returncode = 0;
	/*int i = 0;
	for(car_t *f = car1; f !=NULL; f = f->next){
    if(prices[i] != f->price+1000){
			printf("bad\n");
			returncode = 1;
		}
		else
			printf("good\n");
		i++;
		}*/

	if(returncode == 0)
		printf("function applied correctly\n");
	else
		printf("function not applied corectly\n");


	return returncode;

	/*printf("%f : %f\n\n", price1, car1.price);
	if(car1.price==price1-1000 &&
		 car2.price==price2-1000 &&
		 car3.price==price3-1000 &&
		 car4.price==price4-1000 &&
		 car5.price==price5-1000){
		printf("function applied successfully\n");
		return 0;
	}
	else
	printf("function not applied correctly\n");*/

	
}

