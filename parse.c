#include <stdio.h>

#include "parse.h"

/**
 * Parse a line from a CSV file.
 * 
 * Parameters:
 *   char *line     The line buffer; a string containing a line in the file.
 *   int   ncols    The total number of columns in the row.
 *   char *values[] An array of pointers to the separate column values in the row.
 * Return:
 *   int: 0 if line was parse successfully, -1 if some error occurred.
*/

    


int parse(char *line, int ncols, char *values[])
{
    // TODO: Implement this function 
    
    // Do NOT use an index to traverse `line`! You will not
    // receive any points if you do so.

   //Invalid inputs 
   if (line == NULL || ncols <= 0 || values == NULL) {
       return -1;
   }

   //Initialize variables 
   int colCount = 0;
   char *token = line;

   while (*token != '\0' && colCount <= ncols) {
        //Split the string by swaping commas with null characters
        if (*token == ',') {
            *token = '\0';
            token++; // increment token
        }

    //Store the token in the values array
    values[colCount] = token;

    //Move to the next token aka start of next substring
    while (*token != '\0' && *token != ',') {
            token++;
    }

    //Increment the column count
    colCount++;
   }

   //Case if there are fewer columns than expected
   if (colCount < ncols) {
        return -1;
   }

   //return 0 if everything works 
   return 0;
}
