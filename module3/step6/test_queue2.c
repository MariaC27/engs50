

/* test_queue1.c --- 
 * 
 * 
 * Author: Justin Sapun
 * Created: Thursday Jan 27
 * Version: 
 * 
 * Description: 
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

	person_t *one;
	person_t *two;
	person_t *three;

	struct queue_t *qp;

	qp = qopen();

	one = make_person("Fred",20,4.6);
	two = make_person("Bill",15,5.9);
	three = make_person("Joe",42,9.7);


	int res1 = qput(qp, (void *)one);
	int res2 = qput(qp, (void *)two);
	int res3 = qput(qp, (void *)three);
	int x =res1+res2+res3; 
	if (x !=0)
		return 1;
	printf("%i\n",x);

	person_t* one_res = (person_t *)qget(qp);
	person_t* two_res = (person_t *)qget(qp);
	person_t* three_res = (person_t *)qget(qp);


	printf("pp pointer: %p\n",(void *)one);
	printf("pp_res pointer: %p\n",(void *)one_res);

	if ((strcmp((void *)one,(void *)one_res)) || (strcmp((void *)two,(void *)two_res)) || (strcmp((void *)three,(void *)three_res))){
		printf("Fail: pointers don't match");
		return 1;
	}
	
	// do apply and search test
		
	qclose(qp);

	return 0;

}
