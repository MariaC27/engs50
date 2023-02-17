/* removetest.c --- 
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


	car_t *car1 = make_car(NULL, "TJF901", 10450, 2020);
	// remove test on none empty list
	car_t *car_remp = lremove(car1->plate);

	if (car_remp != NULL) { // checks if actual struct is empty
		printf("Failed to remove from empty list");
		return 1;	
	}

	// put cars into list
	int32_t empty_list_result = lput(car1);
	if (empty_list_result != 0){
		printf("Did not correctly add to empty list\n");
		return 1; 
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
		printf("Did not correctly add to non-empty list");
		return 1;
	}
	 
	car_t *car5_remp = lremove(car5->plate); // top car
	
	car_t *car1_remp = lremove(car1->plate); // bottom car

	car_t *car3_remp = lremove(car3->plate); // middle car
	
	if (strcmp(car5_remp->plate, "94L72D")!=0){ // check if plates are the same 
		printf("Failed to remove a top car correctly");
		return 1;
	}
	if (strcmp(car1_remp->plate, "TJF901")!=0){ // check if plates are the same 
		printf("Failed to remove a bottom car correctly");
		return 1;
	}
	if (strcmp(car3_remp->plate, "PPP444")!=0){ // check if plates are the same 
		printf("Failed to remove a middle car correctly");
		return 1;
	}

	// now we do lget and see if we properly removed using lremove
	car_t* car4p = lget();  
	car_t* car2p = lget();  		
	
	if ((strcmp(car4p->plate, "5624FG")!=0) || (strcmp(car2p->plate, "GRP452")!=0)) { // check is same cars came back in correct order
		printf("Fail: lget returned wrong match\n");
		return 1;
	}

	free(car1);
	free(car2);
	free(car3);
	free(car4);
	free(car5);

	return 0;
}
