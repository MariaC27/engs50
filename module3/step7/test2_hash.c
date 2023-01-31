/* test2_hash.c --- 
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Tue Jan 31 00:22:58 2023 (-0500)
 * Version: 1.0
 * 
 * Description: tests for hash 
 * 
 */

//tests for apply

typedef struct dog{
	double age;
	char *name;
	char *breed;
	int *gender;
}dog_t

void increase_age(void* data){
	dog_t* curr_dog = data;
	curr_dog->age = curr_dog->age + 1;
}

int main(void){
	hashtable *h1 = hopen(10)
	dog_t sparky = {4, "sparky", "border collie", 1};
	dog_t rose = {2.5, "rose", "golden retriever", 0};
	dog_t misty = {10, "misty", "poodle", 0};

	hput(h1, (void*)sparky);
	hput(h1, (void*)rose);
	hput(h1, (void*)misty);

	happly(h1, increase_age);

	if (sparky->age != 5 || rose->age != 3.5 || misty->age != 11){
		printf("Fail: did not properly apply function\n");
	}
}
