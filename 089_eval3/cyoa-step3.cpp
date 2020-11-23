
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cstdio>
#include <fstream>
#include <cstdlib>

#include "story.h"
#include "cyoa.h"

int main(int argc, char ** argv) {
    checkArgs(argc, 2);
    Story s1(argv[1]);
    s1.verifyPages();
    s1.getPrev(true);
    return EXIT_SUCCESS;
}
