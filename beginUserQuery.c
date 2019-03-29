/*
 * Filename: beginUserQuery.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This function holds the beginIserQuery function
 * Date: Jun 02 2018
 * Sources of Help: piazza, discussion
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NEWLINE '\n'

/*
 * Function Name: beginUserQuery()
 * Function Prototype: void beginUserQuery(int counts[], table_t * htbl, 
 *  table_t * rtbl, table_t * eotbl, int statsOn);
 * Description: This function handles the user interaction to the search tables
 *  and reports the number of collisions occured as user searches emails
 * Parameters: 
 *  counts[] - int[] - keeps track of collisions
 *  htbl - table_t * - pointer to htbl with void *
 *  rtbl - table_t * - pointer to rtbl with void *
 *  eotbl - table_t * - pointer to eotbl with LinkedLists
 * Side Effects: This function prompts the user through stdout and prints out
 *  the stats and the number of collisions if specified.
 * Error Conditions: none
 * Return Value: none 
 */
int numSearches = 0;

void beginUserQuery(int counts[], table_t * htbl, table_t * rtbl, table_t *
  eotbl, int statsOn) {
  //init variables for fgets
  char email[BUFSIZ];
  char * nlPtr;

  //prompt
  fprintf(stdout, USER_PROMPT);
  while((fgets(email, BUFSIZ-1, stdin)) != NULL) {
    if((int)email == EOF) {
      printf("exiting\n");
      break;
    }
    nlPtr = strchr(email, NEWLINE);
    *nlPtr = '\0'; //repalce newline with NUL char
    if(strlen(email) == 0) {
      //input is empty ("\n"), reprompt 
      fprintf(stdout, USER_PROMPT);
      continue;
    }
    numSearches++;
    //turn input to lower
    for(int i = 0; i < strlen(email); i++) {
      email[i] = tolower(email[i]);
    }
    char * word = email;
    //check if input is in tables
    int ret = checkTables(word, htbl, rtbl, eotbl);
    if(ret == IN_TABLE) {
      fprintf(stdout, FOUND_IN_ALL, email);
    }
    else if(statsOn && ret >= 1) {
      fprintf(stdout, FOUND_IN_SOME, email, ret);
    }
    else{
      //no collisions
      fprintf(stdout, WORD_NOT_FOUND, email);
    }
    //update collision counts[]
    for(int i = ret - 1; i >= 0; i--) {
      (counts[i])++;
    }
    fprintf(stdout, USER_PROMPT);
  }
  printf("\n");
  return;
}
