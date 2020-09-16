
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

size_t maxSeq(int * array, size_t n);


void run_check(int * array, size_t n, size_t expected_ans) {
    if (maxSeq(array, n) != expected_ans) exit(EXIT_FAILURE);
    return;
}

int main() {
    int arrayTest1[] = {1, -2, -1, 0, 1, 2, 4, -5};
    run_check(arrayTest1, 8, 6);

    int arrayTest2[] = {};
    run_check(arrayTest2, 0, 0);

    int arrayTest3[] = {-1};
    run_check(arrayTest3, 1, 1);

    int arrayTest4[] = {-2, -3, -4};
    run_check(arrayTest4, 3, 1);

    int arrayTest5[] = {1, 2, -1, 3, 5, 7, -2, -4, 6, 9};
    run_check(arrayTest5, 10, 4);

    int arrayTest6[] = {0, 0, 0, 0, 0};
    run_check(arrayTest6, 5, 1);

    
    return EXIT_SUCCESS; 
}
