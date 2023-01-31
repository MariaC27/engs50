

/* qconcattest.c --- 
 * Author: Justin Sapun
 * Created: Monday Jan 30
 * Version: 
 * 
 * Description: To test qconcat function for queue.c module
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

typedef struct building {
	char location[10];
	int age;
	double cost;
} building_t;

person_t* make_person(char* name, int age, double rate){
  person_t *tmp = malloc(sizeof(person_t));
  strcpy(tmp->name, name);
  tmp->age = age;
  tmp->rate = rate;
  return tmp;
}
building_t* make_building(char* location, int age, double cost){
  building_t* tmp = malloc(sizeof(building_t));
  strcpy(tmp->location, location);
  tmp->age = age;
  tmp->cost = cost;
  return tmp;
}

int main(void){	

	person_t *one_p;
	person_t *two_p;
	person_t *three_p;
	building_t *one_b;
	building_t *two_b;
	building_t *three_b;


	struct queue_t* qp_1;
	struct queue_t* qp_2;

	qp_1 = qopen();
	qp_2 = qopen();

	one_p = make_person("Fred",20,4.6);
	two_p = make_person("Bill",15,5.9);
	three_p = make_person("Joe",42,9.7);

	one_b = make_building("Manhattan",11,1000000);
	two_b = make_building("LA",27,560000);
	three_b = make_building("Chicago",57,230000);


	int res1 = qput(qp_1, (void *)one_p);
	int res2 = qput(qp_1, (void *)two_p);
	int res3 = qput(qp_1, (void *)three_p);

	int res4 = qput(qp_2, (void *)one_b);
	int res5 = qput(qp_2, (void *)two_b);
	int res6 = qput(qp_2, (void *)three_b);
	
	if ((res1+res2+res3+res4+res5+res6) !=0){
		printf("Fail: did not qput successfully\n");
		return 1;
	}

	qconcat(qp_1,qp_2); // put everything into qp_1 and closes qp_2

	// use qget

	void* one_res = qget(qp_1);
	void* two_res = qget(qp_1);
	void* three_res = qget(qp_1);

	void* one_b_res = qget(qp_1);
	void* two_b_res = qget(qp_1);
	void* three_b_res = qget(qp_1);

	// test that pointers are same

	if (((void *)one_p != one_res) || ((void *)two_p != two_res) || ((void *)three_p != three_res)) {
		return 1;
		printf("Fail: did not properly concat\n");
	}

	if (((void *)one_b != one_b_res) || ((void *)two_b != two_b_res) || ((void *)three_b != three_b_res)) { // fails here
		return 1;
		printf("Fail: did not properly concat\n");
	}

	free(one_p); // free local structs
	free(two_p);
	free(three_p);
	free(one_b);
	free(two_b);
	free(three_b);

	qclose(qp_1); // close and deallocate queue

	return 0;
}
