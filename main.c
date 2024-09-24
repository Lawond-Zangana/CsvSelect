#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"

/* Maximum length of a csv line (including NULL terminator) */
#define MAX_LINE_LEN 1024 // max length of a line including null terminator

/* Maximum number of columns to read or output */
#define MAX_COLS 100

/* Error message strings (to be used by various fprintf calls) */
#define INVALID_SYNTAX_MSG "Invalid syntax at line %d.\n"

void print_usage(const char *argv0)
{
    fprintf(stderr, "Usage: %s -c NCOLS -n NRECS COL1 COL2 COL3...\n", argv0);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_usage(argv[0]);
    }

    /**
     * Total number of columns to read from the CSV file. Can be less than the
     * actual number of columns in the CSV file but no more.
     * 
     * Must be a non-negative value. If left as -1 after parsing arguments,
     * raise an error.
    */
    int ncols = -1;

    /**
     * Total number of rows to read and process from the CSV file. If set to -1,
     * then process all rows from the CSV file (no limit). Default value is -1.
    */
    int nrecs = -1;

    /* Process command line arguments using `getopt` */
    int c;
    

    while ((c = getopt(argc, argv, "n:c:")) != -1) {
        // TODO: Write the switch-case statement to fill in 
        // the `ncols` and `nrecs` variables.
        switch (c) {
                
            case 'n': //when n-flag gets detected
               nrecs  = atoi(optarg); //n followed by value
               //check if value is less than 0 
               if (nrecs < 0){
                 fprintf(stderr, "value can't be negative.\n");
                 exit(EXIT_FAILURE);
                }
               break;

            case 'c': //when -c flag gets detected
               ncols  = atoi(optarg); //c followed by value

              //check if value is less than 0
              if (ncols < 0){
                fprintf(stderr, "value can't be negative.\n");
                exit(EXIT_FAILURE);
              }
              break;
            }
        } 
        
        
   
    

    if (ncols < 0) {
        fprintf(stderr, "ncols not specified.\n");
        return EXIT_FAILURE;

    }

    /* number of columns to output */
    int count = argc - optind;
    if (count <= 0) {
        fprintf(stderr, "no output columns specified.\n");
        return EXIT_FAILURE;
    }

    /* array of output indices */
    int outidx[MAX_COLS];
    // TODO: Fill in the outidx from argv. You do not have to use every
    // element in the outidx array, just as many as you need.
    
    
        //Task 2: Setting values to outidx[] 
        for (int i = 0; i < count; i++) {
                //atoi is an error handler
                outidx[i] = atoi(argv[i + optind]);
        }
  


    /* array of pointers to the start of each field in input buffer.
     * Has MAX_COLS elements but not all of the spaces need to be used.
     * You should only use up to the number of columns in the CSV file. */
    char *values[MAX_COLS];

    /* Line buffer for reading from stdin (keyboard input) */
    char line[MAX_LINE_LEN];

    /* Read input into the line buffer */
    int lineno = 0;

    while (fgets(line, MAX_LINE_LEN, stdin)) {
        // TODO: Call the parse() function and process the input
        // line by line. If parse() returns -1, terminate processing
        // and print error message (INVALID_SYNTAX_MSG).
    
        lineno++;

        if (parse(line, ncols, values) == -1) {
           fprintf(stderr, INVALID_SYNTAX_MSG, lineno);
           return EXIT_FAILURE; 
        }

   
        //Call the parse function
        parse(line, ncols, values); 
        //Print selected columns using values and outidx array
           for (int i = 0; i < count; i++) {
               int idx = outidx[i];
               if (idx >= 0 && idx < ncols + 1) {
                    printf("%s", values[idx-1]);
                    if (i < count - 1){
                            printf(",");
                    }
               }
         }   
         printf("\n"); //Print newline after each line of selected columns
     
     }

    return EXIT_SUCCESS;
}
