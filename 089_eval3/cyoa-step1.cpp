
#include <iostream>
#include <cstdlib>
#include "page.h"
#include "cyoa.h"

int main() {
    std::string filename;
    std::cin >> filename;
    Page p1(filename);
    p1.printPage();
    return EXIT_SUCCESS;
}
