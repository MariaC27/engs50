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
#include <hash.h>
#include <queue.h>
#include <pageio.h>
#include <indexio.h>

static int word_total;



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


int main(int argc, char *argv[]){ //takes an argument from the command line
	word_total = 0;
	if(argc !=3){
		printf("Usage: indexer <pagedir> <indexnm>\n");
		exit(EXIT_FAILURE);
	}
	
 	// Prepare newdir
	char* pagedir = argv[1];
	char* filename = argv[2];
	char* save_path = "./";
	
	char *newdir = malloc(strlen(filename)+strlen(save_path)+1);
  strcpy(newdir, save_path);
	strcat(newdir, filename);
	
	// Check if directory exists
	DIR *d;
	struct dirent *dir;
	d = opendir(pagedir);
	if (!d){ printf("Failed to access directory"); exit(EXIT_FAILURE);}	
	
	int doc_id = -1;
	hashtable_t *h1 = hopen(1000);
	webpage_t* page;

	while ((dir = readdir(d)) != NULL) {
	//for(int i = 0; i <4; i++){
	//sscanf(dir->d_name, "%d", &doc_id); // this could be used to pull the file name directly
		if ( doc_id > 0){
			//printf("document id: %i\n", doc_id);
			page = pageload(doc_id, "../pages/");
			
			int pos = 0;
			char *word;
			while((pos = webpage_getNextWord(page, pos, &word)) > 0){
				if(normalize_word(word)==0){ // Normalize word here
					wordcount_t *found_word = hsearch(h1, wordsearch, (void *)word, strlen(word)); // hash search
					// printf("%s\n", word); // prints words on screen
					if(found_word == NULL){//NOT FOUND IN HASH TABLE
						wordcount_t *tmp = new_wordcount(word); // create new hash struct (2 mallocs: 1 struct, 1 char *)
						put_entry(tmp->q, doc_id, 1);
						hput(h1, (void *)tmp, (void *)word, strlen(word));//put tmp into the has table
					}
					else{//FOUND IN HASH TABLE
						qentry_t *found_entry = qsearch(found_word->q, docsearch, &doc_id);
						if(found_entry != NULL){//entry already exists
							found_entry->count++;//increase its count
						}
						else{//entry does not yet exist
							put_entry(found_word->q, doc_id, 1);//malloc new entry, count 1 and put it in the queue associated with word
						}
					}
				}
				free(word); // free second pointer from webpage.c
			}
			webpage_delete(page);
		}
		doc_id++;
	}
	happly(h1, hsumwords);//sum the words frfr
	printf("Sum word count after hash: %i\n", word_total);
	
	//happly(h1, h_words);
		
	indexsave(h1, newdir);

	happly(h1, close_wordcount);
	happly(h1, del_hash_word);
	hclose(h1);

	free(newdir);
	closedir(d);
	
	exit(EXIT_SUCCESS);
}
