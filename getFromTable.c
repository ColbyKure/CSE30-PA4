/*
 * Filename: getFromTable.c
 * Author: Colby Kure
 * Userid: cs30xdc
 * Description: This file holds the getFromTable function
 * Date: Jun 02 2018
 * Sources of Help: piazza, notes
 */

#include <stdio.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: getFromTable()
 * Function Prototype: void * getFromTable( int hashVal, table_t * table );
 * Description: This function returns the value at the 
 * Parameters: 
 *  hashVal - int - is the val to hash
 *  table - table_t * - pointer to table to search
 * Side Effects: none 
 * Error Conditions: none 
 * Return Value: void * of tbl[index] according to hashVal
 */

void * getFromTable(int hashVal, table_t * table) {
  int indx = hashVal % table->size;
  indx = indx + table->size;
  indx = indx % table->size;
  return table->tbl[indx];
}
