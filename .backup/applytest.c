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

int main(void){

	car_t *car1 = make_car(NULL, "SL5117", 30000 , 2014);


  lput(make_car(NULL, "GRP452", 30000, 2003));
  lput(make_car(NULL, "PPP444", 33050, 2020));
  lput(make_car(NULL, "5624FG", 25000, 2004));
  lput(make_car(NULL, "94L72D", 10000, 1993));
  lput(car1);

	int prices[5] = {30000, 33050, 25000, 10000, 30000}
	lapply(decrease_price);

	for(car_t *f = car1; f !=NULL; f = f->next){
    if(prices[i] == f
  }

	printf("%f : %f\n\n", price1, car1.price);
	if(car1.price==price1-1000 &&
		 car2.price==price2-1000 &&
		 car3.price==price3-1000 &&
		 car4.price==price4-1000 &&
		 car5.price==price5-1000){
		printf("function applied successfully\n");
		return 0;
	}
	else
		printf("function not applied correctly\n");
}

