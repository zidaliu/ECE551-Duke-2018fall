#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows, numColums;
  vector<vector<T> > rows;

 public:
  Matrix() : numRows(0), numColums(0) {}

  Matrix(int r, int c) : numRows(r), numColums(c), rows(r) {
    for (int i = 0; i < numRows; i++) {
      this->rows[i].resize(c);
    }
  }

  Matrix(const Matrix<T> & m) : numRows(m.numRows), numColums(m.numColums), rows(m.rows) {}
  int getRows() const { return numRows; }
  int getColumns() const { return numColums; }
  vector<T> & operator[](int index) {
    assert(0 <= index && index < numRows);
    return rows[index];
  }
  const vector<T> & operator[](int index) const {
    assert(0 <= index && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows || numColums != rhs.numColums) {
      return false;
    }
    if (rows == rhs.rows) {
      return true;
    }
    else
      return false;
  }

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColums = rhs.numColums;
    rows = rhs.rows;
    return *this;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColums == rhs.numColums);
    Matrix<T> ans(numRows, numColums);
    typename vector<vector<T> >::iterator z;
    typename vector<vector<T> >::const_iterator x = rows.begin(), y = rhs.rows.begin();
    for (z = ans.rows.begin(); z != ans.rows.end(); ++z, ++x, ++y) {
      typename vector<T>::iterator zz = z->begin();
      typename vector<T>::const_iterator xx = x->begin(), yy = y->begin();
      while (zz != z->end()) {
        *zz++ = *xx++ + *yy++;
      }
    }
    return ans;
  }

  template<typename U>
  friend ostream & operator<<(std::ostream & s, const Matrix<U> & m);
};

template<typename T>
ostream & operator<<(std::ostream & s, const Matrix<T> & m) {
  s << "[ ";
  for (int i = 0; i < m.numRows; i++) {
    if (i == 0) {
      s << "{";
    }
    else {
      s << ",\n{";
    }
    for (size_t j = 0; j < m[i].size(); j++) {
      if (j == 0) {
        s << m[i][j];
      }
      else {
        s << ", " << m[i][j];
      }
    }
    s << "}";
  }
  s << " ]";
  return s;
}
#endif
