

/* qclose_test.c --- 
 * Author: Justin Sapun
 * Created: Monday Jan 30
 * Version: 
 * 
 * Description: To test qclose function for queue.c module
 */

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct person {
	char name[10];
	int age;
	double rate;
} person_t;

person_t* make_person(char* name, int age, double rate){
  person_t *tmp = malloc(sizeof(person_t));
  strcpy(tmp->name, name);
  tmp->age = age;
  tmp->rate = rate;
  return tmp;
}


int main(void){	

	person_t *one_p;
	person_t *two_p;
	person_t *three_p;


	struct queue_t* qp_1;

	qp_1 = qopen();
	
	one_p = make_person("Fred",20,4.6);
	two_p = make_person("Al",15,5.9);
	three_p = make_person("McChicken",42,9.7);


	int res1 = qput(qp_1, (void *)one_p);
	int res2 = qput(qp_1, (void *)two_p);
	int res3 = qput(qp_1, (void *)three_p);
	
	if ((res1+res2+res3) !=0){
		printf("Fail: did not qput successfully\n");
		return 1;
	}

	// do not use qget
	
	qclose(qp_1);	// qclose should deallocate queue and its 3 elements

	free(one_p); // free local structs
	free(two_p);
	free(three_p);
	
	return 0;
}
