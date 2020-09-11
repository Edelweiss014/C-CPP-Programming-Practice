
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
    if (power(x, y) != expected_ans) exit(EXIT_FAILURE);
}

int main(){
    unsigned myPower = 0;
    unsigned x = 0; unsigned y = 0;

    run_check(0, 0, 1);

    run_check(-1, 0, 1);

    run_check(-1, -1, -1);

    run_check(-1, 10, 1);

    run_check(2, 5, 32);

    run_check(2, 0.5, sqrt(2));

    run_check(1000, 3, 1000 * 1000 * 1000);
    
    return EXIT_SUCCESS; 
}