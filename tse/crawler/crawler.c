
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

int main(void){
	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);
	if(webpage_fetch(page)){
			
		// Find all URLS and print whether they are internal or external

		pagesave(page, 1, "../pages/"); // step 5 - Page Save to File
		
		struct queue_t* qp = qopen();
		hashtable_t* h1 = hopen(10);
		
		int pos = 0;
		char *result;
		printf("\nBefore Queue:\n");

		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){ // Step 2 - Print I/E URLS
			printf("Found url: %s", result);

			if(IsInternalURL(result)){
				printf(" - INTERNAL\n");

			 	if (!hsearch(h1, search_url, (void*)result, strlen(result))){
					webpage_t *tmp = webpage_new(result, 0, NULL); // Step 3 - Queue
					qput(qp, (void *)tmp);				                 // Step 3 - Queue
 					hput(h1, (void *)tmp, result, strlen(result)); // Step 4 - Hash
			 	}
				free(result);
			}
			else{
				printf(" - EXTERNAL\n");
				free(result);
			}
		}
		printf("\nAfter Queue:\n");
		qapply(qp, print_webpage);

		qapply(qp, del_q_webpage);
	  qclose(qp);
		hclose(h1);
		webpage_delete(page);

		exit(EXIT_SUCCESS);
	}
	else{
		printf("Unable to fetch page successfully\n");
		exit(EXIT_FAILURE);
  }	
}
