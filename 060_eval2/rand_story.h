#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "provided.h"

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum1: the right number of 
//      arguments; rightNUm2: the second choice of the
//      right number of args, -1 when unnecessary
void checkArgs (size_t providedNum, int rightNum1, int rightNum2);

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

// isValidInt: decide whether a category string can
//      be converted to an int larger than 0
// Parameter(s): the category string
// Return(s): if the string contains characters(s)
//      other than digits, returns -1; if the string
//      is a number out of the range of a long int,
//      exits with a failure state; if the string is
//      a number larger than the number of the used
//      words, exits with a failure state
long isValidInt (const char * thisCat, size_t usedNum);

// makePrintChoice: choose which word to use to
//      replace the category name in the story
//      template
// Parameter(s): thisCat: the category name in the
//      story template; cat: the catarray which
//      provides the words to print; wordUsed: the
//      special category with words that are used
//      previously
// Output(s): the final choice of the word, to stdout
void makePrintChoice (char * thisCat, catarray_t * cat, category_t * wordUsed, int noRepeat);

// parseStory: using the provided file stream,
//      find the blanks and replace them with
//      suitable words by referring to the
//      catarray
// Parameter(s): f: a file stream to read; 
//      cat: a catarray with words of different
//      categories stored; noRepeat: specify the
//      requirement that no repeated words should
//      be used
// Output(s): parsed story, to stdout
void parseStory (FILE * f, catarray_t * cat, int noRepeat);

// wordInCat: checks whether a word is already in a
//      certain category
// Parameter(s): thisWord: the word to be found;
//      thisCat: the category to be checked
// Return(s): the index of the word in the category;
//      -1 when the word does not exist
int wordInCat (const char * thisWord, category_t * thisCat);

// catInArr: checks whether a category is already
//      in the catarray
// Parameter(s): thisCategory: the category to be
//      checked; catArr: the corresponding catarray
// Return(s): the index of the category in the catarray;
//      -1 if not exists
int catInArr (const char * thisCategory, catarray_t * catArr);

// storeWord: store the word in the category and increment
//      the word num of the category
// Parameter(s): word: the word to be stored (which is already
//      allocated); thisCate: the target category
void storeWord (char * word, category_t * thisCate);

// removeWord: remove the word in a certain category and
//      decrement the word num of the category
// Parameter(s): wordIndex: the index of word to be removed; 
//      catIndex: the index of the category to be modified
//      catArr: the catarray to be modified
void removeWord (int wordIndex, int catIndex, catarray_t * catArr);

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

// freeWordsInCat: free the memory allocated to store
//      words in a single category
// Parameter(s): thisCat: the category  with its words
//      to be freed
void freeWordsInCat (category_t * thisCat);

// freeCats: free the memory allocated to store
//      the catarray
// Parameter(s): thisCatArr: the catarray to be
//      freed
void freeCats(catarray_t * thisCatArr);

#endif

