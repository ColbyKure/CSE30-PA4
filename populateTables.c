/*
 * Filename: populateTables.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the populateTables function
 * Date: May 26 2018
 * Sources of Help: piazza, discussion notes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "pa4.h"

#define NEWLINE_CHAR '\n'

/*
 * Function Name: populateTables(0
 * Function Prototype: void populateTables(table_t * htbl, table_t * rtbl,
 *   table_t * eotbl, FILE * dataFile);
 * Description: This function will populate the values of the tables by reading
 *  from the dataFile. 
 * Parameters: 
 *  htbl - arg 1 - first table
 *  rtbl - arg 2 - reverse table
 *  eotbl - arg 3 - even odd table
 *  dataFile - arg 4 - file to read from
 * Side Effects: none
 * Error Conditions: none
 * Return Value: none
 */

void populateTables(table_t * htbl, table_t * rtbl, table_t * eotbl, 
  FILE * dataFile) {

  //read lines 
  char line[BUFSIZ];
  char * newlinePtr; 
  while(fgets(line, BUFSIZ, dataFile) != NULL) {
    //find newline char 
    newlinePtr = strchr(line, NEWLINE_CHAR);
    *newlinePtr = '\0'; //replace newline for null char 
    //whole line tolower
    for(int i = 0; i < strlen(line); i++) { 
      line[i] = tolower(line[i]);
    }
    //calculate hash keys and then normalized  hash indexes
    int regHash = hash(line);
    int revH = revHash(line);
    int EOHash = evenOddHash(line);
    int sizeA = htbl->size;
    regHash = regHash % sizeA;
    regHash = regHash + sizeA;
    regHash = regHash % sizeA;
    revH = revH % sizeA;
    revH = revH + sizeA; 
    revH = revH % sizeA;
    EOHash = EOHash % sizeA;
    EOHash = EOHash + sizeA;
    EOHash = EOHash % sizeA;
    //set value in hash tables
    htbl->tbl[regHash] = (void *)1;
    rtbl->tbl[revH] = (void *)1;
    pushToList((eotbl->tbl + EOHash), line);
  }
}
