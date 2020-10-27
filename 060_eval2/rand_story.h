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

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error null pointer
void nullPointerErr ();

// parseStory: using the provided file stream,
//      find the blanks and replace them with
//      suitable words by referring to the
//      catarray
// Parameter(s): f: a file stream to read; 
//      cat: a catarray with words of different
//      categories stored
// Output(s): parsed story, to stdout
void parseStory (FILE * f, catarray_t * cat);

// catInArr: check whether a category is already
//      in the catarray
// Parameter(s): thisCategory: the category to be
//      checked; catArr: the corresponding catarray
// Return(s): the index of the category in the catarray;
//      -1 if not exists
int catInArr (const char * thisCategory, catarray_t * catArr);

// storeWord: store the word in the category and increment
//      the word num of the category
void storeWord (char * word, category_t * thisCate);

// parseWord: reads a line with a word and its
//      category and stores the word in the array
// Parameter(s): line: the line containing a word
//      with its category indicated; catArr: the
//      catarray to store the words
void parseWord (const char * line, catarray_t * catArr);

// collectWords: reads a file indicated in the
//      command line arg and collects the words
//      in it according to their categories
// Parameter(s): f: a file stream to read
// Return(s): a catarray with all words collected
//      according to their categories
// Output(s): words, according to their categories
catarray_t * collectWords (FILE * f);

// printCatArr: prints the words and category
//      information of the required format
// Output(s): the words according to their
//      categories, to stdout
void printCatArr (catarray_t * thisCatArr);

// freeCats: free the memory allocated to story
//      the catarray
// Parameter(s): thisCatArr: the catarray to be
//      freed
void freeCats(catarray_t * thisCatArr);

#endif

