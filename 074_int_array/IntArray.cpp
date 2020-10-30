#include "IntArray.h"
#include <assert.h>
#include <iostream>

IntArray::IntArray() : data(NULL), numElements(0) {

}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {

}

IntArray::IntArray(const IntArray & rhs)  {
    numElements = rhs.size();
    data = new int[rhs.size()];
    for (int i = 0; i < rhs.size(); i++) {
        data[i] = rhs.data[i];
    }
}
IntArray::~IntArray() {
    delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    delete[] data;
    numElements = rhs.size();
    data = new int[numElements];
    for (int i = 0; i < numElements; i++) {
        data[i] = rhs.data[i];
    }
    return *this;
}
const int & IntArray::operator[](int index) const {
    assert(index >= 0 && index < numElements);
    return data[index];
}
int & IntArray::operator[](int index) {
    assert(index >= 0 && index < numElements);
    return data[index];
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    for (int i = 0; i < numElements; i++) {
        if (data[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    std::cout << "{";
    for (int i = 0; i < rhs.size(); i++) {
        std::cout << rhs[i] << " ";
    }
    std::cout << "}" << std::endl;
    return s;
}
