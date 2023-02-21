/* query.c --- prompt to get query from user
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Mon Feb 20 13:52:01 2023 (-0500)
 * Version: 1.0
 * 
 * Description: prompt to get query from user
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <webpage.h>
#include <hash.h>
#include <queue.h>
#include <indexio.h>
#include <pageio.h>

#define MAX_WORDS 20


static int min_count;
static char *word_match;


typedef struct doc_words{
  int doc_id;
	int rank;
	//char *word_array[MAX_WORDS];
	//int size; // array size
	webpage_t *page;
} doc_words_t;

int make_doc_struct(queue_t *queue_toput, int id, int mincount, webpage_t *webpage){
	doc_words_t *q = malloc(sizeof(doc_words_t));
  q->doc_id = id;
	q->rank = mincount;
	/*	q->size = array_size;
	for (int i = 0; i < array_size; i++){
		q->word_array[i] = malloc(strlen(array[i]));
		q->word_array[i] = array[i];
		}	*/
	q->page = webpage;
	
	int result = qput(queue_toput, (void*)q);
  return result;
}     

// funtion to remove spaces and tabs from string
char *strip_extra_spaces(char* str) {
  int i, x;
  for(i=x=0; str[i]; ++i)
    if( !isspace(str[i]) || (i > 0 && !isspace(str[i-1])) ){
			if (str[i] == '\t'){
				str[x] = ' ';
			}
			else {
				str[x] = str[i];
			}
			x++;
		}
  str[x-1] = '\0';
	return str;
}

// function to check that all chars in string are alphanumeric and lowers all letters
bool allalpha(char *str){
  for(int i = 0; str[i]; i++){
    if(!isalpha(str[i])){
      return false;
    }
		str[i] = tolower(str[i]);
	}
	return true;
}

bool wordsearch(void* elementp, const void* searchkeyp){
	wordcount_t* word_element = elementp;
	if(!strcmp(word_element->word_data, searchkeyp))
		return true;
	return false;
}    

void print_word_count(void* data){
  qentry_t* q = data;
	//  printf("%d ", q->count);
	if (q->count < min_count || min_count == -1)
		min_count = q->count;
}                                                                                                                                   
                                                                                                                                    
void print_word(void* data){ // get doc and counts
  wordcount_t *tmp = data;
	if (!strcmp(tmp->word_data, word_match)){
		//printf("%s:", tmp->word_data);
		qapply(tmp->q, print_word_count);
	}
}

void close_wordcount(void *w){
	wordcount_t *wc = w;
	qapply(wc->q, free);
	qclose(wc->q);
}	

void del_hash_word(void* data){ // this function tries to free up word_data pointer and tmp for every element
	wordcount_t *tmp = data;
	free(tmp->word_data);
	free(tmp);
}   


void print_queue2(void* data){
  doc_words_t* q = data;
	printf("\nrank:%i doc:%i:%s", q->rank, q->doc_id, webpage_getURL(q->page) );
	/*for (int i = 0; i < q->size; i++){
		printf("%s, ", q->word_array[i]);
		}*/
}


int main(void){

	char str[100];
	char *token;
	const char s[4] = " ";
	char *words_array[MAX_WORDS];
	int counter = 0;
	

	hashtable_t *h1 = indexload("../indexer/step3");
	queue_t *q1 = qopen();
	
	while (true){

		
		counter = 0;
		min_count = -1;
		printf("\n>");
		
		if (fgets(str, sizeof(str), stdin) == NULL){  break; } // always checks if there is a ctrl-D, then breaks

		strip_extra_spaces(str); // remove extra spaces & tabs		

		for (token=strtok(str, s); token!=0; token = strtok(0, s)) {
			if (allalpha(token)){
				words_array[counter] = token;
				counter++;
			}
			else{
				printf("invalid query\n");
				return 1;
			}
		}


		// Output formating per entry

		for (int i = 0; i < counter; i++){ // for loop to print all words
			printf("%s ", words_array[i]);
		}


		// Need to go through every document,and get rank for each




		
		// Let's just practice going through one document:::
		char *words_in_doc[MAX_WORDS];
		int counter2 = 0;

		webpage_t *page = pageload(1, "../pages/");
		
		for (int i = 0; i < counter; i++){

			word_match = words_array[i];
			// need to search hash for word to get word count
			if (hsearch(h1, wordsearch, (void *)words_array[i], strlen(words_array[i]))){ // search hash for word
				
				happly(h1, print_word); // update min_count
				words_in_doc[counter2] = words_array[i];
				counter2++;
			}
			else {
				min_count = 0;
			}
		}

		if (min_count != 0)
			make_doc_struct(q1, 1, min_count, page);

		qapply(q1, print_queue2);
		free(qget(q1));


		str[0] = '\0'; //clearing the array at the end




	}


	
	
	happly(h1, close_wordcount);
  happly(h1, del_hash_word);
	hclose(h1);
	return 0;
}
