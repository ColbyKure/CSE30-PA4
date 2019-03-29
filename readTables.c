/*
 * Filename: readTables.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the readTables function
 * Date: Jun 02 2018
 * Sources of Help: piazza, discussion, tutorials point fread 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NUM_BITS_IN_BYTE 8

/*
 * Function Name: readTables()
 * Function Prototype: void readTables(FILE * inFile, table_t * htbl, table_t *
 *  rtbl, table_t * eotbl);
 * Description: This function reads from the outFile and populates the three 
 *  hashTables which were serialized in writeTables. 
 * Parameters: 
 *  inFile - FILE * - file to get info from 
 *  htbl - table_t * - first table 
 *  rtbl - table_t * - second table 
 *  eotbl - table_t * - third table 
 * Side Effects: prints error message in case of error
 * Error Conditions: error dynamically allocating memory
 * Return Value: none
 */

void readTables(FILE * inFile, table_t * htbl, table_t * rtbl, table_t * eotbl){
  //seek beginning of file
  fseek(inFile, 0, SEEK_SET);

  //get size
  int size = 0;
  fread(&size, sizeof(int), 1, inFile);

  //get htbl array
  void ** firstT = calloc(size, sizeof(void *));
  if(firstT == NULL) {
    perror(MEM_ERR);
    return;
  }
  fread(firstT, sizeof(void *), size, inFile);

  //get rtbl array
  void ** secT = calloc(size, sizeof(void *));
  if(secT == NULL) {
    perror(MEM_ERR);
    return;
  }
  fread(secT, sizeof(void *), size, inFile);
  
  //set htbl and rtbl
  htbl->tbl = firstT;
  rtbl->tbl = secT;
  htbl->size = size;
  rtbl->size = size;

  //get and set eotbl array
  eotbl->size = size;
  void ** llT = calloc(size, sizeof(void *));
  if(llT == NULL) {
    perror(MEM_ERR);
    return;
  }
  eotbl->tbl = llT;

  //get BUFSIZ chars from file
  char buf[BUFSIZ];
  int numRead = fread(buf, sizeof(char), BUFSIZ, inFile);
  //printf("\nreading first: %s\n", buf);
 
  //extract eotbl
  int readAgain = 1;
  int pushCount = 0;
 
  char * reader;
  char * email;
  int bucketCount = 0;
  int i, flag = 0;
  do{
    reader = buf;
    email = buf;
    i = 0;
    char part1[BUFSIZ] = {0};
    while(*reader == '\0') {
      if(*part1 != 0) {
        break;
      }
      i++;
      bucketCount++;
      reader++; //next char in buf
      email++;
    }
    for(; i < BUFSIZ; i++) {
      if(*reader != '\0') {
        flag = 0;
        reader++;
        continue;
      }
      else {
        if(flag) {
          bucketCount++;
          if(bucketCount > size) {
            break;
          }
          reader++;
          email = reader;
          continue;
        }
        pushCount++;
        pushToList((eotbl->tbl + bucketCount), email);
        reader++;
        email = reader;
        flag = 1;
      }
    }
    if(readAgain == 0) {
      break;
    }
    if(buf[numRead - 1] != '\0') {
      readAgain = 1;
      strncpy(part1, email, reader - email); //copy the rest of the email to part1
      int len = reader - email; //length of string
      strncpy(buf, part1, len); //copy over partial email to beginning of buf
      char * newStart = buf + len; //find pointer to next char in buf
      int newlen = BUFSIZ - len; //find new length to copy over
      numRead = fread(newStart, sizeof(char), newlen, inFile);
      if(numRead != newlen) {
        readAgain = 0;
      }
    }
    else if(buf[numRead - 1] == '\0') {
      readAgain = 1;
      numRead = fread(buf, sizeof(char), BUFSIZ, inFile);
      if(numRead != BUFSIZ) {
        readAgain = 0;
      }
    }
  }while(1);

  //print LinkedList
  /*pushCount = 0;
  for(int i = 0; i < size; i++) {
    printf("index: %d\n", i);
    if(eotbl->tbl[i] == NULL) {
      continue;
    }
    linkedList_t * llptr = eotbl->tbl[i];
    while(llptr->next != NULL) {
      printf("%s\n", llptr->value);
      pushCount++;
      llptr = llptr->next;
    }
    printf("%s\n", llptr->value);
    pushCount++;
  }
  printf("number in linkedList = %d\n", pushCount);
  */
}
