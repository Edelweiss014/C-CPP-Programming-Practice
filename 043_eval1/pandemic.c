#include "pandemic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

// Define the value of the largest population
#define ULLONG_MAX MAX_POPULATION

country_t parseLine(char * line) {
  country_t ans;
  size_t lineLength = strlen(line);
  size_t i = 0; size_t j = 0;

  // use "num" to store the string form of the population
  char num[65] = {'\0'};

  // Get country name by iterating and add '\0' after it
  for (i = 0; i < lineLength; i++) {
    if (line[i] == ',') {
      (ans.name)[i] = '\0';
      break;
    }
    (ans.name)[i] = line[i];
  }

  // If we reach the end of the string without getting a 
  //    comma, we should return with a failure status.
  if (line[i] == '\0') {
    fprintf(stderr, "Wrong country format - population not available\n");
    exit(EXIT_FAILURE);
  }

  // Get population by iterating. When encounter a 
  //    non-digit char or the string is out of range
  //    (more than 64 digits), we should return with
  //    a failure status. We then end the string with
  //    '\0'.
  i = i + 1;
  for (; i < lineLength - 1; i++) {
    if (!isdigit(line[i])) {
      fprintf(stderr, "Wrong country format - population is not a number\n");
      exit(EXIT_FAILURE);
    }
    // We use j as the index for population
    if (j >= 64) {
      // Stop the program directly when the string is too long
      fprintf(stderr, "Wrong country format - population out of range\n");
      exit(EXIT_FAILURE);
    }
    num[j] = line[i];
    j = j + 1;
  }
  num[j] = '\0';
  // Set errno to 0 to check overflow
  errno = 0;
  (ans.population) = strtoull(num, NULL, 10);
  if (errno != 0) {
     fprintf(stderr, "Wrong country format - population out of range\n");
     exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  size_t j = 0;
  int k = 0;
  double runAvg = 0;
  // The iterator i is the middle element
  for (size_t i = 3; i < n_days - 3; i++) {
    // Set runAvg of a certain day to 0
    runAvg = 0;
    for (k = -3; k < 4; k++) {
      runAvg += data[i + k];
    }
    avg[j] = runAvg / 7;
    j++;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // Variable "thisCum" calculates the cumulative number
  //    that should be placed into the array each time
  double thisCum = 0;
  for (size_t i = 0; i < n_days; i++) {
    thisCum += (double)data[i] * 100000 / pop;
    cum[i] = thisCum;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned maxCases = 0;
  size_t rowNum = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > maxCases) {
        maxCases = data[i][j];
        rowNum = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", (countries[rowNum]).name, maxCases);
}
