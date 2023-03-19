#include "3D.h"

inline double Vec3D::Dot(const Vec3D& v2){
  return (v*v2.v).sum();
}

inline Vec3D Vec3D::Cross(const Vec3D& v2)
{
  return Vec3D (
    y()*v2.z() - z()*v2.y(),
    x()*v2.z() - z()*v2.x(),
    x()*v2.y() - y()*v2.x());
}

inline Vec3D Vec3D::Normalise(){
  double lensqrd = (v*v).sum();
  double invrslen = pow(lensqrd, -0.5);
  v *= invrslen;
  return *this;
}

//inline Vec3D Vec3D::Transform(const Matrix& Mat, bool normalise /* = true*/) //wrt axes
//{
//	v = Mat * v;
//  if(normalise) NormaliseW();
//	return *this;
//}

// inline gives linker err :(
Vec3D Vec3D::Transform(Matrix* Mat, bool normalise /* = true*/) //wrt axes
{
	v = (*Mat) * v;
  if(normalise) NormaliseW();
  return *this;
}

inline Vec3D Vec3D::Rotate(double x, double y, double z, bool normalise /* = true*/) //wrt axes
{
	v = S3D::rotateMatrix(x, y, z) * v;
  if(normalise) NormaliseW();
	return *this;
}

Vec3D Vec3D::Rotate(const Vec3D& pivot, double x, double y, double z, bool normalise /* = true*/) //wrt a point
{	
  Translate(-pivot, false);
	Rotate(x, y, z, false);
	Translate(pivot, normalise);
	return *this;
}

inline Vec3D Vec3D::Translate(double x, double y, double z, bool normalise /* = true*/)
{
	v = S3D::translateMatrix(x, y, z) * v;
  if(normalise) NormaliseW();
	return *this;
}

Matrix S3D::rotateXMatrix(double x)
{
  Matrix M(4);
  M(0,0) = 1;
  M(1,1) = cos(x);
  M(1,2) = -sin(x);
  M(2,1) = sin(x);
  M(2,2) = cos(x);
  M(3, 3) = 1;
  return M;
}

Matrix S3D::rotateYMatrix(double y){
  Matrix M(4);
  M(0,0) = cos(y);
  M(0,2) = sin(y);
  M(1,1) = 1;
  M(2,0) = -sin(y);
  M(2,2) = cos(y);
  M(3, 3) = 1;
  return M;
}

Matrix S3D::rotateZMatrix(double z){
  Matrix M(4);
  M(0,0) = cos(z);
  M(0,1) = -sin(z);
  M(1,0) = sin(z);
  M(1,1) = cos(z);
  M(2,2) = 1;
  M(3, 3) = 1;
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
