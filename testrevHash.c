/*
 * Filename: testrevHash
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function revHash().
 * Date: 5/26/18
 * Sources of Help: discussion notes, piazza
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

static int revHashC(char * src) {

  int hash = HASH_START_VAL;
  if(src == NULL) {
    return hash;
  }
  int strLen = strlen(src);
  for(int i = strLen - 1; i >= 0; i--) {
    hash = hash * HASH_PRIME + src[i];
  }
  return hash;
}

/*
 * Unit Test for revHash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {

  char * src = "ABCD";
  /* Validate the hash value. */
  TEST( revHash(src) == revHashC(src) );
  
  src = "";
  TEST( revHash(src) == revHashC(src) );

  src = "asdf";
  TEST( revHash(src) == revHashC(src) );

  src = "asFD";
  TEST( revHash(src) == revHashC(src) );

  src = "1234";
  TEST( revHash(src) == revHashC(src) );

  src = "12BD";
  TEST( revHash(src) == revHashC(src) );

  src = "1c3F$";
  TEST( revHash(src) == revHashC(src) );

  src = "1";
  TEST( revHash(src) == revHashC(src) );

  src = "a";
  TEST( revHash(src) == revHashC(src) );

  src = NULL;
  TEST( revHash(src) == HASH_START_VAL );

}

int main() {
  fprintf( stderr, "Testing revHash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
