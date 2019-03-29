/*
 * Filename: create.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This is the main driver for the create portion of program
 * Date: Jun 02 2018
 * Sources of Help: piazza, discussion/lecture notes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#include "pa4Strings.h"
#include "pa4.h"

#define BASE 10

/*
 * Function Name: main.c 
 * Function Prototype: int main.c(int argc, char * argv[])
 * Description: This is the main driver for the create portion of the program.
 *  It will parse the command line arguments and build the hashatables, and then
 *  serialize them onto an outfile.
 * Parameters: 
 *  argc - int - number of command line arguments 
 * Side Effects: prints out error messages in case of error. Writes the
 *  serialized version of the tables to an outFile
 * Error Conditions: Command line argument error, missing infile or output flag,
 *  extra arguements, dynamic allocation failed.
 * Return Value: EXIT_SUCCESS on success, otherwise EXIT_FAILURE
 */

int main( int argc, char * argv[] ) {
  //long getopt 
  int flag;
  //create option array with flag values
  struct option options[] = {  \
      {LONG_HELP_FLAG, no_argument, NULL, HELP_FLAG} ,  \
      {LONG_SIZE_FLAG, required_argument, NULL, SIZE_FLAG} ,  \
      {LONG_INFILE_FLAG, required_argument, NULL, INFILE_FLAG} ,  \
      {LONG_OUTPUT_FLAG, required_argument, NULL, OUTPUT_FLAG},  \
      {0, 0, 0, 0}
  };
  //init variables
  long tSize = DEFAULT_SIZE;
  char * endptr;
  int inFlag = 0, outFlag = 0;
  FILE * inFile;
  FILE * outFile;
  while((flag = getopt_long(argc, argv, CREATE_FLAGS, options, NULL)) != -1) {
    //swtich statement for options
    switch(flag) {
      //help option
      case HELP_FLAG:
        fprintf(stderr, LONG_CREATE_USAGE);
        return EXIT_SUCCESS;
      //size option
      case SIZE_FLAG:
        errno = 0;
        tSize = strtol(optarg, &endptr, BASE);
        if(*endptr != '\0') {
          //not a valid num
          fprintf(stderr, INVALID_NUM, optarg);
          fprintf(stderr, SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        else if(errno != 0) {
          //too large num
          char errStr[BUFSIZ];
          snprintf(errStr, BUFSIZ, TOO_LARGE_NUM, optarg, BASE);
          perror(errStr);
          fprintf(stderr, SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        else if(isInRange(tSize, MIN_SIZE, MAX_SIZE + 1) == 0) {
          //not in range
          fprintf(stderr, TABLE_SIZE_ERR, MIN_SIZE, MAX_SIZE);
          fprintf(stderr, SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        break;
      //infile option
      case INFILE_FLAG:
        errno = 0;
        inFile = fopen(optarg, "r");
        if(errno != 0 ) {
          perror(FILTER_ERR);
          fprintf(stderr, SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        inFlag = 1;
        break;
      //outfile option
      case OUTPUT_FLAG:
        errno = 0;
        outFile = fopen(optarg, "w");
        if(errno != 0) {
          perror(FILTER_ERR);
          fprintf(stderr, SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        outFlag = 1;
        break;
      //bad option
      default:
        //error message automatically printed by getopt
        fprintf(stderr, SHORT_CREATE_USAGE);
        return EXIT_FAILURE;
    }
  }
  //end reading options
  if(inFlag == 0) {
    //inFile option not specified
    fprintf(stderr, ARG_ERR);
    fprintf(stderr, SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }
  if(outFlag == 0) {
    //outFile option not specified
    fprintf(stderr, ARG_ERR);
    fprintf(stderr, SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }
  if(argv[optind] != NULL) {
    fprintf(stderr, EXTRA_ARGS, argv[0]);
    fprintf(stderr, SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }

  //build hashtables and write to file:
  //init htbl
  table_t htbl;
  htbl.size = tSize;
  void ** hArr = calloc(tSize, sizeof(void *));
  if(hArr == NULL) {
    perror(MEM_ERR);
    return EXIT_FAILURE;
  }
  htbl.tbl = hArr;
  //init rtbl
  table_t rtbl;
  rtbl.size = tSize;
  void ** rArr = calloc(tSize, sizeof(void *));
  if(rArr == NULL) {
    perror(MEM_ERR);
    return EXIT_FAILURE;
  }
  rtbl.tbl = rArr;
  //init eotbl
  table_t eotbl;
  eotbl.size = tSize;
  void ** eoArr = calloc(tSize, sizeof(void *));
  if(eoArr == NULL) {
    perror(MEM_ERR);
    return EXIT_FAILURE;
  }
  eotbl.tbl = eoArr;

  populateTables(&htbl, &rtbl, &eotbl, inFile);
  writeTables(outFile, &htbl, &rtbl, &eotbl);
  //print LinkedList
  /*for(int i = 0; i < htbl.size; i++) {
    printf("index: %d\n", i);
    if(eotbl.tbl[i] == NULL) {
      continue;
    }
    linkedList_t * llptr = eotbl.tbl[i];
    while(llptr->next != NULL) {
      printf("%s\n", llptr->value);
      llptr = llptr->next;
    }
    printf("%s\n", llptr->value);
  }*/
  
  //free up memory
  free(htbl.tbl);
  free(rtbl.tbl);
  for(int i = 0; i < tSize; i++) {
    freeLinkedList(eotbl.tbl[i]);
  }
  free(eotbl.tbl);
  return EXIT_SUCCESS;
}
