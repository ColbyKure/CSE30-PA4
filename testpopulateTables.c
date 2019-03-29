/*
 * Filename: populateTables.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function populateTables().
 * Date: 5/58/18
 * Sources of Help: notes, discussion notes, piazza
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

#define NUM_EMAILS 100

/*
 * Unit test for populateTables
 *
 * void populateTables(table_t * htbl, table_t * rtbl, table_t * eotbl, FILE *
 *    dataFile)
 *
 * This function will populate the tables passed in as parameters
 *
 * Purpose: to test that the populateTables correctly populates the tables
 */

void testpopulateTables() {

  //char line[BUFSIZ];
  char * path = "emails/emails_1000";
  FILE * file = fopen(path, "r");
  char * addresses[NUM_EMAILS];
  int count = 0;
  char line[BUFSIZ];
  char * tmpPtr; //
  char * tmp; //temp ptr for email memory block
  while(fgets(line, BUFSIZ, file) != NULL) {
    tmpPtr = strchr(line, '\n');
    if(tmpPtr == NULL) {
      printf("newline not found!!\n");
      continue;
    }
    *tmpPtr = '\0';
    tmp = calloc(BUFSIZ, sizeof(char)); //email memory block
    if(tmp == NULL) {
      printf("err dynamic mem alloc\n");
    }
    for(int i = 0; i < strlen(line); i++) {
      line[i] = tolower(line[i]);
    }
    addresses[count] = tmp; // set in email in address array
    strncpy(addresses[count], line, BUFSIZ);
    count++; 
    if(count == NUM_EMAILS + 1) {
      break;
    }
  }
  fclose(file);

  //init tables with 0 filled void *'s
  table_t htbl;
  htbl.size = NUM_EMAILS;
  void * arr[NUM_EMAILS] = {0};
  htbl.tbl = arr;

  void * arr2[NUM_EMAILS] = {0};
  table_t rtbl;
  rtbl.size = NUM_EMAILS;
  rtbl.tbl = arr2;
  
  void * arr3[NUM_EMAILS] = {0};
  table_t eotbl;
  eotbl.size = NUM_EMAILS;
  eotbl.tbl = arr3;
  //call populateTables
  file = fopen(path, "r");
  populateTables(&htbl, &rtbl, &eotbl, file);
  fclose(file);
  //print contents of eotbl
  linkedList_t * ptr;
  //find each address
  int regH = 0, revH = 0, eoH = 0, hasEmail = 0;
  for(int i = 0; i < NUM_EMAILS; i++) {
    printf("\ntesting %s\n", addresses[i]);
    regH = hash(addresses[i]);
    revH = revHash(addresses[i]);
    eoH = evenOddHash(addresses[i]);

    printf("regH is: %d\n", regH);
    printf("revH is: %d\n", revH);
    printf("eoH is: %d\n", eoH);
    regH = regH % NUM_EMAILS;
    regH = regH + NUM_EMAILS;
    regH = regH % NUM_EMAILS;
    revH = revH % NUM_EMAILS;
    revH = revH + NUM_EMAILS;
    revH = revH % NUM_EMAILS;
    eoH = eoH % NUM_EMAILS;
    eoH = eoH + NUM_EMAILS;
    eoH = eoH % NUM_EMAILS;

    TEST(htbl.tbl[regH] == (void *)1);
    TEST(rtbl.tbl[revH] == (void *)1);
    ptr = (linkedList_t *)eotbl.tbl[eoH];
    if(ptr == NULL) {
      printf("no entry for index: %d\n", eoH);
    }
    hasEmail = 0;
    for(int j = 0; ;j++) {
      if(strcmp(addresses[i], ptr->value) == 0) {
        hasEmail = 1;
        break;
      }
      else if( j > NUM_EMAILS) {
        printf(":( %s, not found in linkedList", addresses[i]);
        break;
      }
      else if(((linkedList_t *)ptr)->next != NULL){
        ptr = ((linkedList_t *)ptr)->next;
      }
      else{
        printf("end of bucket, exiting");
        break;
      }
    }
    TEST(hasEmail == 1);
  }
}

int main() {
  (void) fprintf( stderr, "Testing populateTables...\n\n" );
  testpopulateTables();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
