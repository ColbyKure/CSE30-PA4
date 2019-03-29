/*
 * File: pa4.h
 * Description: Header file that contains function prototypes and
 *              constants.
 *
 * XXX Only add constants to this file at the bottom.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */

#ifndef PA4_H       /* Macro Guard */
#define PA4_H
#include <stdio.h>

/* Struct Definitions */
typedef struct {
  int size;
  // It's a pointer to void pointers. In table 3, the void pointers are 
  // linkedList_t structs.
  void ** tbl;
} table_t;

typedef struct llist {
  struct llist * next;
  char * value;
} linkedList_t;

/* Checking Table */
#define IN_TABLE 4

/* Hashing */
#define HASH_START_VAL 11
#define HASH_PRIME     37

/* Table Size */
#define DEFAULT_SIZE 5000
#define MIN_SIZE 10
#define MAX_SIZE 25000

/* getopt constants */
#define SEARCH_FLAGS "i:hx"
#define CREATE_FLAGS "i:ho:s:"

#define LONG_HELP_FLAG "help"
#define LONG_INFILE_FLAG "infile"
#define LONG_OUTPUT_FLAG "output"
#define LONG_SIZE_FLAG "size"

#define SIZE_FLAG 's'
#define OUTPUT_FLAG 'o'
#define INFILE_FLAG 'i'
#define HELP_FLAG 'h'
#define STATS_FLAG 'x'

// These macros combine to convert __LINE__ which is a number to a string,
// then the preprocessor conctatenates all three to be file:lineNo for the 
// OOM perror call.
#define STR_HELP( x ) #x
#define MEM_ERR __FILE__ ":" STR_HELP( __LINE__ )

/* C Function Prototypes */
int evenOddHash( char * str );
void populateTables( table_t * htbl, table_t * rtbl, table_t * eotbl,
    FILE * dataFile );
void * getFromTable( int hashVal, table_t * table );
int checkTables( char * str, table_t * htbl, table_t * rtbl, table_t * eotbl );
void pushToList( void ** head, char * str );
void readTables( FILE * inFile, table_t * htbl, table_t * rtbl,
    table_t * eotbl );
void writeTables( FILE * outFile, table_t * htbl, table_t * rtbl,
    table_t * eotbl );
void beginUserQuery(int counts [], table_t * htbl, table_t * rtbl,
    table_t * eotbl, int statsOn);
void freeLinkedList( linkedList_t * head );

/* Assembly Function Prototypes */
int hash( char * str );
int revHash( char * str );
long isInRange( long num, long min, long max );

//define global variable for numSearches
extern int numSearches;
#endif
