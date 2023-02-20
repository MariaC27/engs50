
/* qputgettest.c --- 
 *
 * Author: Justin Sapun
 * Created: Thursday Jan 27
 * Version: 
 * 
 * Description: To test qput and qget
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
	struct queue_t *qp;

	qp = qopen();

	pp = make_person("Fred",20,4.6);

	int32_t res = qput(qp, (void *)pp);

	if (res) {
		printf("Fail: did not qput successfully\n");
		return 1;
	}

	void* pp_res = qget(qp);

	if ((void *)pp != (void *)pp_res){
		printf("Fail: did not qget successfully\n");
		return 1;
	}
	
	qclose(qp); // free queue

	free(pp);	// free person_t	
	
	return 0;

}

