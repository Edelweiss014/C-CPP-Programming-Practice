#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"


// story-step1: parses the story provided in the
//      file indicated by the command line arg;
//      outputs the story with categories replaced
//      by "cat".
// Argument(s): the name of the file to be parsed
int main(int argc, char ** argv) {
    checkArgs(argc, 2, -1);
    FILE * f = openFile(argv[1]);
    parseStory(f, NULL, 0);
    closeFile(f);
    return EXIT_SUCCESS;
}