#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * newCounts = malloc(sizeof(* newCounts));
  newCounts->numElements = 0;
  newCounts->unknownCount = 0;
  newCounts->countList = NULL;
  return newCounts;
}
void addCount(counts_t * c, const char * name) {
  // If the name is NULL
  if (name == NULL) {
    c->unknownCount++;
    return;
  }
  // If the name is not NULL and appeared before, increment it
  for (size_t i = 0; i < c->numElements; i++) {
    if (strcmp(c->countList[i]->name, name) == 0) {
      c->countList[i]->num++;
      return;
    }
  }
  // If the name is not NULL and did not appear before, create
  //    a new place for it
  c->countList = realloc(c->countList, (c->numElements + 1) * sizeof(* (c->countList)));
  one_count_t * newElement = malloc(sizeof(* newElement));
  newElement->name = malloc((strlen(name) + 1) * sizeof(* name));
  strcpy(newElement->name, name);
  newElement->name[strlen(name)] = '\0';
  newElement->num = 1;
  c->countList[c->numElements] = newElement;
  c->numElements++;
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  if (outFile == NULL) {
    fprintf(stderr, "Wrong file stream\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->numElements; i++) {
    fprintf(outFile, "%s: %ld\n", c->countList[i]->name, c->countList[i]->num);
  }
  if (c->unknownCount != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknownCount);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->numElements; i++) {
    free(c->countList[i]->name);
    free(c->countList[i]);
  }
  free(c->countList);
  free(c);
  return;
}
