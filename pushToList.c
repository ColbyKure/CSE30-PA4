/*
 * Filename: pushToList.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: File holds the pushToList function
 * Date: May 26 2018
 * Sources of Help: piazza, discussion notes
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: pushToList()
 * Function Prototype: void pushToList(void ** head, char * str);
 * Description: This function will take in a str and a pointer to a LinkedList
 *  head. Then it will allocate new memory on the heap for them and make it the
 *  new head of the LinkedList passed in. 
 * Parameters: 
 *  head - arg 1 - pointer to head of LinkedList
 *  str - arg 2 - string to push
 * Side Effects: error is printed to stderr in case of error
 * Error Conditions: error dynamically allocating memory
 * Return Value: none
 */

void pushToList(void ** head, char * str) {
  //malloc memory for newHead
  linkedList_t * newHead = malloc(sizeof(linkedList_t));
  if(newHead == NULL) {
    perror(MEM_ERR);
  }
  //calloc memory for value
  int  strLen = strlen(str);
  strLen++; // add 1 for null char
  newHead->value = calloc(strLen, sizeof(char));
  if(newHead->value == NULL) {
    perror(MEM_ERR);
  }

  //set members of newHead
  strncpy(newHead->value, str, strLen);
  if(*head == NULL) { //first element in bucket
    newHead->next = NULL;
    *head = newHead;
  }
  else {
    newHead->next = *head;
    *head = newHead;
  }
  return;
}
