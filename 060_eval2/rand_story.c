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

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error null pointer
void nullPointerErr () {
    fprintf(stderr, "Null pointer visited\n");
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

// catInArr: check whether a category is already
//      in the catarray
// Parameter(s): thisCategory: the category to be
//      checked; catArr: the corresponding catarray
// Return(s): the index of the category in the catarray;
//      -1 if not exists
int catInArr (const char * thisCategory, catarray_t * catArr) {
    if (catArr == NULL) {
        nullPointerErr();
    }
    for (size_t i = 0; i < catArr->n; i++) {
        if (strcmp(thisCategory, catArr->arr[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

// storeWord: store the word in the category and increment
//      the word num of the category
void storeWord (char * word, category_t * thisCate) {
    if (thisCate == NULL) {
        nullPointerErr();
    }
    thisCate->n_words++;
    thisCate->words = realloc(thisCate->words, thisCate->n_words * sizeof(* thisCate->words));
    thisCate->words[thisCate->n_words - 1] = word;
    return;
}

// parseWord: reads a line with a word and its
//      category and stores the word in the array
// Parameter(s): line: the line containing a word
//      with its category indicated; catArr: the
//      catarray to store the words
void parseWord (const char * line, catarray_t * catArr) {
    const char * colonPointer = strchr(line, ':');
    if (!colonPointer) {
        formatErr();
    }
    char * thisCategory = strndup(line, colonPointer - line);
    char * thisWord = strdup(colonPointer + 1);
    int index;
    if ((index = catInArr(thisCategory, catArr)) == -1) {
        catArr->n++;
        catArr->arr = realloc(catArr->arr, catArr->n * sizeof(* catArr->arr));
        // new category initialization
        catArr->arr[catArr->n - 1].words = NULL;
        catArr->arr[catArr->n - 1].n_words = 0;
        catArr->arr[catArr->n - 1].name = thisCategory;
        storeWord(thisWord, &(catArr->arr[catArr->n - 1]));
    }
    else {
        storeWord(thisWord, &(catArr->arr[index]));
        free(thisCategory);
    }
    return;
}

// collectWords: reads a file indicated in the
//      command line arg and collects the words
//      in it according to their categories
// Parameter(s): f: a file stream to read
// Return(s): a catarray with all words collected
//      according to their categories
// Output(s): words, according to their categories
catarray_t * collectWords (FILE * f) {
    if (f == NULL) {
        nullPointerErr();
    }
    catarray_t * thisCatArr = malloc(sizeof(* thisCatArr));
    if (thisCatArr == NULL) {
        memErr();
    }
    thisCatArr->n = 0;
    thisCatArr->arr = NULL;
    size_t sz = 0;
    int len = 0;
    char * line = NULL;
    while ((len = getline(&line, &sz, f)) >= 0) {
        line[strlen(line) - 1] = '\0';
        parseWord(line, thisCatArr);
    }
    free(line);
    return thisCatArr;
}

// printCatArr: prints the words and category
//      information of the required format
// Output(s): the words according to their
//      categories, to stdout
void printCatArr (catarray_t * thisCatArr) {
    if (thisCatArr == NULL) {
        return;
    }
    for (size_t i = 0; i < thisCatArr->n; i++) {
        printf("%s:\n", thisCatArr->arr[i].name);
        for (size_t j = 0; j < thisCatArr->arr[i].n_words; j++) {
            printf("  %s\n", thisCatArr->arr[i].words[j]);
        }
    }
    return;
}

// freeCats: free the memory allocated to story
//      the catarray
// Parameter(s): thisCatArr: the catarray to be
//      freed
void freeCats(catarray_t * thisCatArr) {
    if (thisCatArr == NULL) {
        return;
    }
    for (size_t i = 0; i < thisCatArr->n; i++) {
        // free each category
        for (size_t j = 0; j < thisCatArr->arr[i].n_words; j++) {
            // free each word
            free(thisCatArr->arr[i].words[j]);
        }
        free(thisCatArr->arr[i].words);
        free(thisCatArr->arr[i].name);
    }
    free(thisCatArr->arr);
    free(thisCatArr);
    return;
}