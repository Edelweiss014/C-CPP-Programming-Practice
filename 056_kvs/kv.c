#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void readPair(char * line, kvpair_t * pair) {
  char * equPosition = strchr(line, '=');
  if (equPosition == NULL) {
    fprintf(stderr, "Invalid key-value pair\n");
    exit(EXIT_FAILURE);
  }
  size_t i = 0;
  for (i = 0; i < equPosition - line; i++) {
    if (i == 64) {
      fprintf(stderr, "Too long key\n");
      exit(EXIT_FAILURE);
    }
    pair->key[i] = line[i];
  }
  pair->key[i] = '\0';
  size_t j = 1;
  for (j = 1; j <strlen(line); j++) {
    if (j == 65) {
      fprintf(stderr, "Too long value\n");
      exit(EXIT_FAILURE);
    }
    pair->value[j - 1] = equPosition[j];
  }
  pair->value[j - 1] = '\0';
  return;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * thisArray = malloc(sizeof(* thisArray));
  thisArray->len = 0;
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    kvpair_t * thisPair = malloc(sizeof(* thisPair));
    readPair(line, thisPair);
    thisArray->len++;
    thisArray->kvarray = realloc(thisArray->kvarray, thisArray->len);
    thisArray->kvarray[len - 1] = thisPair;
    line = NULL;
  }
  free(line);
  return thisArray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  return NULL;
}
