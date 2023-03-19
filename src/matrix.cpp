#include "matrix.h"
#include <cassert>

Matrix Matrix::operator*(const Matrix& M2) const{
  static const Matrix* M1 = this;

  assert(M1->cols == M2.rows);
  Matrix result(M1->rows, M2.cols);
  
  for(int rw = 0; rw < M1->rows; rw++){
    for(int cl = 0; cl < M2.cols; cl++){
      result(rw, cl) = (M1->row(rw)*M2.col(cl)).sum();
    }
  }
  return result;
}

std::valarray<double> Matrix::operator*(std::valarray<double> M2) const{
  std::valarray<double> output(M2.size());
  
  for(int c = 0; c < M2.size(); c++){
    output[c] = (col(c)*M2).sum();
  }
  return output;
}

void Matrix::print(){
  for(int r = 0; r< this->rows; r++){
    for(int c = 0; c< this->cols; c++){
        std::cout << " " << this->data[static_cast<size_t>(r * cols + c)];
    } 
    std::cout << std::endl;
  }
}
