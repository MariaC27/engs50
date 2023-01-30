/* puttest.c --- 
 * 
 * 
 * Author: Miles B. Hudgins / Justin Sapun
 * Created: Sun Jan 22 15:07:10 2023 (-0500)
 * Version: 
 * 
 * Description: 
 * Justin - organized and simplified 01/23/2023
 */

#include "list.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
void print_car(char str[4], car_t car){
	printf("%s contents:\n   plate: %s\n   price:%f \n   year: %i\n", str, car.plate, car.price, car.year);
}
*/

car_t* make_car(car_t* next, char* plate, double price, int year){
	car_t *retp = malloc(sizeof(car_t));
	retp->next = next;
	strcpy(retp->plate, plate);
	retp->price = price;
	retp->year = year;

	return retp;
}

int main(void){

	car_t *car1 = make_car(NULL, "SL5117", 30000 , 2014);

	
	lput(make_car(NULL, "GRP452", 30000, 2003));
	lput(make_car(NULL, "PPP444", 33050, 2020));
	lput(make_car(NULL, "5624FG", 25000, 2004));
	lput(make_car(NULL, "94L72D", 10000, 1993));
	lput(car1);// add to empty list test

	for(car_t *f = car1; f !=NULL; f = f->next){
		printf("%s\n", f->plate);
	}
	return 0;
}
