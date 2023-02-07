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

typedef struct weburl {
  char *url;                               // url of the page
  char *html;                              // html code of the page
  size_t html_len;                         // length of html code
  int depth;                               // depth of crawl
} weburl_t;

void print_webpage(void* data){
  weburl_t* site = data;
  printf("URL: %s\n", site->url);
}
void del_res(void* data){
	weburl_t* site = data;
	free(site->url);
}
bool search_url(void* elementp, const void* searchkeyp){
	weburl_t* web = elementp;
	if (!strcmp(web->url, searchkeyp))
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
		//char *html = webpage_getHTML(page);
			
		// Find all URLS and print whether they are internal or external

		pagesave(page, 1, "../pages/");
		
		struct queue_t* qp = qopen();
		hashtable_t* h1 = hopen(10);
		
		
		int pos = 0;
		int counter = 0;
		char *result;
		printf("\nBefore Queue:\n");
		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){
			printf("Found url: %s", result);
			if(IsInternalURL(result)){
				weburl_t* tmp = malloc(sizeof(weburl_t));
				printf(" - INTERNAL\n");
 				tmp->url = result;

				if (!hsearch(h1, search_url, (const void*)result, strlen(result))){ 
					hput(h1, (void *)tmp, tmp->url, strlen(tmp->url));
					qput(qp, (void *)tmp);				
				}
				counter++;
			}
			else{
				printf(" - EXTERNAL\n");
				free(result);
			}
			
		}
		printf("\nAfter Queue:\n");
		qapply(qp, print_webpage);
		
		qapply(qp, del_res);
		qclose(qp);

		webpage_delete(page);
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Unable to fetch page successfully\n");
		exit(EXIT_FAILURE);
  }
	
}
