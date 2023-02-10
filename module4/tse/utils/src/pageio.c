/* pageio.c --- module implementation of pageio.h
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Thu Feb  9 19:59:42 2023 (-0500)
 * Version: 
 * 
 * Description: pagesave and pageload functions
 * 
 */

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
