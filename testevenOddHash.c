/*
 * Filename: testEOHash
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function EOHash().
 * Date: 5/28/18
 * Sources of Help: discussion notes, piazza
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

static int EOHashC(char * src) {

  int ret = 0;
  if(src == NULL) {
    ret = HASH_START_VAL;
    int strLen = 0;
    for(int i = 0; i < strLen; i++) {
      ret = ret * HASH_PRIME + src[i];
    }
    return ret;
  }
  int len = strlen(src);
  char newStr[len + 1];
  int counter = 0;
  for(int i = 0; i < len; i+=2) {
    newStr[counter] = src[i];
    counter++;
  }
  for(int i = 1; i < len; i+=2) {
    newStr[counter] = src[i];
    counter++;
  }
  //printf("\noriginal string: %s\n", src);
  newStr[len] = '\0';
  //printf("modified string: %s\n\n", newStr);
  ret = HASH_START_VAL;
  int strLen = strlen(src);
  for(int i = 0; i < strLen; i++) {
    ret = ret * HASH_PRIME + newStr[i];
  }
  return ret;
}

/*
 * Unit Test for EOHash.s
 *
 * long EOHash( char * src );
 *
 */
void testEOHash() {

  char * src = "ABCD";
  /* Validate the hash value. */
  TEST( evenOddHash(src) == EOHashC(src) );
  
  src = "";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = "asdf";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = "1a2b3c4d5e";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = "asFD";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = "1234";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = "a";
  TEST( evenOddHash(src) == EOHashC(src) );

  src = NULL;
  TEST( evenOddHash(src) == HASH_START_VAL );

}

int main() {
  fprintf( stderr, "Testing EOHash...\n\n" );
  testEOHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
