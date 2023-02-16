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
#include <webpage.h>
#include <pageio.h>
#include <ctype.h>
#include <hash.h>
#include <queue.h>


static int word_total;

//struct stored in hash
typedef struct wordcount{
	char *word_data;
	queue_t *q;
}wordcount_t;

//struct storied in queue - "entry"
typedef struct qentry{
	int id;
	int count;
}qentry_t;

//MALLOC a new wordcount, give it word_data and give it a new queue, return a pointer to the structure
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



//takes in a wordcount structure and closes the queue stored inside of it. used for happly()!!!!!
void close_wordcount_queue(void *w){
	wordcount_t *hehehe = w;
	qclose(hehehe->q);
}

void free_wordcount_queue_data(void *w){
	wordcount_t *wc = w;
	qapply(wc->q, free);
}


// checks if document ID is already in that entry (where entry in queue)		
bool docsearch(void* entry, const void *keyp){
	qentry_t *e = entry;

	if(e->id == *(int*)keyp)
		return true;//if equal
	return false;//if not equal
}


char *wordcount_getWordData(wordcount_t *w){return w ? w->word_data   : NULL; }



//search function for hsearch
bool wordsearch(void* elementp, const void* searchkeyp){
	wordcount_t* word_element = elementp;
	if(strcmp(wordcount_getWordData(word_element), searchkeyp)) 
		return true;
	return false;
}


/*void increase_wordcount(wordcount_t *word){ // function to increase word count per iteration
	word->count++;
	}*/

/*void increase_word_total(void *ep){ // apply to all functions to get total count of all word iterations
	wordcount_t *temp = ep;
	word_total += temp->count;
	}*/

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
	printf("%s\n",wc->word_data);
}


int main(int argc, char *argv[]){ //takes an argument from the command line
	word_total = 0;
	if(argc !=2){
		printf("Usage: indexer <id>\n");
		exit(EXIT_FAILURE);
	}
	
	hashtable_t *h1 = hopen(1000);
	int maxdocument = 0;//number that designates the document id to be loaded
	if(strcmp(argv[1], "0")){
		char **fnptr = NULL;
		maxdocument = strtod(argv[1], fnptr);
		if(maxdocument ==0){
			printf("invalid integer input for document id\n");
			exit(EXIT_FAILURE);
		}
	}
	webpage_t* page;
	for(int doc_id = 1; doc_id <= maxdocument; doc_id++){
	printf("document id: %i\n", doc_id);
		page = pageload(doc_id, "../pages/");
		//char *path = "./testout.txt";
		/*FILE *out;
			if((out = fopen(path, "w")) == NULL){printf("Could not open file."); exit(EXIT_FAILURE);}*/
		int pos = 0;
		char *word;
		while((pos = webpage_getNextWord(page, pos, &word)) > 0){
			if(normalize_word(word)==0){ // Normalize word here
				wordcount_t *found_word = hsearch(h1, wordsearch, (void *)word, strlen(word)); // hash search
				// printf("%s\n", word); // prints words on screen
				if(found_word == NULL){//NOT FOUND IN HASH TABLE
					//char *tempword = malloc(strlen(word+1));
					wordcount_t *tmp = new_wordcount(word);
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
	happly(h1, hsumwords);//sum the words frfr
	printf("Sum word count after hash: %i\n", word_total);

	//	happly(h1, h_words);
	
	happly(h1, free_wordcount_queue_data);
	happly(h1, close_wordcount_queue);
	happly(h1, del_hash_word);
	hclose(h1);
	//fclose(out);
	
	exit(EXIT_SUCCESS);
}
