/* test2_hash.c --- tests for hash.c 
0;10;1c * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Tue Jan 31 00:22:58 2023 (-0500)
 * Version: 1.0
 * 
 * Description: tests for hash apply function
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void increase_age(void* data){
	dog_t* curr_dog = data;
	curr_dog->age = curr_dog->age + 1;
}

int main(void){
	lhashtable_t* lh1 = lhopen(20);
	dog_t *sparky = make_dog(4, "sparky", "border collie", 1);
	dog_t *rose = make_dog(2.5, "rose", "golden retriever", 0);
	dog_t *misty = make_dog(10, "misty", "poodle", 0);

	int32_t res1 = lhput(lh1, (void*)sparky, sparky->name, strlen(sparky->name));
	int32_t res2 = lhput(lh1, (void*)rose, rose->name, strlen(rose->name));
	int32_t res3 = lhput(lh1, (void*)misty, misty->name, strlen(misty->name));

	if ((res1 + res2 + res3) != 0){
		printf("Did not put successfully\n");
		return 1;
	}
	
	lhapply(lh1, increase_age);
	

	if (sparky->age != 5 || rose->age != 3.5 || misty->age != 11){
		printf("Fail: did not properly apply function\n");
		return 1;
	}
	
	lhclose(lh1);
	free(sparky);
	free(rose);
	free(misty);

	return 0;
}
