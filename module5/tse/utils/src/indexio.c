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
#include "hash.h"
#include "queue.h"
#include "indexio.h"

static FILE *fp;

void print_queue_line(void* data){
	qentry_t* q = data;

	fprintf(fp, "%d ", q->id);
	fprintf(fp, "%d ", q->count);
}

void get_word_data(void* data){ // get doc and counts
	wordcount_t *tmp = data;
	fprintf(fp, "%s ", tmp->word_data);
	
	qapply(tmp->q, print_queue_line);
	
	fprintf(fp, "%s\n", " ");	
}

// take a hash table (index) as argument and write info to file
int32_t indexsave(hashtable_t *h1){
	// one line for each word in the index
	// each line has word to start, then doc ID + count repeated on line
	// name of file: indexnm
	// return 0 or 1 based on success
 
	if((fp = fopen("./indexnm", "w")) == NULL){ printf("Could not open file\n"); exit(EXIT_FAILURE);}

	//use apply - for all words in hash,  write word and doc + counts to line
	happly(h1, get_word_data);

	printf("helo\n");
	fclose(fp);
	return 0;
}



// load info from file and back into hash table (index)
/*hashtable_t* indexload(void){
	return NULL;
	}*/
