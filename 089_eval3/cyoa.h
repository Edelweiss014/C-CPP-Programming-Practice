
#ifndef _CYOA_H_
#define _CYOA_H_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>

// checkArgs: if there are wrong number of arguments
//      provided in the command line, exits with a
//      failure state
// Parameter(s): providedNum: the existing number of 
//      arguments; rightNum: the right number of 
//      arguments
void checkArgs (size_t providedNum, size_t rightNum);

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error input format
void formatErr (std::string mesg = "Error format");

// formatErr: exits with failure after printing
//      error message to stderr indicating the
//      error range
void rangeErr ();

// notAvailErr: exits with failure after printing
//      error message to stderr indicating that
//      the variable is not available
void notAvailErr ();

// readFile: read the file acccording to its name
// Parameter(s) : the ifstream to receive the file;
//      the filename
// Modifies: the input filestream
// Output(s): if fails, prints error message
// Return(s): the opened ifstream
std::ifstream & readFile (std::ifstream & read, const char * filename);

// unsignToStr: convert a unsigned int to a C++ str
// Parameter(s): an unsigned number to be converted
// Return(s): a string converted from num
std::string unsignToStr (unsigned num);

// unsignToStr: convert a C++ str to unsigned
// Parameter(s): an string to be converted
// Return(s): a num converted from str
unsigned strToUnsign (std::string & str);

// isDigits: check whether a string contains only
//      digits
// Parameter(s): a string to be checked
// Return(s): true for a str with only digits, false
//      otherwise
bool isAllDigits (std::string & str);

#endif
