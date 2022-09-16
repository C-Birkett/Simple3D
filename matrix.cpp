#include "matrix.h"

std::valarray<double> Matrix::row(int r){
  std::valarray<double> output(this->cols);
  output = this->data[std::slice(r*this->cols, this->cols, 1)];
  return output;
}

std::valarray<double> Matrix::col(int c){
  std::valarray<double> output(this->rows);
  output = this->data[std::slice(c, this->rows, this->cols)];
  return output;
}

Matrix Matrix::operator*(Matrix M2){
  Matrix* M1 = this;

  //std::assert("Matrix multiplication correct size", M1->cols == M2->rows);
  Matrix output(M1->rows, M2.cols);
  
  for(int r = 0; r < M1->rows; r++){
    for(int c = 0; c < M2.cols; c++){
      output(r, c) = (M1->row(r)*M2.col(c)).sum();
    }
  }
  return output;
}

std::valarray<double> Matrix::operator*(std::valarray<double> M2){
  Matrix* M1 = this;

  //std::assert("Matrix multiplication correct size", M1->cols == M2->rows);
  std::valarray<double> output(M1->rows);
  
  for(int r = 0; r < M1->rows; r++){
    output[r] = (M1->row(r)*M2).sum();
  }
  return output;
}

void Matrix::print(){
  for(int r = 0; r< this->rows; r++){
    for(int c = 0; c< this->cols; c++){
      std::cout << " " << this->data[r*cols + c];
    } 
    std::cout << std::endl;
  }
}
