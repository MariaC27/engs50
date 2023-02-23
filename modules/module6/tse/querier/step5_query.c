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
static FILE *doc_out; // print file out via qapply

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
	free(q);
}	

void print_queue2(void* data){                                                                                                    
  doc_words_t* q = data;
	if (q->rank > 0)
		printf("\nrank:%i:doc:%i:%s", q->rank, q->doc_id, webpage_getURL(q->page) );                                                    
}    

void queue_to_file(void *data){
	doc_words_t *q = data;
	if (q->rank > 0){
		fprintf(doc_out, "\nrank:%i:doc:%i:%s", q->rank, q->doc_id, webpage_getURL(q->page));
	}
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

int main(int argc, char *argv[]){
	if(argc > 6 || argc < 3){
		printf("Invalid number of arguments. Usage: query <pageDirectory> <indexFile> [-q]\n");
		exit(EXIT_FAILURE);
	}

	char *page_directory = argv[1];
	char *indexFile = argv[2];
	
	FILE *query_readfile;
	char *query_readfile_path;
	char *doc_out_path;
	int q = 1;
	if(argc >3){
		if(strcmp(argv[3], "-q")==0){
			query_readfile_path = argv[4];
			doc_out_path = argv[5];
			query_readfile = fopen(query_readfile_path, "r");
			doc_out = fopen(doc_out_path, "w");
			q = 0;
		}
		else{
			printf("Usage: query <pageDirectory> <indexFile> [-q]\n");
			exit(EXIT_FAILURE);
		}
	}
	
	char str[100];
	char *token;
	const char s[4] = " ";
	char *words_array[MAX_WORDS];
	int counter = 0;
	
	hashtable_t *h1 = indexload(indexFile);

	int end = 1;
	while (end == 1){
		counter = 0;

		if (q==1){
			printf(">");
		}
		
		if(q ==1){
			if (fgets(str, sizeof(str), stdin) == NULL){ printf("\n"); break; } // always checks if there is a ctrl-D, then breaks
		}
		else{
			char ch = fgetc(query_readfile);
			int ctr = 0;
			for (; ch != '\n'; ch = fgetc(query_readfile), ctr++){
				if(ch==EOF){
					end = 0;
					//					ctr++;
					printf("\n");
					break;
				}
				str[ctr] = ch;
			}
			str[ctr] = '\n';
			ctr++;
			str[ctr] = '\0';
		}

			strip_extra_spaces(str); // remove extra spaces & tabs		
			
			for (token=strtok(str, s); token!=0; token = strtok(0, s)) {
				if (allalpha(token)){
					words_array[counter] = token;
					counter++;
				}
				else{
					if (q==1){
						printf("invalid query\n");
					}
					else{
						fprintf(doc_out, "invalid query\n");
					}
					continue;
					//return 1;
				}
			}

		// OUTPUT formatting to print query
		if (!(strlen(str) < 1)){
			if (q!=1)
				fprintf(doc_out, "-->> ");                                                                                              
			for (int i = 0; i < counter; i++){ // for loop to print all words                                                             
				if (q==1){
					printf("%s ", words_array[i]);                                                                                              
				}
				else {
					fprintf(doc_out, "%s ", words_array[i]);                                                                                              
				}
			}
		}

		if(valid_query_sequence(words_array, counter)!=true){//if the query sequence is invalid based on the placement of keywords "and" and "or"
			if (q==1){
				printf("\ninvalid query, \"and\" and \"or\" sequence mishapen\n");
			}
			else{
				fprintf(doc_out, "\ninvalid query, \"and\" and \"or\" sequence mishapen\n");
			}
			continue;
			//exit(EXIT_FAILURE);//exit failure
		}
		// Need to go through every document, and get rank for each and put into queue
		// Check if directory exists
		DIR *d;                                                                                                                         
		struct dirent *dir;                                                                                                             
		//		d = opendir("../pages/");
		d = opendir(page_directory);
		if (!d){ printf("\nFailed to access directory\n"); exit(EXIT_FAILURE);}		


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
						min_count = -1;
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
			// Print error if direc is empty
			if (doc_id == 1){
				printf("\nDirectory has not been crawled");
			}
		}
		
		
		if (q==1){
			qapply(q1, print_queue2);
		}
		else{
			qapply(q1, queue_to_file);
			fprintf(doc_out, "\n");
		}
				
		if (!(strlen(str) < 1)){
			for (int i = 0; i < counter; i++){ // for loop to print all words                                                             
				words_array[i] = '\0';
			}
			printf("\n");
		}
		str[0] = '\0';

		qapply(q1, close_doc_struct);
		qclose(q1);
		closedir(d);

		

	}
	if(q == 0){
		fclose(query_readfile);
		fclose(doc_out);
	}
	happly(h1, close_wordcount);
  happly(h1, del_hash_word);
	hclose(h1);
	return 0;
}
