/* indexer.c --- 
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

int normalize_word(char *word){
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

int main(void){
	webpage_t* page1 = pageload(1, "../pages/");
	int pos;
	char *word;
	char *path = "./testout.txt";
	FILE *out = fopen(path, "w");
	if(out == NULL){
		printf("Could not open file\n");
		return 1;
		}
	
	while((pos = webpage_getNextWord(page1, pos, &word)) > 0){
		if(normalize_word(word)==0){
			fprintf(out, "%s\n", word); // print to file
			free(word);
		}
	}

	fclose(out);
}
