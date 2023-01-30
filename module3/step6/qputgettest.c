/* qopentest.c --- test for queue module
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Thu Jan 26 10:48:35 2023 (-0500)
 * Version: 1.0 
 * 
 * Description: test functions qopen(), qclose(), qput(), and qget() in queue.c 
 * 
 */

#include "list.h"
#include "queue.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>


car_t* make_car(car_t* next, char* plate, double price, int year){
	car_t *newcar = malloc(sizeof(car_t));
	newcar->next = next;
	strcpy(newcar->plate, plate);
	newcar->price = price;
	newcar->year = year;

	return newcar;

}

int main (void) {
	qp = qopen()
		
	car_t car1 = make_car(NULL, "5RPD50", 19000, 2015);
	
	qput(qp, (void*)car1);


	for (car_t *f = c1; f != NULL; f = f->next){
		print("%s\n", f->plate);
	}
	
	car1 = (car_t*)qget();

	qclose(qp); // note: clear out queue before closing

}
