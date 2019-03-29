/*
 * Filename: writeTables.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the writeTables function
 * Date: May 26 2018
 * Sources of Help: piazza, discussion notes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"

/*
 * Function Name: writeTables()
 * Function Prototype: void writeTables(FILE * outFile, table_t * htbl, 
 *  table_t * rtbl, table_t * eotbl);
 * Description: This function will serialize the tables and write them to the
 *  outFile. 
 * Parameters: 
 *  outFile - arg 1 - file to write to
 *  htbl - arg 2 - table 1 
 *  rtbl - arg 3 - table 2 
 *  eotbl - arg 4 - table 3 
 * Side Effects: writes the serialized contents of tables to outFile
 * Error Conditions: None
 * Return Value: none
 */

void writeTables(FILE * outFile, table_t * htbl, table_t * rtbl, 
  table_t * eotbl) {
  //print size of table  
  fwrite(&(htbl->size), sizeof(int), 1, outFile);

  //fwrite htbl and rtbl 
  fwrite(htbl->tbl, sizeof(void *), htbl->size,  outFile);
  fwrite(rtbl->tbl, sizeof(void *), rtbl->size,  outFile);

  //print eotbl
  linkedList_t * trPtr;
  for(int i = 0; i < eotbl->size; i++) {
    trPtr = (linkedList_t *)eotbl->tbl[i]; //update linkedList traverse pointer 
    if(trPtr == NULL) {
      fputc('\0', outFile);
      continue;
    }
    while(1) { //empty contents of bucket
      char * email = trPtr->value;
      fputs(email, outFile); //print each name
      fputc('\0', outFile); //follewed by the null char
      if(trPtr->next == NULL) {
        break;
      }
      trPtr = trPtr->next;
    }
    fputc('\0', outFile); //end bucket char 
  }
}
