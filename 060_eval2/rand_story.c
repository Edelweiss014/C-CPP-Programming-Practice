#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "rand_story.h"

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum1: the right number of 
//      arguments; rightNUm2: the second choice of the
//      right number of args, -1 when unnecessary
void checkArgs (size_t providedNum, int rightNum1, int rightNum2) {
    if (rightNum2 == -1 && providedNum != rightNum1) {
        fprintf(stderr, "Wrong number of args\n");
        exit(EXIT_FAILURE);
        return;
    }
    else if (providedNum != rightNum1 && providedNum != rightNum2) {
        fprintf(stderr, "Wrong number of args\n");
        exit(EXIT_FAILURE);
        return;
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

void rangeErr () {
    fprintf(stderr, "Num out of range\n");
    exit(EXIT_FAILURE);
    return;
}

// isValidInt: decide whether a category string can
//      be converted to an int larger than 0
// Parameter(s): the category string
// Return(s): if the string contains characters(s)
//      other than digits, returns -1; if the string
//      is a number out of the range of a long int,
//      exits with a failure state; if the string is
//      a number larger than the number of the used
//      words, exits with a failure state
long isValidInt (const char * thisCat, size_t usedNum) {
    long converted = 0;
    for (size_t i = 0; i < strlen(thisCat); i++) {
        if (!isdigit(thisCat[i])) {
            return -1;
        }
    }
    errno = 0;
    converted = strtol(thisCat, NULL, 10);
    if (errno == ERANGE || converted > (long) usedNum) {
        rangeErr();
    }
    return converted;
}

// makePrintChoice: choose which word to use to
//      replace the category name in the story
//      template
// Parameter(s): thisCat: the category name in the
//      story template; cat: the catarray which
//      provides the words to print; wordUsed: the
//      special category with words that are used
//      previously
// Output(s): the final choice of the word, to stdout
void makePrintChoice (char * thisCat, catarray_t * cat, category_t * wordUsed, int noRepeat) {
    // case 0: simply prints out "cat"
    if (cat == NULL) {
        printf("%s", chooseWord(thisCat, cat));
        return;
    }
    char * thisWord = NULL;
    // case 1: look up for previously used word
    long thisCatToInt = isValidInt(thisCat, wordUsed->n_words);
    if (thisCatToInt > 0) {
        printf("%s", wordUsed->words[wordUsed->n_words - thisCatToInt]);
        thisWord = strdup(wordUsed->words[wordUsed->n_words - thisCatToInt]);
        storeWord(thisWord, wordUsed);
        return;
    }
    // case 2: randomly chooses words
    if (catInArr(thisCat, cat) == -1) {
        formatErr();
    }
    thisWord = strdup(chooseWord(thisCat, cat));
    printf("%s", thisWord);
    storeWord(thisWord, wordUsed);
    if (noRepeat == 1) {
        int catIndex = -1; 
        int wordIndex = -1;
        if ((catIndex = catInArr(thisCat, cat)) > -1) {
            wordIndex = wordInCat(thisWord, &(cat->arr[catIndex]));
        }
        if (wordIndex > -1 && catIndex > -1) {
            removeWord(wordIndex, catIndex, cat);
        }
    }
    return;
}

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
void parseStory (FILE * f, catarray_t * cat, int noRepeat) {
    // Initialize the special category to store
    //      the used words
    category_t wordUsed;
    wordUsed.n_words = 0;
    wordUsed.words = NULL;
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
        while ((c = fgetc(f)) != '\n') {
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
        makePrintChoice(thisCat, cat, &wordUsed, noRepeat);
        free(thisCat);
    }
    freeWordsInCat(&wordUsed);
    return;
}

// wordInCat: checks whether a word is already in a
//      certain category
// Parameter(s): thisWord: the word to be found;
//      thisCat: the category to be checked
// Return(s): the index of the word in the category;
//      -1 when the word does not exist
int wordInCat (const char * thisWord, category_t * thisCat) {
    if (thisCat == NULL) {
        nullPointerErr();
    }
    for (size_t i = 0; i < thisCat->n_words; i++) {
        if (strcmp(thisWord, thisCat->words[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// catInArr: checks whether a category is already
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
// Parameter(s): word: the word to be stored (which is already
//      allocated); thisCate: the target category
void storeWord (char * word, category_t * thisCate) {
    if (thisCate == NULL) {
        nullPointerErr();
    }
    thisCate->n_words++;
    thisCate->words = realloc(thisCate->words, thisCate->n_words * sizeof(* thisCate->words));
    thisCate->words[thisCate->n_words - 1] = word;
    return;
}

// removeWord: remove the word in a certain category and
//      decrement the word num of the category
// Parameter(s): wordIndex: the index of word to be removed; 
//      catIndex: the index of the category to be modified
//      catArr: the catarray to be modified
void removeWord (int wordIndex, int catIndex, catarray_t * catArr) {
    if (wordIndex == -1 || catIndex == -1) {
        return;
    }
    // the words array in the catarray: 
    //      catArr->arr[catIndex].words
    char ** newWords = malloc((catArr->arr[catIndex].n_words - 1) * sizeof (* newWords));
    // use j to trace the index of the newWords arr
    int j = 0;
    for (int i = 0; i < catArr->arr[catIndex].n_words; i++) {
        if (i == wordIndex) {
            continue;
        }
        else {
            newWords[j] = strdup(catArr->arr[catIndex].words[i]);
            j++;
        }
    }
    freeWordsInCat(&(catArr->arr[catIndex]));
    catArr->arr[catIndex].words = newWords;
    catArr->arr[catIndex].n_words--;
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

// freeSingleCat: free the memory allocated to store
//      a certain category (except its name, since not
//      all category has its name allocated)
// Parameter(s): thisCat: the category to be freed
void freeWordsInCat (category_t * thisCat) {
    if (thisCat == NULL) {
        return;
    }
    for (size_t i = 0; i < thisCat->n_words; i++) {
        free(thisCat->words[i]);
    }
    free(thisCat->words);
    return;
}

// freeCats: free the memory allocated to store
//      the catarray
// Parameter(s): thisCatArr: the catarray to be
//      freed
void freeCats(catarray_t * thisCatArr) {
    if (thisCatArr == NULL) {
        return;
    }
    for (size_t i = 0; i < thisCatArr->n; i++) {
        // free each category
        freeWordsInCat(&(thisCatArr->arr[i]));
        free(thisCatArr->arr[i].name);
    }
    free(thisCatArr->arr);
    free(thisCatArr);
    return;
}