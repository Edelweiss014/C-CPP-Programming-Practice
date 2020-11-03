#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template <typename T>
class Matrix {
private:
    int numRows;
    int numColumns;
    std::vector<T> ** rows;
public:
    Matrix() : numRows(0), numColumns(0), rows(NULL) {}
    Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> * [r]) {
        for (int i = 0; i < r; i++) {
            rows[i] = new std::vector<T> (c);
        }
    }
    Matrix(const Matrix & rhs) : numRows(rhs.getRows()), 
                            numColumns(rhs.getColumns()), 
                            rows (new std::vector<T> * [rhs.getRows()]) {
        for (int i = 0; i < numRows; i++) {
            rows[i] = new std::vector<T> (rhs[i]);
        }
    }
    ~Matrix() {
        for (int i = 0; i < numRows; i++) {
            delete rows[i];
        }
        delete[] rows;
    }

    Matrix<T> & operator=(const Matrix & rhs) {
        if (this != &rhs) {
            std::vector<T> ** temp = new std::vector<T> * [rhs.getRows()];
            for (int i = 0; i < rhs.getRows(); i++) {
                temp[i] = new std::vector<T> (rhs[i]);
            }
            for (int i = 0; i < numRows; i++) {
                delete rows[i];
            }
            delete[] rows;
            rows = temp;
            numRows = rhs.getRows();
            numColumns = rhs.getColumns();
        }
        return *this;
    }

    int getRows() const {
        return numRows;
    }
    int getColumns() const {
        return numColumns;
    }
    const std::vector<T> & operator[](int index) const {
        assert(index >= 0 && index < numRows);
        return *(this->rows[index]);
    }

    std::vector<T> & operator[](int index) {
        assert(index >= 0 && index < numRows);
        return *(this->rows[index]);
    }

    bool operator==(const Matrix<T> & rhs) const {
        if (numRows != rhs.getRows() || numColumns != rhs.getColumns()) {
            return false;
        }
        for (int i = 0; i < numRows; i++) {
            typename std::vector<T>::const_iterator it1 = (*this)[i].begin();
            typename std::vector<T>::const_iterator it2 = rhs[i].begin();
            while (it1 != (*this)[i].end()) {
                if (*it1 != *it2) {
                    return false;
                }
                ++it1;
                ++it2;
            }
        }
        return true;
    }

    Matrix<T> operator+(const Matrix<T> & rhs) const {
        assert(numRows == rhs.getRows() && numColumns == rhs.getColumns());
        Matrix ans(*this);
        for (int i = 0; i < numRows; i++) {
            typename std::vector<T>::const_iterator it1 = (*this)[i].begin();
            typename std::vector<T>::const_iterator it2 = rhs[i].begin();
            typename std::vector<T>::iterator it3 = ans[i].begin();
            while (it1 != (*this)[i].end()) {
                *it3 += *it2;
                ++it1;
                ++it2;
                ++it3;
            }
        }
        return ans;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
    if (rhs.size() == 0) {
        s << "{}";
        return s;
    }
    s << "{";
    typename std::vector<T>::const_iterator it = rhs.begin();
    while (it != rhs.end() - 1) {
        s << *it << ", ";
        ++it;
    }
    s << *it << "}";
    return s;
}

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
    if (rhs.getRows() == 0) {
        s << "[  ]";
        return s;
    }
    s << "[ ";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
        s << rhs[i] << "," << std::endl;
    }

    s << rhs[rhs.getRows() - 1] << " ]";
    return s;
}

#endif
