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
#include <hash.h>
#include <queue.h>
#include <indexio.h>
 
static int min_count;
static char *word_match;

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

void print_word_count(void* data){
  qentry_t* q = data;
  printf("%d ", q->count);
	if (q->count < min_count || min_count == -1)
		min_count = q->count;
}                                                                                                                                   
                                                                                                                                    
void print_word(void* data){ // get doc and counts
  wordcount_t *tmp = data;
	if (!strcmp(tmp->word_data, word_match)){
		printf("%s:", tmp->word_data);
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


int main(void){

	char str[4] = "team";
	char *token;
	const char s[4] = " ";
	char *words_array[20];
	int counter = 0;
	

	hashtable_t *h1 = indexload("../indexer/pages0");

	//	while (true){
		
		counter = 0;
		min_count = -1;
		//printf(">");
		
		//if (fgets(str, sizeof(str), stdin) == NULL){ printf("\n"); break; } // always checks if there is a ctrl-D, then breaks

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

		if (!(strlen(str) < 1)){
			for (int i = 0; i < counter; i++){ // for loop to print all words
				
				word_match = words_array[i];
				// need to search hash for word to get word count
				if (hsearch(h1, wordsearch, (void *)words_array[i], strlen(words_array[i]))){ // search hash for word
					happly(h1, print_word); // if present, print count
				}
				else {
					printf("%s:0 ", words_array[i]); // if not present, print count 0
					min_count = 0;
				}
				words_array[i] = '\0'; //clearing the array at the end
			}
			printf("-- %i\n", min_count); // print min count
		}
		str[0] = '\0';
		//}
	
		
	happly(h1, close_wordcount);
  happly(h1, del_hash_word);
	hclose(h1);
	return 0;
}
