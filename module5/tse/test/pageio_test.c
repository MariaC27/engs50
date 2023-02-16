/* pagio_test.c --- 
 * 136;0c *  
 * Author: Justin Sapun
 * Created: Mon Feb 13 13:26:27 2023 (-0500)
 * Version: 
 * 
 * Description: 
 *  
 */


#include <pageio.h>
#include <string.h>
#include <webpage.h>


/*int32_t pagesave(webpage_t *pagep, int id, char *dirname){                                                                
                                                                                                                          
                                                                                                                          
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
                                                                                                                          
webpage_t *pageload(int id, char *dirname){                                                                               
                                                                                                                          
  //get a string of dirname and id                                                                                        
  char new_id[10];                                                                                                        
  sprintf(new_id, "%d", id); //turns id into a string                                                                     
  char *ch1 = malloc(strlen(dirname)+2);                                                                                  
  strcpy(ch1, dirname);                                                                                                   
  strcat(ch1, new_id); //concatenate dir and id together into ch1                                                         
                                                                                                                          
  //open file to read from                                                                                                

	//if((*fp = fopen(ch1, "r")) == NULL){ exit(EXIT_FAILURE);}
	FILE *fp = fopen(ch1, "r");                                                                                             
  if (fp == NULL) {                                                                                                       
    printf("Could not open file\n");                                                                                      
    exit(EXIT_FAILURE);                                                                                                   
  } 

	
  char url[1000];                                                                                                         
	char depth[5];                                                                                                          
  int int_depth;                                                                                                          
	char html_len[10];
	int int_html_len;


	// For URL
	char ch = fgetc(fp);
	int counter = 0;
	for (; ch != '\n'; ch = fgetc(fp), counter++){
		url[counter] = ch;
	}
	url[counter] = '\0';
	
	//fgets(url, 1000, fp);
  fgets(depth, 5, fp);                                                                                                    
  sscanf(depth, "%d", &int_depth); // convert string to int
	fgets(html_len, 10, fp); // gets html_len but we don't put it into new webpage
	sscanf(html_len, "%d", &int_html_len); // convert string to int
	

	char *html = malloc(int_html_len+1);
	
	ch = fgetc(fp);
	counter = 0;
	for (; !feof(fp); ch = fgetc(fp), counter++){
		html[counter] = ch;
	}
	html[int_html_len] = '\0';
	
	
  webpage_t *newpage = webpage_new(url, int_depth, html); // need to copy over html                                       

  free(ch1);
  fclose(fp);
	
  return newpage;                                                                                                         
	}*/


int main(void ){
	
	webpage_t *tmp = pageload(1, "../pages/");
	
	pagesave(tmp, 0, "./"); // Save file to 0
	
	webpage_t *tmp2 = pageload(0, "../pages/"); // Load same file
	 
	int res = 1;

	/* Tests if all components are the same in both the read and loaded files */ // 2 errors
	if (strcmp(webpage_getURL(tmp), webpage_getURL(tmp2)) != 0){ 
		  res = 0;
	}
	if (webpage_getDepth(tmp) != webpage_getDepth(tmp2)){
			res = 0;
	}
	if (webpage_getHTMLlen(tmp) != webpage_getHTMLlen(tmp2)){
			res = 0;
	}
	if (strcmp(webpage_getHTML(tmp), webpage_getHTML(tmp2))){
			res = 0;
			}
	
	webpage_delete(tmp);
	webpage_delete(tmp2);

	if (res == 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
