/* test1_hash.c --- hash test number 1 - open, put, close
 * 
 * 
 * Author: Miles B. Hudgins
 * Created: Sun Jan 29 15:22:51 2023 (-0500)
 * Version: 
 * 
 * Description: Test file to test the functionality of a hashtable
 * 
 */

typedef struct dog{
	double age;
	char *name;
	char *breed;
	int *gender; //0 for female, 1 for male
}dog_t


int main(void){
	hashtable *h1 = hopen(10);
	dog_t sparky  = {4, "sparky", "border collie", 1};
	dog_t rose = {2.5, "rose", "golden retriever", 0};
	
	hput(h1, (void*)sparky);
}
