/* indexer.c --- 
 * 
 * 
 * Author: Maria H. Cristoforo
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

int main(void){
	printf("Hello\n");
	webpage_t* page1 = pageload(1, "../pages/");
	while((pos = webpage_getNextWord(page1, pos, &word) > 0){
			printf("%s\n", word);
			free(word);
	}
}
