/* crawler.c --- code for crawler
0;136;0c0;136;0c * 
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

typedef struct webpage {
  char *url;                               // url of the page
  char *html;                              // html code of the page
  size_t html_len;                         // length of html code
  int depth;                               // depth of crawl
} webpage_t;

void print_webpage(void* data){
	webpage_t* page = data;
	printf("URL: %s\n", page->url);
}

int main(void){
	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);

	if(webpage_fetch(page)){
		char *html = webpage_getHTML(page);
		printf("Found html\n");
		printf("Found URLS:\n");
		
		// find all URLS and print whether they are internal or external
		int pos = 0;
		char *result;

		
		struct queue_t* qp = qopen();

		
		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){
			webpage_t* tmp = malloc(sizeof(webpage_t));
			printf("Found url: %s", result);

			if(IsInternalURL(result)){
				printf(" - INTERNAL\n");
				tmp->url =  result;
				qput(qp, (void *)tmp);
				

			}
			else{
				printf(" - EXTERNAL\n");
			}
		}
		printf("\nQueue Returns:\n");
		qapply(qp, print_webpage);

		qclose(qp);
		free(result);
		webpage_delete(page);
		//free(tmp);
		
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Unable to fetch page successfully\n");
		exit(EXIT_FAILURE);
		}
}
