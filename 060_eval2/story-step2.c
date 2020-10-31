#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"

// story-step1: parses the words provided in the
//      file indicated by the command line arg;
//      stores the words in the catarray and then
//      outputs them to stdout. 
// Argument(s): the name of the file to be parsed
int main(int argc, char ** argv) {
    // checks for invalid args/files
    checkArgs(argc, 2, -1);
    FILE * f = openFile(argv[1]);
    // finish words collecting and printing
    catarray_t * thisCatArr = collectWords(f);
    printCatArr(thisCatArr);
    // frees the memory
    freeCats(thisCatArr);
    closeFile(f);
    return EXIT_SUCCESS;
}