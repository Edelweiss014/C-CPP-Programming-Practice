#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"


// story-step3: makes use of the functions in step
//      1 and step 2, but it should add the 
//      functionality to 1) randomly chooses a word
//      from the named category to replace each blank
//      and 2) support references to previously used
//      words
// Argument(s): the name of the file to be parsed, 
//      1 for words and 1 for story template
int main(int argc, char ** argv) {
    // checks for invalid args/files
    checkArgs(argc, 3, -1);
    FILE * f_words = openFile(argv[1]);
    FILE * f_story = openFile(argv[2]);
    // collects the words
    catarray_t * thisCatArr = collectWords(f_words);
    // reads/prints the story
    parseStory(f_story, thisCatArr, 0);
    // frees the memory
    freeCats(thisCatArr);
    closeFile(f_words);
    closeFile(f_story);
    return EXIT_SUCCESS;
}