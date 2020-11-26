#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <map>

#include "StringHasher.h"

int main(int argc, char ** argv) {
    int key = atoi(argv[1]);
    std::string str;
    StringHasher hash(key);
    std::map<unsigned, unsigned> hashMap;
    while (std::getline(std::cin, str)) {
        unsigned hashResult = hash(str);
        if (hashMap.find(hashResult) != hashMap.end()) {
            hashMap[hashResult]++;
        }
        else {
            hashMap[hashResult] = 0;
        }
    }
    unsigned maxCol = 0;
    std::map<unsigned, unsigned>::iterator it = hashMap.begin();
    while (it != hashMap.end()) {
        std::cout << it->first << ": " << it->second << std::endl;
        ++it;
        if (it->second > maxCol) maxCol = it->second;
    }
    std::cout << "Max collision: " << maxCol << std::endl;
    return EXIT_SUCCESS;
}