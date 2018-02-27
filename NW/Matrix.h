#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <exception>
#include <iomanip> // setw
#include <sstream> // ostringstream

class IndexOutOfRangeException : public std::exception {
  std::string msg;
 public:

  virtual const char* what() const throw() { return msg.c_str(); }

  IndexOutOfRangeException(std::string msg, int idx) {
    std::ostringstream oss;
    oss << msg << " " << idx;
    this->msg = oss.str();
  }
  ~IndexOutOfRangeException() throw() { }
};

// 1-based access!!
template <class N>
class Matrix {
  N* elems;
  int rows, cols;

  void check(int r, int c) {
    if (r <= 0 || r > rows) 
      throw IndexOutOfRangeException("Invalid row:", r);
    if (c <= 0 || c > cols) 
      throw IndexOutOfRangeException("Invalid column:", c);
  }
  
 public:

  void print(std::string rowlabel, std::string collabel);

  const N& e(int r, int c) const {
    check(r,c);
    return elems[(r-1)*cols + c-1];
  }
  N& e(int r, int c) {
    check(r,c);
    return elems[(r-1)*cols + c-1];
  }
  
  Matrix(int rows, int cols) {
    elems = new N[rows*cols];
    this->rows = rows;
    this->cols = cols;
  }
  
  virtual ~Matrix() {
    delete[] elems;
  }
};

template <class N>
void Matrix<N>::print(std::string rowlabel, std::string collabel) 
{
  if ((int)rowlabel.length() != cols)
    throw IndexOutOfRangeException("Invalid rowlabel: length=", rowlabel.length());
  if ((int)collabel.length() != rows)
    throw IndexOutOfRangeException("Invalid collabel: length=", collabel.length());
  
  // find longest string-rep of element
  int max_length = 0;
  std::ostringstream oss;
  for (int i = 0; i < rows*cols; i++) {
    oss.str("");
    oss << elems[i];
    max_length = std::max(max_length, (int)oss.str().length());
  }

  // print matrix
  std::cout << std::setw(max_length+1) << " ";
  for (int c = 1; c <= cols; c++) {
    std::cout << " ";
    std::cout << std::setw(max_length+1) << rowlabel.at(c-1);
  }
  std::cout << std::endl;
  for (int r = 1; r <= rows; r++) {
    std::cout << std::setw(max_length+1) << collabel.at(r-1);
    for (int c = 1; c <= cols; c++) {
      std::cout << " ";
      std::cout << std::setw(max_length+1) << e(r,c);
    }
    std::cout << std::endl;
  }
}

#endif
