/*
 * Filename: pushToList.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: Unit test program to test the function pushToList().
 * Date: 5/28/18
 * Sources of Help: notes, discussion notes, piazza
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit test for pushToList()
 *
 * void pushToList(void ** head, char * str);
 *
 * This function allocates memory for the new Linked List object and the str and
 * then sets it as a new head node for LinkedList bucket
 *
 * Pupose: to test that linkedtlist is correctly updated.
 */

void testpushToList() {
  linkedList_t a;
  linkedList_t b;
  linkedList_t c;
  linkedList_t d;
  linkedList_t e;
  linkedList_t f;
  linkedList_t g;
  a.value = "Thou";
  a.next = &b;
  b.value = "Shall";
  b.next = &c;
  c.value = "Not";
  c.next = &d;
  d.value = "Sleep";
  d.next = &e;
  e.value = "With";
  e.next = &f;
  f.value = "Thy";
  f.next = &g;
  g.value = "Neighbor";
  g.next = NULL;

  linkedList_t * first = NULL;
  pushToList((void**)&first, "Neighbor");
  pushToList((void**)&first, "Thy");
  pushToList((void**)&first, "With");
  pushToList((void**)&first, "Sleep");
  pushToList((void**)&first, "Not");
  pushToList((void**)&first, "Shall");
  pushToList((void**)&first, "Thou");
  TEST(~strcmp(first->value, a.value));
  first = first->next;
  TEST(~strcmp(first->value, b.value));
  first = first->next;
  TEST(~strcmp(first->value, c.value));
  first = first->next;
  TEST(~strcmp(first->value, d.value));
  first = first->next;
  TEST(~strcmp(first->value, e.value));
  first = first->next;
  TEST(~strcmp(first->value, f.value));
  first = first->next;
  TEST(~strcmp(first->value, g.value));
}

int main() {
  (void) fprintf( stderr, "Testing pushToList...\n\n" );
  testpushToList();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
