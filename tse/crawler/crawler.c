
/* crawler.c --- code for crawler
0;136;0c0;136;0c0;136;0c0;136;0c0;136;0c0;136;0c * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Sun Feb  5 15:56:25 2023 (-0500)
 * Version: 1.1
 * 
 * Description: code for crawler
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webpage.h>
#include <queue.h>
#include <hash.h>
#include <stdbool.h>

void print_webpage(void*  pagep){
	printf("%s\n", webpage_getURL(pagep));
}
void del_q_webpage(void* data){ // this function tries to free up url pointer and page for every element in queue
	webpage_delete(data);
}

bool search_url(void* pagep, const void* searchkeyp){
	webpage_t* site = pagep;
	if (!strcmp(webpage_getURL(site), searchkeyp))
		return true;
	return false;
}

int32_t pagesave(webpage_t *pagep, int id, char *dirname){
	
	
	char *html = webpage_getHTML(pagep); //for testing purposes
	char *url = webpage_getURL(pagep);
	int depth = webpage_getDepth(pagep);
	int len = webpage_getHTMLlen(pagep);

	char new_id[10];
	sprintf(new_id, "%d", id);

	char *ch1 = malloc(strlen(dirname)+2);
	strcpy(ch1, dirname);
	strcat(ch1, new_id);
 
	
	FILE *fp = fopen(ch1, "w"); 

	if (fp == NULL){
		printf("Could not open file\n");
		return 1;
	}
	fprintf(fp, "%s\n", url);
	fprintf(fp, "%d\n", depth);
	fprintf(fp, "%d\n", len);
	fprintf(fp, "%s\n", html);

	free(ch1);
	fclose(fp);
	return 0;
}


void load_queue_and_hashtable(hashtable_t *ht, queue_t *q, webpage_t *page){
	if(webpage_fetch(page)){
		
		int pos = 0;
		char *result;
		printf("\nBefore Queue:\n");

		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){ // Step 2 - Print I/E URLS
			printf("Found url: %s", result);

			if(IsInternalURL(result)){
				printf(" - INTERNAL\n");

			 	if (!hsearch(ht, search_url, (void*)result, strlen(result))){
					webpage_t *tmp = webpage_new(result, webpage_getDepth(page)+1, NULL); // Step 3 - Queue
					qput(q, (void *)tmp);				                 // Step 3 - Queue
 					hput(ht, (void *)tmp, result, strlen(result)); // Step 4 - Hash
			 	}
				free(result);
			}
			else{
				printf(" - EXTERNAL\n");
				free(result);
			}
		}
	}
	else
		printf("could not load page -->%s<--in load_queue_and_hashtable", webpage_getURL(page));
}


int main(int argc, char* argv[]){
	if(argc != 4){
		printf("usage: crawler <seedurl> <pagedir> <maxdepth>");
		return 1;
	}
	
	char *seedurl = argv[1];//"https://thayer.github.io/engs50/";
	char *pagedir = argv[2];//"../pages/";
	int maxdepth = 0;
	if(strcmp(argv[3], "0")){
		char **fnptr = NULL;
		maxdepth = strtod(argv[3], fnptr);
		if(maxdepth == 0){
			printf("invalid integer input for depth");
			return 2;
		}
	}
	
	
	webpage_t* seed = webpage_new(seedurl, 0, NULL);
	if(webpage_fetch(seed)){
		int id = 1;
		pagesave(seed, id, pagedir); // step 5 - Page Save to File
		id++;
		struct queue_t* qp = qopen();
		hashtable_t* h1 = hopen(10);
		load_queue_and_hashtable(h1, qp, seed);
		
		webpage_t *current_page = qget(qp);
		while(current_page != NULL && webpage_getDepth(current_page) <= maxdepth){
			load_queue_and_hashtable(h1, qp, current_page);
			pagesave(current_page, id, pagedir);
			id++;
			current_page = qget(qp);
		}
		printf("\nAfter Queue:\n");
		//	qapply(qp, print_webpage);
			
			qapply(qp, del_q_webpage);
			qclose(qp);
			hclose(h1);
			webpage_delete(seed);
			
			exit(EXIT_SUCCESS);
	}
	else{
			printf("Unable to fetch seed page successfully\n");
			exit(EXIT_FAILURE);
		}	
}
