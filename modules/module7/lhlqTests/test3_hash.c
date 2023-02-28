/* test3_hash.c --- 
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Tue Jan 31 01:14:53 2023 (-0500)
 * Version: 1.0
 * 
 * Description: test search and remove functions for hash 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lhash.h"
#include "queue.h"

typedef struct dog{
	double age;
	char name[10];
	char breed[30];
	int gender;
}dog_t;

dog_t *make_dog(double age, char* name, char* breed, int gender){
	dog_t *tmp = (dog_t*)malloc(sizeof(dog_t));
	tmp->age = age;
	strcpy(tmp->name, name);
	strcpy(tmp->breed, breed);
	tmp->gender = gender;
	return tmp;
}


bool search_hash(void* data, const void* key){
	dog_t *dog1 = data;

	if (!strcmp(dog1->name, key))
		return true;
	return false;
}

void print_dog(void* data){
	dog_t* dog = data;
	printf("\n Name: %s \n Age: %f \n", dog->name, dog->age);
}


int main(void){
	
	lhashtable_t* lh1 = lhopen(10);
	dog_t *sparky = make_dog(4, "sparky", "border collie", 1);
	dog_t *rose = make_dog(2.5, "rose", "golden retriever", 0);
	dog_t *misty = make_dog(10, "misty", "poodle", 0);

	int32_t res1 = lhput(lh1, (void*)sparky, sparky->name, strlen(sparky->name));
	int32_t res2 = lhput(lh1, (void*)rose, rose->name, strlen(rose->name));
  int32_t res3 = lhput(lh1, (void*)misty, misty->name, strlen(misty->name));

	if ((res1 + res2 + res3) != 0){
		printf("Failed to put successfully\n");
		return 1;
	}
		
	// testing for search

	const void* fake_key = "teddy";
	const void* key1 = "rose";

	//check using fake/real keys
	if ( lhsearch(lh1, search_hash, fake_key, strlen(fake_key)) != NULL ){
		printf("Fail: using fake key, should have returned NULL but did not\n");
		return 1;
	}
	
	if ( lhsearch(lh1, search_hash, key1, strlen(key1)) == NULL ){
		printf("Fail: using real key, should not have returned NULL but did\n");
		return 1;
	}
	
	//check if the right data is returned for the key

	void* key1_res = lhsearch(lh1, search_hash, key1, strlen(key1));

	if ((void*)rose != key1_res){
		printf("Fail: did not return the correct data\n");
		return 1;
	}
	
	lhclose(lh1);
	free(sparky);
	free(rose);
	free(misty);
}
