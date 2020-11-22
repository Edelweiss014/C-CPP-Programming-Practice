
#include <iostream>
#include <cstdlib>
#include "page.h"
#include "cyoa.h"

int main(int argc, char ** argv) {
    checkArgs(argc, 2);
    std::string filename(argv[1]);
    Page p1(filename);
    p1.printPage();
    return EXIT_SUCCESS;
}
