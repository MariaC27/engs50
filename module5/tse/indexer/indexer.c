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
	char word_data[20];
	int count;
}wordcount_t;


static bool wordsearch(void *elementp, const void* searchkeyp){
	wordcount_t *word_element = elementp;
	if(!strcmp(searchkeyp, word_element->word_data))
		return true;
	return false;
}

void increase_wordcount(wordcount_t *word){
	word->count++;
}

void increase_word_total(void *ep){
	wordcount_t *temp = ep;
	word_total += temp->count;
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
	int pos = 0;
	char *word;
	char *path = "./testout.txt";
	FILE *out = fopen(path, "w");
	if(out == NULL){
		printf("Could not open file\n");
		exit(EXIT_FAILURE);
	}


	//wordcount_t *array[141];
	//int counter = 0;
	while((pos = webpage_getNextWord(page1, pos, &word)) > 0){
		if(normalize_word(word)==0){
			wordcount_t *found_word = hsearch(h1, wordsearch, word, strlen(word));
			fprintf(out, "%s\n", word); // print to file
			if(found_word == NULL){
				printf("%s\n", word);
				wordcount_t *tmp = (wordcount_t *)malloc(sizeof(wordcount_t));
				tmp->word_data = 				checkp(malloc(strlen(word)+1), "tmp->word_data");

				//array[counter] = tmp;
				strcpy(tmp->word_data, word);

				tmp->count = 1;
				hput(h1, (void *)tmp, word, strlen(word));				
			}
			else{
				found_word->count++;
			}
	  }
		free(word);
		//counter++;
	}
	
	word_total = 0;

	//happly(h1, increase_word_total);
	printf("\n\n%i\n\n", word_total);
	webpage_delete(page1);
	hclose(h1);
	//for(int i = 0; i < 141; i++){
	//free(array[i]);
	//}
	fclose(out);
	
	exit(EXIT_SUCCESS);
}
