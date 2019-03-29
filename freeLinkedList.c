/*
 * Filename: freeLinkedList.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the freeLinkedList function
 * Date: Jun 02 2018
 * Sources of Help: piazza, discussion notes
 */

#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: freeLinkedList()
 * Function Prototype: void freeLinkedList(linkedList_t * head)
 * Description: Frees everything in whole linkedList
 * Parameters: 
 *  head - linkedList_t * - head of linkedList
 * Side Effects: frees all dynamically alloced memory in LinkedList
 * Error Conditions: none
 * Return Value: none
 */

void freeLinkedList( linkedList_t * head ) {
  //handle base case: length 2
  if(head == NULL) {
    return;
  }

  //handle base case: length 1
  if(head->next == NULL) {
    free(head->value);
    free(head);
    return;
  }

  //handle base case: length 2
  linkedList_t * ptr = head;
  linkedList_t * tail;
  int finish = 1;
  while(finish) {
    while(ptr->next->next != NULL) {
      ptr = ptr->next;
    }
    //ptr_>next->next == NULL
    tail = ptr; //set temporary
    ptr = ptr->next; //increment so ptr->next is NULL
    free(ptr->value); //free value first 
    free(ptr); //then the linkedList itself

    tail->next = NULL; //set new endpoint
    ptr = head; //reset ptr to head 
    if(head->next == NULL) {
      free(head->value);
      free(head);
      finish = 0;
    }
  }
  return;
}
