#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream myFile;
  uint64_t * myFreq = new uint64_t [257] ();
  myFile.open(fname);
  if (myFile.fail()) {
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }
  int c;
  while ((c = myFile.get()) != EOF) {
    myFreq[c]++;
  }
  myFreq[256] = 1;
  return myFreq;
}
