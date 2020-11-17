
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
    if (low >= high) return low;
    int half = (low + high) / 2;
    if (half == low) return low;
    int this_ans = f->invoke(half);
    if (this_ans == 0) {
        return half;
    }
    else if (this_ans < 0) {
        if (half < high - 1) {
            return binarySearchForZero(f, half + 1, high);
        }
        else {
            return high - 1;
        }
    }
    else {
        if (half > low + 1) {
            return binarySearchForZero(f, low, half);
        }
        else {
            return low;
        }
    }
}
