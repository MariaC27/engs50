/* pagio_test.c --- 
0;136;0c *  
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



int main(void ){
	
	webpage_t *tmp = pageload(1, "../pages/");
	//char *x = webpage_getURL(tmp);
	//printf("%s\n", x);

	pagesave(tmp, 50, "../pages/");

	webpage_t *tmp2 = pageload(50, "../pages/");

	int res = 1;
	
	if (strcmp(webpage_getURL(tmp), webpage_getURL(tmp2)) != 0){
		  res = 0;
			}
	if (webpage_getDepth(tmp) != webpage_getDepth(tmp2)){
			res = 0;
		  }
	/*if (webpage_getHTMLlen(tmp) != webpage_getHTML(tmp2)){
			res = 0;
		  }*/
	printf("%i\n",webpage_getHTMLlen(tmp2));

	webpage_delete(tmp);
	webpage_delete(tmp2);

	if (res == 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
