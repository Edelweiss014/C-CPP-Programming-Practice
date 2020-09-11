#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y){
    if (x == 0){
        if (y == 0) return 1;
        else return 0;
    }
    else if (x == 1) return 1;
    else if (y == 0) return 1;
    else if (y == 1) return x;
    return x * power(x, y - 1);
}
