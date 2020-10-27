#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum: the right number of 
//      arguments with a size_t type
void checkArgs (size_t providedNum, size_t rightNum);

// openFile: opens the file according to the file
//      name; exits in a failure state if the file
//      does not exit
// Parameter(s): the name of the file (a string)
// Return(s): an opened file stream
FILE * openFile (const char * fileName);


// closeFile: closes the file; exits in a failure
//      state if fails
// Parameter(s): a file stream
void closeFile (FILE * f);

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error input format
void formatErr ();

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error about memory
void memErr ();

// parseStory: using the provided file stream,
//      find the blanks and replace them with
//      suitable words by referring to the
//      catarray.
// Parameter(s): f: a file stream to read; 
//      cat: a catarray with words of different
//      categories stored
// Output(s): parsed story, to stdout
void parseStory (FILE * f, catarray_t * cat);

#endif

