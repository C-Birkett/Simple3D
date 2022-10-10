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
    Matrix(int r, int c) : data(r* c), rows(r), cols(c) {this->zeros();};
    Matrix(int s) : data(s* s), rows(s), cols(s) {this->zeros();}

    ~Matrix() {};

    //access row & col vectors within matrix using slice
    std::valarray<double> row(int r);
    std::valarray<double> col(int c);

    //access element of matrix
    double& operator()(int r, int c) {return data[r*cols + c];}
  
    //standard matrix ops
    Matrix operator*(Matrix M2);
    Matrix operator+(Matrix &M2);
    Matrix operator-(Matrix &M2);

    //matrix ops with vectors
    std::valarray<double> operator*(std::valarray<double> M2);
    
    //populate with zeros
    void zeros(){this->data = 0.0;};
    
    // print to stdout
    void print();
};
