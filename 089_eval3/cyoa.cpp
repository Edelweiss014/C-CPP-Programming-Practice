
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include "cyoa.h"

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum: the right number of 
//      arguments
void checkArgs (size_t providedNum, size_t rightNum) {
    if (providedNum != rightNum) {
        std::cerr << "Wrong number of args" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error input format
void formatErr () {
    std::cerr << "Error format" << std::endl;
    exit(EXIT_FAILURE);
    return;
}

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error range
void rangeErr () {
    std::cerr << "Num out of range" << std::endl;
    exit(EXIT_FAILURE);
    return;
}

// notAvailErr: exits with failure after printing
//      error message to stderr indicating that
//      the variable is not available
void notAvailErr () {
    std::cerr << "Not available" << std::endl;
    exit(EXIT_FAILURE);
    return;
}

// readFile: read the file acccording to its name
// Parameter(s) : the ifstream to receive the file;
//      the filename
// Return(s): the opened ifstream
std::ifstream & readFile (std::ifstream & read, const char * filename) {
    read.open(filename);
    return read;
}

// unsignToStr: convert a unsigned int to a C++ str
// Parameter(s): an unsigned number to be converted
// Return(s): a string converted from num
std::string unsignToStr (unsigned num) {
    std::ostringstream os;
    os << num;
    return os.str();
}

// unsignToStr: convert a C++ str to unsigned
// Parameter(s): an string to be converted
// Return(s): a num converted from str
unsigned strToUnsign (std::string & str) {
    std::stringstream os;
    unsigned num;
    os << str;
    os >> num;
    return num;
}

// isALlDigits: check whether a string contains only
//      digits
// Parameter(s): a string to be checked
// Return(s): true for a str with only digits, false
//      otherwise
bool isAllDigits (std::string & str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}