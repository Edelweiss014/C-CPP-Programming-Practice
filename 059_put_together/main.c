#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(EXIT_FAILURE);
  }
  counts_t * c = createCounts();
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * name = malloc(strlen(line) * sizeof(* name));
    strncpy(name, line, strlen(line) - 1);
    name[strlen(line) - 1] = '\0';
    char * value = lookupValue(kvPairs, name);
    addCount(c, value);
    free(name);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
 //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 1) {
    fprintf(stderr, "Too few arguments\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Error closing file\n");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
