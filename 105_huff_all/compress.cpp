#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include <fstream>
#include "readFreq.h"
#include "node.h"



void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream myFile;
  myFile.open(inFile);
  if (myFile.fail()) {
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  int c;
  while ((c = myFile.get()) != EOF) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(c);
    bfw.writeBitString(it->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  std::map<unsigned,BitString>::const_iterator it = theMap.find(256);
  bfw.writeBitString(it->second);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree (counts);
  delete[] counts;
  std::map<unsigned,BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete tree;
  return EXIT_SUCCESS;
}
