/* indexio.c --- index save and load functions
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Wed Feb 15 15:20:01 2023 (-0500)
 * Version: 1.0
 * 
 * Description: index save and load functions 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <hash.h>

int main(void){
	printf("Hello\n");
}

void get_word_data(void *w){
	wordcount_t *theword = w;
	// get doc and counts
}

// take a hash table (index) as argument and write info to file
int indexsave(hastable_t *h1){
	// one line for each word in the index
	// each line has word to start, then doc ID + count repeated on line
	// name of file: indexnm
	// return 0 or 1 based on success

	FILE *fp = fopen("indexnm", "w");

	if (fp == NULL){
		printf("Could not open file\n");
		return 1;
  }

	//use apply - for all words in hash,  write word and doc + counts to line
}



// load info from file and back into hash table (index)
hastable_t* indexload(void){
}
