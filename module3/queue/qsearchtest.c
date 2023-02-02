

/* qsearchtest.c --- 
 * Author: Justin Sapun
 * Created: Monday Jan 30
 * Version: 
 * 
 * Description: To test qsearch and qremove function for queue.c module
 */

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


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

bool search_queue(void* data, const void* keyp){
	person_t* person = data;

	if (!strcmp(person->name, keyp))
		return true; // if equal
	return false; // if not equal
}
void print_person(void* data){
	person_t* person = data;
	printf("\nName: %s\nAge: %i\nRate %f\n", person->name, person->age, person->rate);
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

	// the following section focuses on checking search function
	const void* skeyp = "Hello";
	const void* skeyp2 = "Bill";


	if (qsearch(qp, search_queue, skeyp) != NULL){ // remove with false key
		printf("Fail: qsearch should've returned NULL but didn't");
		return 1;
	}
	if (qsearch(qp, search_queue, skeyp2) == NULL){
		printf("Fail: qsearch shouldn't return NULL but did");
		return 1;
	}
	void* skeyp2_res = qsearch(qp, search_queue, skeyp2); // remove with possible key
	
	if ((void *)two_p != skeyp2_res) {
		printf("Fail: qsearch did not return correct person");
		return 1;
	}
	
	// the following section focuses on checking the remove function

	const void* skeyp3 = "Hola";
	const void* skeyp4 = "Fred";

	if (qremove(qp, search_queue, skeyp3) != NULL){ // remove with false key
		printf("Fail: qsearch should've returned NULL but didn't");
		return 1;
	}

	void* skeyp4_res = qremove(qp, search_queue, skeyp4); // remove with possible key

	if ((void *)one_p != skeyp4_res){
		printf("Fail: qremove did not return correct person");
		return 1;
	}

	void* bill_res = qget(qp);
	if ((void *)two_p != bill_res){
		printf("Fail: qget did not return bill implying qremove did not work");
		return 1;
	}

	qclose(qp);	

	free(one_p);
	free(two_p);
	free(three_p);
	
	return 0;
}
