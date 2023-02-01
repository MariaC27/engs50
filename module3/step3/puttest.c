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

car_t* make_car(car_t* next, char* plate, double price, int year){
	car_t *retp = malloc(sizeof(car_t));
	retp->next = next;
	strcpy(retp->plate, plate);
	retp->price = price;
	retp->year = year;

	return retp;
}

int main(void){

	car_t *car1 = make_car(NULL, "SL5117", 30000, 2014);
	car_t *car2 = make_car(NULL, "94L72D", 10000, 1993);
	car_t *car3 = make_car(NULL, "GRP452", 30000, 2003);
	car_t *car4 = make_car(NULL, "PPP444", 33050, 2020);
	car_t *car5 = make_car(NULL, "5624FG", 25000, 2004);

	lput(car1);// add to empty list test
	lput(car2);
	lput(car3);
	lput(car4);
	lput(car5);
	

	free(car1);
	free(car2);
	free(car3);
	free(car4);
	free(car5);
	
	return 0;
}
