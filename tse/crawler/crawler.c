
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

void print_webpage_url(void*  pagep){
	printf("%s\n", webpage_getURL(pagep));
}
void print_webpage_html(void*  pagep){
	printf("%s\n", webpage_getHTML(pagep));
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

int32_t load_queue_and_hashtable(hashtable_t *ht, queue_t *q, webpage_t *page){

	//webpage_fetch(page); // format html into queue
	int32_t res = 0;
	//&& strstr(webpage_getHTML(page), "404")==NULL)){
	
	if (!(webpage_getDepth(page)==3 && webpage_getHTMLlen(page)==37)){

		int pos = 0;
		char *result;

		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){ // Step 2 - Print I/E URLS
			//printf("Found url: %s", result);
			if(IsInternalURL(result)){
				//printf(" - INTERNAL\n");

			 	if (!hsearch(ht, search_url, (void*)result, strlen(result))){
					
					webpage_t *tmp = webpage_new(result, webpage_getDepth(page)+1, NULL); // Step 3 - Queue

		 
					qput(q, (void *)tmp);				                 // Step 3 - Queue
 					hput(ht, (void *)tmp, (void *)result, strlen(result)); // Step 4 - Hash
			 	}
				free(result);
			}
			else{
				//printf(" - EXTERNAL\n");
				free(result);
			}
		}
	}
	else{
		res = 1;
		//		printf("could not load page -->%s<--in load_queue_and_hashtable", webpage_getURL(page));
	}
	return res;
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
	
	int id = 1;

	struct queue_t* qp = qopen();

	hashtable_t* h1 = hopen(10);
	webpage_t *tmp = webpage_new(seedurl, 0, NULL); // Step 3 - Queue
	qput(qp, (void *)tmp);                        // Step 3 - Queue                                                                                                      
	hput(h1, (void *)tmp, (void *)seedurl, strlen(seedurl)); // Step 4 - Hash               

	
	webpage_t *current_page = qget(qp);
	while(current_page != NULL && webpage_getDepth(current_page) <= maxdepth){
		if (webpage_fetch(current_page)){ // need to fetch once
			int32_t res = load_queue_and_hashtable(h1, qp, current_page);
			if (res==0){
				printf("%i\n",id);
				webpage_fetch(current_page); // need to fetch again ?? to format html to print
				pagesave(current_page, id, pagedir);
				id++;
			}
			current_page = qget(qp);
		}
	}

	//qapply(qp, print_webpage_html);
	
	qapply(qp, del_q_webpage);
	qclose(qp);
	hclose(h1);
	webpage_delete(seed);
	
	exit(EXIT_SUCCESS);
}
