#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum: the right number of 
//      arguments with a size_t type
void checkArgs (size_t providedNum, size_t rightNum) {
    if (providedNum != rightNum) {
        fprintf(stderr, "Wrong number of args\n");
        exit(EXIT_FAILURE);
    }
    return;
}

// openFile: opens the file according to the file
//      name; exits in a failure state if the file
//      does not exit
// Parameter(s): the name of the file (a string)
// Return(s): an opened file stream
FILE * openFile (const char * fileName) {
    FILE * f = fopen(fileName, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

// closeFile: closes the file; exits in a failure
//      state if fails
// Parameter(s): a file stream
void closeFile (FILE * f) {
    if (fclose(f) != 0) {
        fprintf(stderr, "Error closing file\n");
        exit(EXIT_FAILURE);
    }
    return;
}

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error input format
void formatErr () {
    fprintf(stderr, "Error input format\n");
    exit(EXIT_FAILURE);
    return;
}

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error about memory
void memErr () {
    fprintf(stderr, "Memory act(s) failed\n");
    exit(EXIT_FAILURE);
    return;
}

// parseStory: using the provided file stream,
//      find the blanks and replace them with
//      suitable words by referring to the
//      catarray.
// Parameter(s): f: a file stream to read; 
//      cat: a catarray with words of different
//      categories stored
// Output(s): parsed story, to stdout
void parseStory (FILE * f, catarray_t * cat) {
    int c;
    // categoryFinished: check whether the cats
    //      are closed by an underscore
    int categoryFinished = 1;
    while ((c = fgetc(f)) != EOF) {
        // If the character is not an underscore
        //      and we did not find underscore
        //      before, we simply print it out
        if (c != '_') {
            printf("%c", c);
            continue;
        }
        categoryFinished = 0;
        char * thisCat = NULL;
        size_t thisCatLen = 0;
        while ((c = fgetc(f)) != EOF) {
            if (c == '_') {
                categoryFinished = 1;
                break;
            }
            thisCatLen++;
            thisCat = realloc(thisCat, thisCatLen * sizeof(* thisCat));
            thisCat[thisCatLen - 1] = c;
        }
        thisCatLen++;
        thisCat = realloc(thisCat, thisCatLen * sizeof(* thisCat));
        thisCat[thisCatLen - 1] = '\0';
        if (!categoryFinished) {
            formatErr();
            break;
        }
        printf("%s", chooseWord(thisCat, cat));;
        free(thisCat);
    }
    return;
}