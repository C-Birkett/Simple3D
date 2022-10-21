#include "3D.h"

Vec3D Vec3D::cross(Vec3D v2){
  auto v1 = *this;

  double x = v1.y()*v2.z() - v1.z()*v2.y();
  double y = v1.x()*v2.z() - v1.z()*v2.x();
  double z = v1.x()*v2.y() - v1.y()*v2.x();

  Vec3D out(x,y,z);
  return out;
}

double Vec3D::dot(Vec3D v2){
  auto v1 = *this;
  double out = (v1.v*v2.v).sum();
  return out;
}

Vec3D Vec3D::normalise(){
  double lensqrd = (this->v*this->v).sum();
  double invrslen = 1.0/pow(lensqrd, 0.5);
  this->v *= invrslen;
  return *this;
}

Vec3D Vec3D::rotate(double x, double y, double z) {//wrt axes
	Vec3D out;
	out.v = S3D::rotateMatrix(x, y, z) * this->v;
	this->v = out.v;
	return out;
}

Vec3D Vec3D::rotate(Vec3D pivot, double x, double y, double z) {//wrt a point
	this->translate(-pivot);
	this->rotate(x, y, z);
	this->translate(pivot);
	return *this;
}

Vec3D Vec3D::translate(double x, double y, double z) {
	Matrix T = S3D::translateMatrix(x, y, z);

	/*
	this->v = T * this->v;
	this->GenToV3D();
	*/

	std::valarray<double> gen = this->generalise();

	gen = T * gen;
	this->GenToV3D(gen);

	return *this;
}

Matrix S3D::rotateXMatrix(double x){
  Matrix M(3);
  M(0,0) = 1;
  M(1,1) = cos(x);
  M(1,2) = -sin(x);
  M(2,1) = sin(x);
  M(2,2) = cos(x);
  return M;
}

Matrix S3D::rotateYMatrix(double y){
  Matrix M(3);
  M(0,0) = cos(y);
  M(0,2) = sin(y);
  M(1,1) = 1;
  M(2,0) = -sin(y);
  M(2,2) = cos(y);
  return M;
}

Matrix S3D::rotateZMatrix(double z){
  Matrix M(3);
  M(0,0) = cos(z);
  M(0,1) = -sin(z);
  M(1,0) = sin(z);
  M(1,1) = cos(z);
  M(2,2) = 1;
  return M;
}

Matrix S3D::rotateMatrix(double x, double y, double z){
  return rotateXMatrix(x)*(rotateYMatrix(y)*rotateZMatrix(z));
}

Matrix S3D::translateMatrix(double x, double y, double z) {
	Matrix M(4);

	M(0, 0) = 1;
	M(1, 1) = 1;
	M(2, 2) = 1;
	M(3, 3) = 1;

	M(3, 0) = x;
	M(3, 1) = y;
	M(3, 2) = z;

	return M;
}

Matrix S3D::translateMatrix(Vec3D v) {
	return S3D::translateMatrix(v.x(), v.y(), v.z());
}