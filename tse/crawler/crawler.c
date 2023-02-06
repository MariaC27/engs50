/* crawler.c --- code for crawler
 * 
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

int main(void){
	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);
	if(webpage_fetch(page)){
		char *html = webpage_getHTML(page);
		printf("Found html\n");
		
		// find all URLS and print whether they are internal or external
		int pos = 0;
		char *result;
		while ((pos = webpage_getNextURL(page, pos, &result)) > 0){
			printf("Found url: %s", result);
			if(IsInternalURL(result)){
				printf(" - INTERNAL\n");
			}
			else{
				printf(" - EXTERNAL\n");
			}
			free(result);
		}
		
		free(html);
		webpage_delete(page);
		exit(EXIT_SUCCESS);
		return 0;
	}
	else{
		printf("Unable to fetch page successfully\n");
		exit(EXIT_FAILURE);
		return 1;
  }
	
}
