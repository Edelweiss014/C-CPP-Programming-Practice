#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  size_t inputLen = strlen(inputName);
  size_t nameLen = inputLen + 7;
  char * temp = malloc((nameLen + 1) * sizeof(*temp));
  strncpy(temp, inputName, strlen(inputName));
  temp[inputLen] = '.';
  temp[inputLen + 1] = 'c';
  temp[inputLen + 2] = 'o';
  temp[inputLen + 3] = 'u';
  temp[inputLen + 4] = 'n';
  temp[inputLen + 5] = 't';
  temp[inputLen + 6] = 's';
  temp[inputLen + 7] = '\0';
  return temp;
}
