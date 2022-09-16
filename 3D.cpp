#include "3D.h"

Matrix S3D::rotateX(double x){
  Matrix M(3);
  M(0,0) = 1;
  M(1,1) = cos(x);
  M(1,2) = -sin(x);
  M(2,1) = sin(x);
  M(2,2) = cos(x);
  return M;
}

Matrix S3D::rotateY(double y){
  Matrix M(3);
  M(0,0) = cos(y);
  M(0,2) = sin(y);
  M(1,1) = 1;
  M(2,0) = -sin(y);
  M(2,2) = cos(y);
  return M;
}

Matrix S3D::rotateZ(double z){
  Matrix M(3);
  M(0,0) = cos(z);
  M(0,1) = -sin(z);
  M(1,0) = sin(z);
  M(1,1) = cos(z);
  M(2,2) = 1;
  return M;
}

Matrix S3D::rotate(double x, double y, double z){
  return rotateX(x)*(rotateY(y)*rotateZ(z));
}
