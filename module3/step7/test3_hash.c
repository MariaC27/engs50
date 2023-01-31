/* test3_hash.c --- 
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Tue Jan 31 01:14:53 2023 (-0500)
 * Version: 1.0
 * 
 * Description: test search function for hash 
 * 
 */

typedef struct dog{
	double age;
	char *name;
	char *breed;
	int *gender;
}dog_t


bool search_hash(void* data, const void* key){
	dog_t* dog1 = data;

	if (!strcmp(dog1->name, key)){
		return true;
	} return false;
}

int main(void){
	hashtable *h1 = hopen(10);
	dog_t sparky = {4, "sparky", "border collie", 1};
	dog_t rose = {2.5, "rose", "golden retriever", 0};
	dog_t misty = {10, "misty", "poodle", 0};

	hput(h1, (void*)sparky);
	hput(h1, (void*)rose);
	hput(h1, (void*)misty);

	// testing for search

	const void* fake_key = "teddy";
	const void* key1 = "rose";

	hsearch(h1, search_hash, fake_key); // TO DO: check if null & corresponding logic
}
