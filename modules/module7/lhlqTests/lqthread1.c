
 
/* qapplytest.c --- 
 * Author: Justin Sapun
 * Created: Monday Jan 30
 * Version: 
 * 
 * Description: To test apply function for queue.c module
 */

#include "lqueue.h"
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

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

// For pthread
void *decrease_age_func(void *data){
	lqueue_t *lqp = data;
	lqapply(lqp, decrease_age); // apply function to decrease age by 10
	return NULL;
}
int main(void){	

	person_t *one_p;
	person_t *two_p;
	person_t *three_p;

	struct lqueue_t* lqp;

	lqp = lqopen();
	
	one_p = make_person("Fred",20,4.6);
	two_p = make_person("Bill",15,5.9);
	three_p = make_person("Joe",42,9.7);


	int res1 = lqput(lqp, (void *)one_p);
	int res2 = lqput(lqp, (void *)two_p);
	int res3 = lqput(lqp, (void *)three_p);
	
	if ((res1+res2+res3) !=0){
		printf("Fail: did not qput successfully\n");
		exit(EXIT_FAILURE);
	}

	pthread_t tid1;
	
	if (pthread_create(&tid1, NULL, decrease_age_func, (void *)lqp)!=0)
    exit(EXIT_FAILURE);
	lqapply(lqp, print_person); // apply function prints persons

	//delay(1000);
	
	if (pthread_join(tid1,NULL)!=0)
		exit(EXIT_FAILURE);

	lqapply(lqp, print_person); // apply function prints persons
	
	
	if ((one_p->age != 10) || (two_p->age != 5) || (three_p->age != 32)) {
		printf("Fail: did not properly concat\n");
		exit(EXIT_FAILURE);
	}

	lqclose(lqp);	

	free(one_p);
	free(two_p);
	free(three_p);

	exit(EXIT_SUCCESS);
}
