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

int main(void){	

	car_t car1 = { NULL, "SL5117", 30000 , 2014 }; // add to empty list test 
	
	// remove test on none empty list
	car_t *car_remp = lremove(car1.plate);

	if (car_remp != NULL) { // checks if actual struct is empty
		printf("Failed to remove from empty list");
		return 1;	
	}

	// put cars into list
	int32_t empty_list_result = lput(&car1);
	if (empty_list_result != 0){
		printf("Did not correctly add to empty list\n");
		return 1; 
	}
	
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
		printf("Did not correctly add to non-empty list");
		return 1;
	}
	printf("\n"); // will not work without this print line, has something to do with memory allocation

	car_t *car5_remp = lremove(car5.plate); // top car
	car_t car5_rem = *car5_remp; // intalize back to car_t
	


	car_t *car1_remp = lremove(car1.plate); // bottom car
	car_t car1_rem = *car1_remp; 

	car_t *car3_remp = lremove(car3.plate); // middle car
	car_t car3_rem = *car3_remp; 
	
	
	if (strcmp(car5.plate, car5_rem.plate)){ // check if plates are the same 
		printf("Failed to remove a top car correctly");
		return 1;
	}
	if (strcmp(car1.plate, car1_rem.plate)){ // check if plates are the same 
		printf("Failed to remove a bottom car correctly");
		return 1;
	}
	if (strcmp(car3.plate, car3_rem.plate)){ // check if plates are the same 
		printf("Failed to remove a middle car correctly");
		return 1;
	}

	// now we do lget and see if we properly removed using lremove

	car_t *car4p = lget();  // should be car 4			
	car_t *car2p = lget(); // car 2 - no more cars after this
	car_t *car_null_p = lget();

	car_t car2_rem = *car2p; 
	car_t car4_rem = *car4p; 
	car_t car_null = *car_null_p; 


	printf(car_null.plate);
	printf("\n");

	printf(car2_rem.plate);
	printf("\n");
	printf(car4_rem.plate);
	printf("\n");
	printf(car2.plate);
	printf("\n");
	printf(car4.plate);



	if (strcmp(car2_rem.plate, car2.plate)==0){ // check is same cars came back in correct order
		printf("Match");
		return 1;
	}
	printf("doesnt match");
	return 0;

}
