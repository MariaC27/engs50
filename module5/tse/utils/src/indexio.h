/* indexio.h --- for indexio.c
 * 
 * 
 * Author: Maria H. Cristoforo
 * Created: Wed Feb 15 19:00:58 2023 (-0500)
 * Version: 1.0
 * 
 * Description: indexsave and indexload functions 
 * 
 */



typedef struct wordcount{                                                                                                                                                                     
  char *word_data;                                                                                                                                                                            
  queue_t *q;                                                                                                                                                                                 
}wordcount_t;                                                                                                                                                                                 
                                                                                                                                                                                              
typedef struct qentry{                                                                                                                                                                        
  int id;                                                                                                                                                                                     
  int count;                                                                                                                                                                                  
}qentry_t;  

/*
	indexsave -- takes an index (hashtable) with info about words and writes to a file which has one line for each word in the index.
	             Each line has the format: <word> <docID1> <count1> <docID2> <count2> ....<docIDN> <countN>
							 Note: saves the file into the current directory with the name "indexnm"

 */

int32_t indexsave(hashtable_t *h1);




/*

	indexload -- takes a file of the format listed above and loads the content into an index (hashtable)
	             Assumes the file is in the current directory and named "indexnm"

 */

//hashtable_t* indexload(void);
