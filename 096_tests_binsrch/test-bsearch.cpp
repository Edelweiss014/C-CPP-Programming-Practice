#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn() {}
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
                                                                    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

class LinearFunc : public CountedIntFn {
public:
    virtual int invoke (int arg) {
      return arg;
    }
};

class Log2Func : public CountedIntFn {
public:
    virtual int invoke (int arg) {
      if (arg <= 0) return -100000;
      return log(arg) / log(2);
    }
};

class SquareFuntRight : public CountedIntFn {
public:
    virtual int invoke (int arg) {
      return arg * (arg - 2.5) - 1;
    }
};

class UniformNegFunc : public CountedIntFn {
public:
    virtual int invoke (int arg) {
      return -10;
    }
};

class UniformPosFunc : public CountedIntFn {
public:
    virtual int invoke (int arg) {
      return 10;
    }
};

class SinFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
      return 10000000 * (sin(arg/100000.0) - 0.5);
    }
};

void check(Function<int,int> * f, int low, int high, int expected_ans, const char * mesg) {
    int max_num = 0;
    if (high > low) {
        max_num = log(high - low) / log(2) + 1;
    }
    else {
        max_num = 1;
    }
    CountedIntFn * c1 = new CountedIntFn (max_num, f, mesg);
    int actual_ans = binarySearchForZero(c1, low, high);
    if (actual_ans != expected_ans) {
        fprintf(stderr, "Wrong answer for %s\n", mesg);
        exit(EXIT_FAILURE);
    }
    return;
}

int main() {
    LinearFunc f1;
    check(&f1, -5, 5, 0, "LINEAR");
    check(&f1, -5, -5, -5, "LINEAR");
    check(&f1, 1, 1, 1, "LINEAR");
    check(&f1, 1, 100, 1, "LINEAR");
    
    Log2Func f2;
    check(&f2, -10, 10, 1, "LOG");
    check(&f2, 5, 100, 5, "LOG");
    check(&f2, -100000000, 100, 1, "LOG");

    SquareFuntRight f3;
    check(&f3, 2, 10, 3, "SQUARE");

    UniformNegFunc f4;
    check(&f4, -10, 10, 9, "UNIFORM_NEG");
    check(&f4, -100, -10, -11, "UNIFORM_NEG");

    UniformPosFunc f5;
    check(&f5, -10, 10, -10, "UNIFORM_POS");

    SinFunction f6;
    check(&f6, 0, 150000, 52359, "SIN");
    
    return EXIT_SUCCESS;
}