/* query.c --- prompt to get query from user
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Mon Feb 20 13:52:01 2023 (-0500)
 * Version: 1.0
 * 
 * Description: prompt to get query from user
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// funtion to remove spaces and tabs from string
char *strip_extra_spaces(char* str) {
  int i, x;
  for(i=x=0; str[i]; ++i)
    if( !isspace(str[i]) || (i > 0 && !isspace(str[i-1])) ){
			if (str[i] == '\t'){
				str[x] = ' ';
			}
			else {
				str[x] = str[i];
			}
			x++;
		}
  str[x-1] = '\0';
	return str;
}

// function to check that all chars in string are alphanumeric and lowers all letters
bool allalpha(char *str){
  for(int i = 0; str[i]; i++){
    if(!isalpha(str[i])){
      return false;
    }
		str[i] = tolower(str[i]);
	}
	return true;
}


int main(void){

	char str[100];
	char *token;
	const char s[4] = " ";
	char *words_array[20];
	int counter = 0;
	
	while (true){
		
		counter = 0;
		printf("\n>");
		
		if (fgets(str, sizeof(str), stdin) == NULL){  break; } // always checks if there is a ctrl-D

		strip_extra_spaces(str); // remove extra spaces & tabs		

		for (token=strtok(str, s); token!=0; token = strtok(0, s)) {
			if (allalpha(token)){
				words_array[counter] = token;
				counter++;
			}
			else{
				printf("invalid query\n");
				return 1;
			}
		}
		
		for (int i = 0; i < counter; i++){ // for loop to print all elements
			printf("%s ", words_array[i]);
			str[i] = '\0'; //clearing the array at the end
		}
	}
	return 0;
}
