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

/*
void print_car(char str[4], car_t car){
	printf("%s contents:\n   plate: %s\n   price:%f \n   year: %i\n", str, car.plate, car.price, car.year);
}
*/

int main(void){
	
	// original example: car_t car1 = { .plate = "SL5117" , .price = 30,000 , .year = 2014 };
	
	car_t car1 = { NULL, "SL5117", 30000 , 2014 }; // add to empty list test 

	int32_t empty_list_result = lput(&car1);
	if (empty_list_result != 0){
		printf("Did not correctly add to empty list\n");
		return 1; // exit
	}
	
	//car_t *front = &car1;

	car_t car2 = { NULL, "GRP452", 30000, 2003 };
	car_t car3 = { NULL, "PPP444", 33050, 2020 };
	car_t car4 = { NULL, "5624FG", 25000, 2004 };
	car_t car5 = { NULL, "94L72D", 10000, 1993 };

	int32_t t2 = lput(&car2);
	int32_t t3 = lput(&car3);
	int32_t t4 = lput(&car4);
	int32_t t5 = lput(&car5);

	int32_t t_total = t2+t3+t4+t5;

	if (t_total != 0){
		printf("Did not correctly add to non-empty list\n");
		return 1;
	}
}
