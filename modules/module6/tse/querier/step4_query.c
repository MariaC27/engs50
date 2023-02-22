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
#include <dirent.h>
#include <webpage.h>                                                                                                              
#include <hash.h>                                                                                                                 
#include <queue.h>                                                                                                                
#include <indexio.h>                                                                                                              
#include <pageio.h> 


#define MAX_WORDS 20


static int min_count;
static char *word_match;
static int id_match;

typedef struct doc_words{
  int doc_id;
	int rank;
	webpage_t *page;
} doc_words_t;

int make_doc_struct(queue_t *queue_toput, int id, int mincount, webpage_t *webpage){
	doc_words_t *q = malloc(sizeof(doc_words_t));
  q->doc_id = id;
	q->rank = mincount;
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



bool consecutive_and_or(char* word1, char* word2){
	if(strcmp(word1, "and") == 0){
    if(strcmp(word2, "and") == 0 || strcmp(word2, "or") == 0){
			return false;
    }
  }
  if (strcmp(word1, "or")==0){
    if(strcmp(word2, "and") == 0 || strcmp(word2, "or") == 0){
			return false;
    }
  }
  return true;
}

bool valid_query_sequence(char* wordsarray[], int len){
	//checks if "and" or "or" are at beginning or end of word sequence
	if ((strcmp(wordsarray[0], "and")==0 || strcmp(wordsarray[0], "or")==0) ||//if word array starts with "and" or "or"
			(strcmp(wordsarray[len-1],"and")==0 || strcmp(wordsarray[len-1], "or")==0)){//if word array ends with "and" or "or"
		return false;
	}
	
	int i;
	// check if "and" or "or" are consecutive anywhere in query
  for (i = 0 ; i < len-1; i++){
		if (!consecutive_and_or(wordsarray[i], wordsarray[i+1])){
			return false;
		}
  }
  return true;
}

// function to check that all chars in string are alphanumeric and lowers all letters
bool allalpha(char *str){
  for(int i = 0; str[i]; i++){
		if (str[i] == '\n' && i==0){
			str[0] = '\0';
			return true;
		}
		else if (!isalpha(str[i])){
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

void close_doc_struct(void *data){
	doc_words_t *q = data;
	webpage_delete(q->page);
}	

void print_queue2(void* data){                                                                                                    
  doc_words_t* q = data;                                                                                                          
  printf("\nrank:%i:doc:%i:%s", q->rank, q->doc_id, webpage_getURL(q->page) );                                                    
}    

void calculate_rank(void* data){
  qentry_t* q = data;
	if ( q->id == id_match ){ // updates min_count (rank) by running through all words with doc #
		if (q->count < min_count || min_count == -1){
			min_count = q->count;
		}	
	}
}                                                                                                                                   

void calculate_rank_hash(void* data){ // get doc and counts
  wordcount_t *tmp = data;
	if (strcmp(tmp->word_data, word_match)==0){
		qapply(tmp->q, calculate_rank);
	}
}

int main(void){
 
	char str[100];
	char *token;
	const char s[4] = " ";
	char *words_array[MAX_WORDS];
	int counter = 0;
	

	hashtable_t *h1 = indexload("../indexer/pages3");
	//	happly(h1, printhash);
	
	while (true){
		
		counter = 0;
		printf(">");
		
		if (fgets(str, sizeof(str), stdin) == NULL){ printf("\n"); break; } // always checks if there is a ctrl-D, then breaks

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

		// OUTPUT formatting to print query
		if (!(strlen(str) < 1)){
			for (int i = 0; i < counter; i++){ // for loop to print all words                                                             
				printf("%s ", words_array[i]);                                                                                              
			} 
		}

		if(valid_query_sequence(words_array, counter)!=true){//if the query sequence is invalid based on the placement of keywords "and" and "or"
			printf("invalid query, \"and\" and \"or\" sequence mishapen\n");
			exit(EXIT_FAILURE);//exit failure
		}
		// Need to go through every document, and get rank for each and put into queue
		// Check if directory exists
		DIR *d;                                                                                                                         
		struct dirent *dir;                                                                                                             
		d = opendir("../pages/");                                                                                                           
		if (!d){ printf("Failed to access directory"); exit(EXIT_FAILURE);}		


		int doc_id = -1;                                                                                                                
		webpage_t* page;                                                                                                                
		queue_t *q1 = qopen();
		int sum_of_ors;
		int min_val_in_and_sequence;
		if (!(strlen(str) < 1)){
			while ((dir = readdir(d)) != NULL) {
				sum_of_ors = 0;
				if ( doc_id > 0){                                                                                                             
					page = pageload(doc_id, "../pages/");
					min_val_in_and_sequence = INT_MAX;
					for (int i = 0; i < counter; i++){ // for loop to print all words
						
						word_match = words_array[i];
						if(strcmp(word_match, "and") == 0)
							continue;
						if(strcmp(word_match, "or") != 0){
							// need to search hash for word to get word count
							if (hsearch(h1, wordsearch, (void *)words_array[i], strlen(words_array[i]))){ // search hash for word
								happly(h1, calculate_rank_hash); // if present, print count, set global variable min_count to the minimum number of occurences of the word in the doc
								if (min_count == -1)
									min_count = 0;
							}
							else {
								min_count = 0;
							}
							if(min_count < min_val_in_and_sequence){
								min_val_in_and_sequence = min_count;
							}
						}
						else{
							sum_of_ors += min_val_in_and_sequence;
							min_val_in_and_sequence = INT_MAX;
						}
					}
					sum_of_ors += min_val_in_and_sequence;
					//make_doc_struct(q1, doc_id, min_count, page);
					make_doc_struct(q1, doc_id, sum_of_ors, page);
				}
				doc_id++;
				min_count = -1;
				id_match = doc_id;
			}
		}
		
		qapply(q1, print_queue2);
		
		if (!(strlen(str) < 1)){
			for (int i = 0; i < counter; i++){ // for loop to print all words                                                             
				words_array[i] = '\0';
			}
			printf("\n");
		}
		str[0] = '\0';

		qapply(q1, close_doc_struct);
		qclose(q1);

		
		/* VALGRIND
DONE	     -->> Need to go through words_array and clear //words_array[i] = '\0'; //clearing the array at the end
Done			 -->> Need to go through queue and free elements //free(qget(q1));
Done			 -->> Need to webpage delete //webpage_delete(page);
		*/
		
		

								 

	}
		
	happly(h1, close_wordcount);
  happly(h1, del_hash_word);
	hclose(h1);
	return 0;
}
