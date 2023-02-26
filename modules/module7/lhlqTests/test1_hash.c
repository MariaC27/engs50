/* test1_hash.c --- tests for hash
 * 
 * 
 * Author: Miles B. Hudgins
 * Created: Sun Jan 29 15:22:51 2023 (-0500)
 * Version: 
 * 
 * Description: test open/close, put, and remove for hash
 * - Maria Cristoforo - edits 1/31: add malloc, remove
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lhash.h"
#include "queue.h"


typedef struct dog{
	double age;
	char name[10];
	char breed[30];
	int gender; //0 for female, 1 for male
}dog_t;//HASHKEY = name

dog_t *make_dog(double age, char* name, char* breed, int gender){
	dog_t *tmp = (dog_t*)malloc(sizeof(dog_t));
	tmp->age = age;
	strcpy(tmp->name, name);
	strcpy(tmp->breed, breed);
	tmp->gender = gender;
	return tmp;
}

bool search_queue(void* data, const void* keyp){
  dog_t* dog = data;
  if (strcmp(dog->name, keyp)==0)
    return true; // if equal
  return false; // if not equal
}


int main(void){
	lhashtable_t *lh1 = lhopen(10);

	dog_t *sparky = make_dog(4, "sparky", "border collie", 1);
	dog_t *rose = make_dog(3, "rose", "golden retriever", 0);
	int32_t put_res = lhput(lh1, (void*)sparky, sparky->name, strlen(sparky->name));
	if (put_res != 0){
		printf("Fail: did not hput successfully\n");
		return 1;
	}
	else{
		// put was successful, so repeat
		lhput(lh1, (void*)rose, rose->name, strlen(rose->name));
	}

	dog_t *d1 = make_dog(3, "rose", "gorgn", 0);
	dog_t *d2 = make_dog(3, "green", "gdsbv", 0);
	dog_t *d3 = make_dog(3, "green", "gwry4jmetngb", 0);
	dog_t *d4 = make_dog(3, "green", "goldeasdfgsd gr", 0);
	dog_t *d5 = make_dog(15, "green", "gasdf", 0);
	dog_t *d6 = make_dog(19, "green", "golden retriever", 0);
	dog_t *d7 = make_dog(15, "green", "golden retriever", 0);
	dog_t *d8 = make_dog(14, "green", "golden retriever", 0);
	dog_t *d9 = make_dog(13, "rose", "golden retriever", 0);
	dog_t *d10 = make_dog(24, "rose", "golden retriever", 0);
	dog_t *d11 = make_dog(2, "rose", "golden retriever", 0);

	lhput(lh1, (void*)d1, d1->name, strlen(d1->name));
	lhput(lh1, (void*)d2, d2->name, strlen(d2->name));
	lhput(lh1, (void*)d3, d3->name, strlen(d3->name));
	lhput(lh1, (void*)d4, d4->name, strlen(d4->name));
	lhput(lh1, (void*)d5, d5->name, strlen(d5->name));
	lhput(lh1, (void*)d6, d6->name, strlen(d6->name));
	lhput(lh1, (void*)d7, d7->name, strlen(d7->name));
	lhput(lh1, (void*)d8, d8->name, strlen(d8->name));
	lhput(lh1, (void*)d9, d9->name, strlen(d9->name));
	lhput(lh1, (void*)d10, d10->name, strlen(d10->name));
	lhput(lh1, (void*)d11, d11->name, strlen(d11->name));

	
	// here is
	dog_t* remove_res = (dog_t *)lhremove(lh1, search_queue, "sparky", 6);
	if (remove_res == NULL){
		printf("Fail: did not hremove successfully\n");
		return 1;
	}


	lhclose(lh1);
	free(sparky);
	free(rose);
	free(d1);
	free(d2);
	free(d3);
	free(d4);
	free(d5);
	free(d6);
	free(d7);
	free(d8);
	free(d9);
	free(d10);
	free(d11);
	
	return 0;
}
