#include "pandemic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

country_t parseLine(char * line) {
  country_t ans;
  size_t lineLength = strlen(line);
  size_t i = 0;

  // Search ',' in the string. If there is no ',' or the
  //    country name is too long, we should exit with a
  //    failure status. 
  const char * commaPointer = strchr(line, ',');
  if (commaPointer == NULL) {
    fprintf(stderr, "Wrong country format - cannot find a comma\n");
    exit(EXIT_FAILURE);
  }
  if (commaPointer - line > 63) {
    fprintf(stderr, "Wrong country format - country name too long\n");
    exit(EXIT_FAILURE);
  }

  // Get country name by iterating and add '\0' after it
  for (i = 0; i < lineLength; i++) {
    if (line[i] == ',') {
      (ans.name)[i] = '\0';
      break;
    }
    (ans.name)[i] = line[i];
  }
  
  // If the population includes characters that are not 
  //    digits, we should exit with a failure status
  i = i + 1;
  for (; i < lineLength - 1; i++) {
    if (line[i] == '\0' || line[i] == '\n') break;
    else if (line[i] < 48 || line[i] > 57) {
      fprintf(stderr, "Wrong country format - population is not a number\n");
      exit(EXIT_FAILURE);
    }
  }

  // If we reach the end of the string without getting a 
  //    comma, we should return with a failure status.
  if (line[i] == '\0') {
    fprintf(stderr, "Wrong country format - population not available\n");
    exit(EXIT_FAILURE);
  }

  errno = 0;
  (ans.population) = strtoull(commaPointer + 1, NULL, 10);
  // Use errno to 0 to check overflow
  if (errno == ERANGE) {
    fprintf(stderr, "Wrong country format - population out of range\n");
    exit(EXIT_FAILURE);
  }
  // Exit with a failure status when there is no population
  if (ans.population == 0) {
    fprintf(stderr, "Wrong country format - population not available\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if (n_days <= 6 || data == NULL) {
    fprintf(stderr, "Avg is unavailable\n");
  }
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