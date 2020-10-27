#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"

int main(int argc, char ** argv) {
    checkArgs(argc, 2);
    FILE * f = openFile(argv[1]);
    parseStory(f, NULL);
    closeFile(f);
    return EXIT_SUCCESS;
}