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
char * removeSpacesFromStr(char *string){
    int non_space_count = 0;
 
    for (int i = 0; string[i] != '\0'; i++){
			if (string[i] != ' ' && string[i] != '\t'){ //not str or tab
				string[non_space_count] = string[i];
        non_space_count++;
      }    
    }
    string[non_space_count] = '\0';
    return string;
}


// function to check that all chars in string are alphanumeric
bool allalpha(char *str){
  for(int i = 0, n = strlen(str)-1; i < n; i++){
    if(!isalpha(str[i])){
      return false;
    }
	}
	return true;
}


int main(void){
	
	while (true){
		char str[100];
		printf(">");
		
		if (fgets(str, sizeof(str), stdin) == NULL){ //always checks if there is a ctrl-D
			break;
		}

						
		if (allalpha(removeSpacesFromStr(str))){
			for(int i = 0; str[i]; i++){ str[i] = tolower(str[i]); }
			printf("%s", removeSpacesFromStr(str));
		}
		else{
			printf("invalid query\n");
		}
		str[0] = '\0'; //clearing the array at the end
	}
	
	return 0;
}
