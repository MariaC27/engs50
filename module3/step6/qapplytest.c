

/* qapplytest.c --- 
 * Author: Justin Sapun
 * Created: Monday Jan 30
 * Version: 
 * 
 * Description: To test apply function for queue.c module
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
  person_t* tmp = malloc(sizeof(person_t));
  strcpy(tmp->name, name);
  tmp->age = age;
  tmp->rate = rate;
  return tmp;
}

void print_person(void* data){
	person_t* person = data;
	printf("\nName: %s\nAge: %i\nRate %f\n", person->name, person->age, person->rate);
}

void decrease_age(void* data){
	person_t* person = data;
	person->age = person->age - 10;
}

int main(void){	

	person_t *one_p;
	person_t *two_p;
	person_t *three_p;

	struct queue_t* qp;

	qp = qopen();
	
	one_p = make_person("Fred",20,4.6);
	two_p = make_person("Bill",15,5.9);
	three_p = make_person("Joe",42,9.7);


	int res1 = qput(qp, (void *)one_p);
	int res2 = qput(qp, (void *)two_p);
	int res3 = qput(qp, (void *)three_p);
	
	if ((res1+res2+res3) !=0){
		printf("Fail: did not qput successfully\n");
		return 1;
	}

	//qapply(qp, print_person); // apply function prints persons
	qapply(qp, decrease_age); // apply function to decrease age by 10

	if ((one_p->age != 10) || (two_p->age != 5) || (three_p->age != 32)) {
		printf("Fail: did not properly concat\n");
		return 1;
	}

	qclose(qp);	

	free(one_p);
	free(two_p);
	free(three_p);

	return 0;
}
