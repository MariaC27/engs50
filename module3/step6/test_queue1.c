/* test_queue1.c --- 
0;10;1c0;10;1c * 
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

	person_t *pp;
	person_t *pp_res;
	struct queue_t *qp;

	qp = qopen();

	pp = make_person("Fred",20,4.6);

	printf("\nBefore qget: \n");
	printf("%s's age: %i\n",pp->name,pp->age);
	printf("%s's rate: %f\n",pp->name,pp->rate);

	int32_t res = qput(qp, (void *)pp);

	pp_res = (person_t *)qget(qp);

	//printf("pp pointer: %p\n",(void *)pp);
	//printf("pp_res pointer: %p\n",(void *)pp_res);

	printf("\nAfter qget: \n");
	printf("%s's age: %i\n",pp_res->name,pp_res->age);
	printf("%s's rate: %f\n",pp_res->name,pp_res->rate);

	free(pp);
	free(pp_res);
	
	
	
	qclose(qp);

	if (res)
		return 1;
	return 0;

}

