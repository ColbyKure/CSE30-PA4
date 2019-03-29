/*
 * Filename: evenOddHash.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: holds the evenOddHash function.
 * Date: May 26 2018
 * Sources of Help: piazza, pa3 write-up
 */

#include <stdio.h>
#include <string.h>

#include "pa4.h"

#define EVERY_OTHER 2

/*
 * Function Name: evenOddHash()
 * Function Prototype: int evenOddHash(char * str);
 * Description: This function hashes the string from even then odd indicies
 * Parameters: 
 *  str - arg 1 - str to hash 
 * Side Effects: none
 * Error Conditions: none
 * Return Value: hash value of str
 */

int evenOddHash(char * str) {
  int hash = HASH_START_VAL; //init at start val
  if(str == NULL) {
    return hash;
  }
  int strLen = strlen(str);
  for(int i = 0; i < strLen; i += EVERY_OTHER) { //first even indicies
    hash = hash * HASH_PRIME + str[i];
  }
  for(int i = 1; i < strLen; i += EVERY_OTHER) { //then odd indicies
    hash = hash * HASH_PRIME + str[i];
  }
  return hash;
}
