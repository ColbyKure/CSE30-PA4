/*
 * Filename: checkTables.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the checkTables function
 * Date: Jun 02 2018
 * Sources of Help: piazza, notes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NUM_TABLES 3

/*
 * Function Name: checkTables()
 * Function Prototype: int checkTables(char * str, table_t * htbl, table_t * 
 *  rtbl, table_t * eotbl);
 * Description: This function reports the unmber of tables that str is seen in
 * Parameters: 
 *  str - char * - string to search for
 *  htbl - table_t * - table_t pointer to htbl
 *  rtbl - table_t * - table_t pointer to rtbl
 *  eotbl - table_t * - table_t pointer to eotbl
 * Side Effects: none 
 * Error Conditions: none 
 * Return Value: number of tables str is in 
 */

int checkTables(char * str, table_t * htbl, table_t * rtbl, table_t * eotbl) {

  int count = 0;
  int twiceFlag = 0;
  //use all 3 hash functions on str
  int regHash = hash(str);
  int revH = revHash(str);
  int eoHash = evenOddHash(str);
  //getFromTable on the 3 hashVals
  void * reg = getFromTable(regHash, htbl);
  void * reverse = getFromTable(revH, rtbl);
  linkedList_t * eoHead = getFromTable(eoHash, eotbl);
  //check if in first table 
  if(reg != NULL) {
    count++;
  }
  //if in first check if in second 
  twiceFlag = 0;
  if(reg != NULL && reverse != NULL) {
    count++;
    twiceFlag = 1;
  }
  //if in first 2 check third 
  if(twiceFlag == 1 && eoHead != NULL) {
    count++;
  }
  else {
    return count;
  }
  //if in all 3 check LinkedList
  if(count == NUM_TABLES) {
    if(strcmp(eoHead->value, str) == 0) {
      count++;
      return count;
    }
    //loop through linkedList
    while(eoHead->next != NULL) {
      eoHead = eoHead->next;
      if(strcmp(eoHead->value, str) == 0) {
        count++;
        return count;
      }
    }
  }
  return count;
}
