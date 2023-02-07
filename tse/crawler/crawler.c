/* crawler.c --- code for crawler
0;136;0c0;136;0c0;136;0c0;136;0c * 
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
  weburl_t* page = data;
  printf("URL: %s\n", page->url);
}

int main(void){
	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);
	if(webpage_fetch(page)){
		//char *html = webpage_getHTML(page);
		//printf("Found html\n");
		
		// find all URLS and print whether they are internal or external

		struct queue_t* qp = qopen();


		int pos = 0;
		char *result;
		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){
			weburl_t* tmp = malloc(sizeof(weburl_t));
			printf("Found url: %s", result);
			if(IsInternalURL(result)){
				printf(" - INTERNAL\n");
 				tmp->url = result;
				qput(qp, (void *)tmp);
			}
			else{
				printf(" - EXTERNAL\n");
			}
			//free(result); // valgrind issue here
			//free(tmp);
		}
		qapply(qp, print_webpage);
		//weburl_t* x = (weburl_t *)qget(qp);
		//printf("After\nURL:%s\n",x->url);
		
		qclose(qp);
		webpage_delete(page);
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Unable to fetch page successfully\n");
		exit(EXIT_FAILURE);
  }
	
}
