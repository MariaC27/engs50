/* indexer5.c --- 
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
#include <ctype.h>
#include <dirent.h> 
#include <webpage.h>
#include "lhash.h"
#include <queue.h>
#include <pageio.h>
#include <indexio.h>
#include <pthread.h>

pthread_mutex_t m2; 

static int word_total;
static int doc_id;
static int dir_count;

//takes in a wordcount structure and closes the queue stored inside of it. used for happly()!!!!!
void close_wordcount(void *w){
	wordcount_t *wc = w;
	qapply(wc->q, free);
	qclose(wc->q);
}

// checks if document ID is already in that entry (where entry in queue)		
bool docsearch(void* entry, const void *keyp){
	qentry_t *e = entry;

	if(e->id == *(int *)keyp)
		return true;//if equal
	return false;//if not equal
}

char *wordcount_getWordData(wordcount_t *w){return w ? w->word_data   : NULL; }

//search function for hsearch
bool wordsearch(void* elementp, const void* searchkeyp){
	wordcount_t* word_element = elementp;
	if(!strcmp(word_element->word_data, searchkeyp)) 
		return true;
	return false;
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

//for qapply
void qsumwords(void *d){
  qentry_t *entry = d;
  if(entry != NULL)
    word_total += entry->count;
} 

//for happly
void hsumwords(void *w){
	wordcount_t *wc = w;
	if(wc != NULL)
		qapply(wc->q, qsumwords);
}

void h_words(void *w){
	wordcount_t *wc = w;
	word_total = 0;
	if (wc != NULL){
		printf("%s - ",wc->word_data);
		qapply(wc->q, qsumwords);
		printf("%i\n", word_total);
	}
}

void *tindexer(void *h){
	hashtable_t *h1 = h;
	webpage_t* page;
	//for (int i=0; i < dir_count; i++){
	while(doc_id < dir_count){
		
		pthread_mutex_lock(&m2);
		int id = doc_id;
		doc_id++;
		pthread_mutex_unlock(&m2);
		
		if ( id > 0){
			//sscanf(dir->d_name, "%d", &doc_id); // this could be used to pull the file name directly
			
			//printf("document id: %i\n", id);
			page = pageload(id, "../pages/");
			
			int pos = 0;
			char *word;
			
			while((pos = webpage_getNextWord(page, pos, &word)) > 0){
				if(normalize_word(word)==0){ // Normalize word here
					wordcount_t *found_word = lhsearch(h1, wordsearch, (void *)word, strlen(word)); // hash search
					// printf("%s\n", word); // prints words on screen
					if(found_word == NULL){//NOT FOUND IN HASH TABLE
						wordcount_t *tmp = new_wordcount(word); // create new hash struct (2 mallocs: 1 struct, 1 char *)
						put_entry(tmp->q, id, 1);
						lhput(h1, (void *)tmp, (void *)word, strlen(word));//put tmp into the has table
					}
					else{//FOUND IN HASH TABLE
						qentry_t *found_entry =  qsearch(found_word->q, docsearch, &id);
						if(found_entry != NULL){//entry already exists
							found_entry->count++;//increase its count
						}
						else{//entry does not yet exist
							put_entry(found_word->q, id, 1);//malloc new entry, count 1 and put it in the queue associated with word
						}
					}
				}
				free(word); // free second pointer from webpage.c
			}
			webpage_delete(page);
		}
	}
	return NULL;
}


int main(int argc, char *argv[]){ //takes an argument from the command line
	word_total = 0;
	if(argc != 4){
		printf("Usage: tindexer <pagedir> <indexnm> <threads>\n");
		exit(EXIT_FAILURE);
	}
	
 	// Prepare newdir
	char* pagedir = argv[1];
	char* filename = argv[2];
	char* save_path = "./";
	
	// Page Directory
	char *newdir = malloc(strlen(filename)+strlen(save_path)+1);
  strcpy(newdir, save_path);
	strcat(newdir, filename);

	// Input Thread Count
	char* input_str = argv[3];
	int input;
	sscanf(input_str, "%d", &input);
	
	// Check if directory exists
	DIR *d;
	struct dirent *dir;
	d = opendir(pagedir);
	if (!d){ printf("Failed to access directory"); exit(EXIT_FAILURE);}	
	
	doc_id = -1;
	hashtable_t *h1 = lhopen(1000);


	// Get size of directory
	dir_count = 0;
	for (int i=0; (dir = readdir(d)) != NULL; i++){
		dir_count = i;
	}
	
 

	// Allocate array for pthreads
	pthread_t array[input];
	pthread_mutex_init(&m2, NULL);

	for (int i=0; i<input; i++){                                                                                                                                         
		if (pthread_create(&array[i], NULL, tindexer, (void *)h1)!=0)                                                                                            
			 exit(EXIT_FAILURE);                                                                                                                                            
	}
	for (int i=0; i<input; i++){                                                                                                                                         
		 if (pthread_join(array[i],NULL)!=0)                                                                                                                               
			 exit(EXIT_FAILURE);                                                                                                                                            
	}
	pthread_mutex_destroy(&m2); 

	lhapply(h1, hsumwords);//sum the words frfr
	printf("Sum word count after hash: %i\n", word_total);
	 
	//happly(h1, h_words);
		
	indexsave(h1, newdir);

	lhapply(h1, close_wordcount);
	lhapply(h1, del_hash_word);
	lhclose(h1);

	free(newdir);
	closedir(d);
	
	exit(EXIT_SUCCESS);
}
