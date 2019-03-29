/*
 * Filename: testhash
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function hash().
 * Date: 5/15/18
 * Sources of Help: notes, discussion notes, piazza
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"


/* Helper function to build the table for you */
int hashC(char const * str) {
  int hash = HASH_START_VAL;
  int strLen;
  if(str == NULL) {
    strLen = 0;
  }
  else {
    strLen = strlen(str);
  }
  for(int i = 0; i < strLen; i++) {
    hash = hash * HASH_PRIME + str[i];
  }
  return hash;
}

/*
 * Unit Test for hash.s
 * 
 * int hash(char const * str)
 *
 * finds the hash of the string
 */
void testhash() {
  char * str;

  str = "AB";
  TEST(hash(str) == hashC(str));

  str = "12";
  TEST(hash(str) == hashC(str));

  str = "a";
  TEST(hash(str) == hashC(str));

  str = "asd234SDGs";
  TEST(hash(str) == hashC(str));

  str = "rSwer34gdfbSDF";
  TEST(hash(str) == hashC(str));

  str = "";
  TEST(hash(str) == hashC(str));

  str = NULL;
  TEST(hash(str) == hashC(str));

  str = "virginity@hack.co";
  TEST(hash(str) == hashC(str));
  TEST(hash(str) == hash(str));
}

int main() {
  (void) fprintf( stderr, "Testing hash...\n\n" );
  testhash();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
