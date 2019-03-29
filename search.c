/*
 * Filename: search.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file hlds the search program
 * Date: Jun 02 2018
 * Sources of Help: piazza, notes
 */

#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NUM_TABLES 3

/*
 * Function Name: main()
 * Function Prototype: int main(int argc, cahr * argv[]);
 * Description: This is the main driver for the search portion of the program.
 *  It takes the command line arguments and parses them. It creates the
 *  hashtable with the input file, and then interatively searches through the
 *  table, printing stats if need be.
 * Parameters: 
 *  argc - int - number of arguments from command line 
 *  argv - char ** - array of char pointers to string representation of input
 * Side Effects: prompts the user for commands in terative search and prints
 *  stats to stdout if commanded.
 * Error Conditions: Error callinf fopen, no input file, extra arguements from
 *  the command line
 * Return Value: return 1 if error and 0 on success
 */

int main(int argc, char * argv[]) {
  int opt;
  FILE * in;
  int pStats = 0, inFlag = 0;
  //getopt portion 
  while((opt = getopt(argc, argv, SEARCH_FLAGS)) != -1) {
    switch(opt) {
      case INFILE_FLAG:
        //infile
        errno = 0;
        in = fopen(optarg, "r");
        if(errno != 0) {
          perror(RTABLE_FILE_ERR);
          fprintf(stderr, SHORT_SEARCH_USAGE);
          return 1;
        }
        inFlag = 1;
        break;
      case HELP_FLAG:
        //help
        fprintf(stdout, LONG_SEARCH_USAGE);
        return 0;
      case STATS_FLAG:
        //stats
        pStats = 1;
        break;
      default:
        fprintf(stderr, SHORT_SEARCH_USAGE);
        return 1;
    }
  }
  //error check after getopt
  if(inFlag == 0) {
    //no -i flag
    fprintf(stderr, MISSING_INFILE);
    fprintf(stderr, SHORT_SEARCH_USAGE);
    return 1;
  }
  if(argv[optind] != NULL) {
    //extra arguments 
    fprintf(stderr, EXTRA_ARGS, argv[0]);
    fprintf(stderr, SHORT_SEARCH_USAGE);
    return 1;
  }

  //init tables and read from file 
  table_t htbl = {0};
  table_t rtbl = {0};  
  table_t eotbl = {0};

  //read tables
  readTables(in, &htbl, &rtbl, &eotbl);

  //begin Query portion
  int * counts = calloc(NUM_TABLES + 1, sizeof(int));
  beginUserQuery(counts, &htbl, &rtbl, &eotbl, pStats);
  //print number of collisions.
  if(pStats) {
    printf(STATS_FOUND, counts[NUM_TABLES]);
    for(int i = NUM_TABLES; i > 0; i--) {
      printf(STATS_COLLISION, counts[i-1], i);
    }
    printf(STATS_TOTAL, numSearches);
  }
  //free all allocated memory
  free(counts);
  free(htbl.tbl);
  free(rtbl.tbl);
  int size = eotbl.size;
  for(int i = 0; i < size; i++) {
    freeLinkedList(eotbl.tbl[i]);
  }
  free(eotbl.tbl);
  return 0;
}
