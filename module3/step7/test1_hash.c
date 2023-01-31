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
#include "hash.h"

typedef struct dog{
	double age;
	char *name;
	char *breed;
	int gender; //0 for female, 1 for male
}dog_t;//HASHKEY = name

dog_t *make_dog(double age, char* name, char* breed, int gender){
	dog_t* tmp = malloc(sizeof(dog_t));
	tmp->age = age;
	strcpy(name,   tmp->name);
	strcpy(breed, tmp->breed);
	tmp->gender = gender;
	return tmp;
}

bool search_queue(void* data, const void* keyp){
  dog_t* dog = data;

  if (!strcmp(dog->name, keyp))
    return true; // if equal
  return false; // if not equal
}


int main(void){
	hashtable_t *h1 = hopen(10);
	dog_t *sparky  = make_dog(4, "sparky", "border collie", 1);
	dog_t *rose = make_dog(2.5, "rose", "golden retriever", 0);
	
	int32_t put_res = hput(h1, (void*)sparky, sparky->name, strlen(sparky->name));
	if (put_res != 0){
		printf("Fail: did not hput successfully\n");
		return 1;
	}
	else{
		// put was successful, so repeat
		hput(h1, (void*)rose, rose->name, strlen(rose->name));
	}

	void* remove_res = hremove(h1, search_queue, sparky->name, strlen(sparky->name));
	if (remove_res == NULL){
		printf("Fail: did not hremove successfully\n");
		return 1;
	}

	hclose(h1);
	free(sparky);
	free(rose);

	return 0;
}
