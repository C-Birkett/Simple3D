#pragma once

#include <valarray>
#include <cmath>
#include <iostream>

class Matrix{
  private:
    std::valarray<double> data;
    int rows;
    int cols;

  public:

    //can have square mats
    Matrix(int nRows, int nCols) : 
    data(nRows* nCols), rows(nRows), cols(nCols)
    {
      zeros();
    }

    Matrix(int size) :
    data(size * size), rows(size), cols(size) 
    {
      zeros();
    }

    ~Matrix() {};

    //access row & col vectors within matrix using slice
    std::valarray<double> row(int r) const;
    std::valarray<double> col(int c) const;

    //access element of matrix
    double& operator()(int r, int c) {return data[r*cols + c];}
  
    //standard matrix ops
    Matrix operator*(const Matrix& M2) const;
    Matrix operator+(Matrix &M2);
    Matrix operator-(Matrix &M2);

    //matrix ops with vectors
    std::valarray<double> operator*(std::valarray<double> M2) const;
    //std::valarray<double> operator*(Vec3D v) {
    //    return *this * v.v;
    //}
    
    //populate with zeros
    void zeros(){data = 0.0;};
    
    // print to stdout
    void print();
};

inline std::valarray<double> Matrix::row(int row) const{
  return this->data[std::slice(row*this->cols, this->cols, 1)];
}

inline std::valarray<double> Matrix::col(int col) const {
  return this->data[std::slice(col, this->rows, this->cols)];
}
