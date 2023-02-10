/* pageio.c --- module implementation of pageio.h
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Thu Feb  9 19:59:42 2023 (-0500)
 * Version: 1.0
 * 
 * Description: implementation of pageio.h: pagesave and pageload functions
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "webpage.h"

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

webpage_t *pageload(int id, char *dirnm){
	
	//get a string of dirname and id
	char new_id[10];
	sprintf(new_id, "%d", id); //turns id into a string
	char *ch1 = malloc(strlen(dirname)+2);
	strcpy(ch1, dirname);
	strcat(ch1, new_id); //concatenate dir and id together into ch1
 
	//open file to read from
	FILE *fp = fopen(ch1, "r");
	if (fp == NULL) {
		printf("Could not open file\n");
		exit(EXIT_FAILURE);
	}

	fgets(url, 1000, fp); //unsure if these are right
	fgets(depth, 5, fp);
	webpage_t *newpage = webpage_new(url, depth, NULL);

	fclose(fp);
	return webpage_t;
}
