#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    size_t count = 0;
    size_t sz = 0; ssize_t len = 0;
    char * line = NULL;
    char ** pointerArray = NULL;
    while ((len = getline(&line, &sz, stdin)) >= 0) {
      count++;
      pointerArray = (char **)realloc(pointerArray, (count) * sizeof(pointerArray));
      pointerArray[count - 1] = line;
      line = NULL;
    }
    free(line);
    sortData(pointerArray, count);
    for (size_t j = 0; j < count; j++) {
      printf("%s", pointerArray[j]);
      free(pointerArray[j]);
    }
    if (pointerArray != NULL) free(pointerArray);
    return EXIT_SUCCESS;
  }

  for (size_t i = 1; i < argc; i++) {
    FILE * f = NULL;
    size_t count = 0;
    f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "Failed to open the file\n");
      return EXIT_FAILURE;
    }
    size_t sz = 0; ssize_t len = 0;
    char * line = NULL;
    char ** pointerArray = NULL;
    while ((len = getline(&line, &sz, f)) >= 0) {
      count++;
      pointerArray = (char **)realloc(pointerArray, (count) * sizeof(pointerArray));
      pointerArray[count - 1] = line;
      line = NULL;
    }
    free(line);
    sortData(pointerArray, count);
    for (size_t j = 0; j < count; j++) {
      printf("%s", pointerArray[j]);
      free(pointerArray[j]);
    }
    if (pointerArray != NULL) free(pointerArray);
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the file\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
