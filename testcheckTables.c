/*
 * Filename: testwriteTables
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function writeTables().
 * Date: 5/28/18
 * Sources of Help: notes, discussion notes, piazza
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

#define TBL_SIZE 500
/*
 * Unit Test for writeTables.s
 * 
 * int writeTables(char const * str)
 *
 * finds the writeTables of the string
 */
void testwriteTables() {
  char * dirName;
  table_t htbl;
  table_t rtbl;
  table_t eotbl;
  void ** h = calloc(TBL_SIZE, sizeof(void *));
  htbl.tbl = h;
  void ** r= calloc(TBL_SIZE, sizeof(void *));
  rtbl.tbl = r;
  void ** llarr = calloc(TBL_SIZE, sizeof(void *));
  eotbl.tbl = llarr;
  htbl.size = TBL_SIZE;
  rtbl.size = TBL_SIZE;
  eotbl.size = TBL_SIZE;
  dirName = "emails/emails_100";
  FILE * file = fopen(dirName, "r");
  populateTables(&htbl, &rtbl, &eotbl, file);

  char * str = "cedes@hack.co";
  int ret = checkTables(str, &htbl, &rtbl, &eotbl);

  fclose(file);
  free(h);
  free(r);
  free(llarr);
}

int main() {
  (void) fprintf( stderr, "Testing writeTables...\n\n" );
  testwriteTables();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
