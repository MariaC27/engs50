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
#define _GNU_SOURCE
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

wordcount_t *new_wordcount(char *some_word){                                                                                                                
  wordcount_t *w = malloc(sizeof(wordcount_t));                                                                                                             
  w->word_data = malloc(strlen(some_word)+1);                                                                                                               
  strcpy(w->word_data, some_word);                                                                                                                          
  w->q = qopen();                                                                                                                                           
  return w;                                                                                                                                                 
}                                                                                                                                                           
                                                                                                                                                            
//MALLOC a new entry, specify values, place it into the queue - assumes queue is already open                                                               
int put_entry(queue_t *queue_toput, int eyedee, int cnt){
  qentry_t *entry = malloc(sizeof(qentry_t));                                                                                                               
  entry->id = eyedee;                                                                                                                                       
  entry->count = cnt;                                                                                                                                       
  int result = qput(queue_toput, (void*)entry);                                                                                                             
  return result;                                                                                                                                            
}

// take a hash table (index) as argument and write info to file
int32_t indexsave(hashtable_t *h1, char *filepath){
	/* one line for each word in the index
		 each line has word to start, then doc ID + count repeated on line
		 name of file: indexnm
		 return 0 or 1 based on success*/
	
	if((fp = fopen(filepath, "w")) == NULL){ printf("Could not open file\n"); return 1;}

	//use apply - for all words in hash,  write word and doc + counts to line
	happly(h1, get_word_data);
	fclose(fp);
	return 0;
}


// load info from file and back into hash table (index)
hashtable_t* indexload(char *filepath){

	if((fp = fopen(filepath, "r")) == NULL){ printf("Could not open file\n"); return NULL;}
	
	char line[1000];

	hashtable_t *h1 = hopen(1000); // open HASH table
 
	for(char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)){ // iterate through all lines
		int counter = 0;
		for (; ch != '\n'; ch = fgetc(fp), counter++){ // iterate through one line
			line[counter] = ch;
		}                                                                                                                                                         
		line[counter] = '\0'; // clear memory after word in char *line
		
		char *token;
		char *token2;
		const char s[4] = " ";
		
		token = strtok(line, s); // gets first word
		char *word_name = token;
		int doc_id;
		int count;
		
		wordcount_t *word_struct = new_wordcount(word_name); // struct for HASH table
		
		while ( (token = strtok(0, s)) != 0){ // go through pairs of doc_id and count and enter into queue
			token2 = strtok(0, s);
			
			sscanf(token, "%d", &doc_id); // converts str to int
			sscanf(token2, "%d", &count);
			
			put_entry(word_struct->q, doc_id, count); // creates struct for QUEUE
			//			printf("doc_id_ .h: %i\n", doc_id);
		}
		
		hput(h1, (void *)word_struct, (void *)word_name, strlen(word_name));
	}
	
	fclose(fp);
	return h1;
}
