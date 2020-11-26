#ifndef _STRING_HASHER_H_
#define _STRING_HASHER_H_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

class StringHasher {
private:
    const int multiplyBy;
public:
    StringHasher() : multiplyBy(29) { }
    StringHasher(int mul) : multiplyBy(mul) { }
    unsigned operator() (const std::string & str) {
        unsigned ans = 0;
        for (std::string::const_iterator it = str.begin(); 
            it != str.end();
            ++it) {
            ans = ans * multiplyBy + *it;
        }
        return ans;
    }
};

#endif
