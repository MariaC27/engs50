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

int main(void){
	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);
	if(webpage_fetch(page)){
		//char *html = webpage_getHTML(page);
			
		// Find all URLS and print whether they are internal or external

		struct queue_t* qp = qopen();

		int pos = 0;
		char *result;
		printf("\nBefore Queue:\n");
		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){
			printf("Found url: %s", result);
			if(IsInternalURL(result)){
				weburl_t* tmp = malloc(sizeof(weburl_t));
				printf(" - INTERNAL\n");
 				tmp->url = result;
				qput(qp, (void *)tmp);
				//free(tmp);
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
