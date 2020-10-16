#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * readPair(char * line) {
  kvpair_t * pair = malloc(sizeof(* pair));
  char * equPosition = strchr(line, '=');
  if (equPosition == NULL) {
    fprintf(stderr, "Invalid key-value pair\n");
    exit(EXIT_FAILURE);
  }
  size_t i = 0;
  pair->key = malloc((equPosition - line + 1) * sizeof(*(pair->key)));
  for (i = 0; i < equPosition - line; i++) {
    pair->key[i] = line[i];
  }
  pair->key[i] = '\0';
  size_t j = 1;
  char * endOfStr = strchr(line, '\n');
  pair->value = malloc((endOfStr - equPosition) * sizeof(*(pair->key)));
  for (j = 0; j < endOfStr - equPosition - 1; j++) {
    pair->value[j] = equPosition[j + 1];
  }
  pair->value[j] = '\0';
  return pair;
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
  thisArray->kvarray = malloc(sizeof(*(thisArray->kvarray)));
  while ((len = getline(&line, &sz, f)) >= 0) {
    kvpair_t * thisPair = readPair(line);
    thisArray->len++;
    thisArray->kvarray = realloc(thisArray->kvarray, (thisArray->len) * sizeof(*(thisArray->kvarray)));
    thisArray->kvarray[thisArray->len - 1] = thisPair;
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file\n");
    exit(EXIT_FAILURE);
  }
  free(line);
  return thisArray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++) {
    free(pairs->kvarray[i]->key);
    free(pairs->kvarray[i]->value);
    free(pairs->kvarray[i]);
  }
  free(pairs->kvarray);
  free(pairs);
  return;
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i]->key, pairs->kvarray[i]->value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp(pairs->kvarray[i]->key, key) == 0) {
      return pairs->kvarray[i]->value;
    }
  }
  return NULL;
}
