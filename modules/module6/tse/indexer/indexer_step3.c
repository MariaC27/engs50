/* indexer.c --- 
 * 
 * 
 * Author: Miles B. Hudgins
 * Created: Mon Feb 13 13:30:02 2023 (-0500)
 * Version: 1.0
 * 
 * Description: 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <webpage.h>
#include <pageio.h>
#include <ctype.h>
#include <hash.h>
#include <queue.h>


static int word_total;

typedef struct wordcount{
	char *word_data;
	int count;
}wordcount_t;

bool wordsearch(void* elementp, const void* searchkeyp){
	wordcount_t* word_element = elementp;
	if(!strcmp(word_element->word_data, searchkeyp)) 
		return true;
	return false;
}

void increase_wordcount(wordcount_t *word){ // function to increase word count per iteration
	word->count++;
}

void increase_word_total(void *ep){ // apply to all functions to get total count of all word iterations
	wordcount_t *temp = ep;
	word_total += temp->count;
}

void del_hash_word(void* data){ // this function tries to free up word_data pointer and tmp for every element
	wordcount_t *tmp = data;
	free(tmp->word_data);
	free(tmp);
}

static int normalize_word(char *word){
	if (!(strlen(word) <= 2)){
		for(int i =0; i < strlen(word); i ++){
			char curr = word[i];
			if(!isalpha(curr))
				return 1;
			word[i]=tolower(curr);
		}
		return 0;
	}
	return 1;
}

int main(void){
	
	hashtable_t *h1 = hopen(1000);
	webpage_t* page1 = pageload(1, "../pages/");

	char *path = "./testout.txt";
	FILE *out;
	if((out = fopen(path, "w")) == NULL){printf("Could not open file.\n"); exit(EXIT_FAILURE);}

	int pos = 0;
	char *word;
	while((pos = webpage_getNextWord(page1, pos, &word)) > 0){

		if(normalize_word(word)==0){ // Normalize word here
			wordcount_t *found_word = hsearch(h1, wordsearch, (void *)word, strlen(word)); // hash search
			
			fprintf(out, "%s\n", word); // print to file

			if(found_word == NULL){
				wordcount_t *tmp = (wordcount_t *)malloc(sizeof(wordcount_t)); // malloc struct
				tmp->word_data = malloc(strlen(word)+1);                       // malloc string
				strcpy(tmp->word_data, word);
				tmp->count = 1;
				hput(h1, (void *)tmp, (void *)word, strlen(word));				
			}
			else{
				found_word->count++; // if duplicate -->> increase word count
			}
	  }
		free(word); // free second pointer from webpage.c
	}
	
	word_total = 0;
	happly(h1, increase_word_total); // calculate sum of word iterations
	printf("Sum word count after hash: %i\n", word_total);

	happly(h1, del_hash_word);
	webpage_delete(page1);
	hclose(h1);
 	fclose(out);
	
	exit(EXIT_SUCCESS);
}
