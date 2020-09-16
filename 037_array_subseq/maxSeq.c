#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
    if (array == NULL) return 0;
    if (n == 0) return 0;
    size_t longestLen = 1;
    size_t accumulateLen = 1;
    int previousNum = 0;
    int currentNum = 0;

    for (int i = 1; i < n; i++) {
        previousNum = array[i - 1];
        currentNum = array[i];
        if (currentNum > previousNum) {
            accumulateLen++;
        }
        else {
            if (accumulateLen > longestLen) longestLen = accumulateLen;
            accumulateLen = 1;
        }
    }
    return longestLen;
}