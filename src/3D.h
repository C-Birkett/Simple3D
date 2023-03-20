#pragma once

//#include <cmath>
#include <valarray>
#include <vector>
#include <iostream>
#include <cassert>

#include "matrix.h"

// generalised vectors for linear transformations
class Vec3D{
  public:
  // 0 by default
  std::valarray<double> v = {0,0,0,1};
  
  // get and set
  double x(void) const {return v[0];}
  double y(void) const {return v[1];}
  double z(void) const {return v[2];}
  double w(void) const {return v[3];}

  void Setx(double xin) {v[0] = xin;}
  void Sety(double yin) {v[1] = yin;}
  void Setz(double zin) {v[2] = zin;}
  void Setw(double win) {v[3] = win;}

  Vec3D() {};

  // copy constructors
  Vec3D(const std::valarray<double>& val)
    : v(val)
  {}
  
  Vec3D(const Vec3D& vec) 
    : v(vec.v)
  {}

  Vec3D(double xin, double yin, double zin)
    : v({xin,yin,zin,1})
  {}

  Vec3D(double xin, double yin, double zin, double win)
    : v({xin,yin,zin,win}) 
  {}

  ~Vec3D(){};
  
  Vec3D& operator=(const Vec3D& vec)
  {
    //double prevW = w();
    v = vec.v;
    //Setw(prevW);
    return *this;
  }

  //cross and dot product
  double Dot(const Vec3D& v2);
  Vec3D Cross(const Vec3D& v2);

  //generalised vector
  std::valarray<double> Generalise() {
      std::valarray<double> v3Dgen(0.0, 4);
      for (int i = 0; i < 3; i++) {
          v3Dgen[i] = v[i];
      }
      v3Dgen[3] = w();  //w = 1 by default
      return v3Dgen;
  }
  
  Vec3D Normalise();
  
  Vec3D NormaliseW()
  {
    v = v / w();
    Setw(1);
    return *this;
  }

  Vec3D GenToV3D(std::valarray<double> gen) {
      //normalise wrt w
      Setw(gen[3]);
      gen = gen / w();
      for (int i = 0; i < 3; i++) {
          this->v[i] = gen[i];
      }
      Setw(1);
      return *this;
  }

  //linear transformations
  //Vec3D Transform(const Matrix& Mat, bool normalise = true);
  Vec3D Transform(Matrix* Mat, bool normalise = true);

  Vec3D Rotate(double x, double y, double z, bool normalise = true); //wrt axes
  Vec3D Rotate(const Vec3D& pivot,  double x, double y, double z, bool normalise = true); //wrt a point
  const Vec3D Rotate(const Vec3D& pivot, Vec3D rot, bool normalise = true) 
  {
    return Rotate(pivot, rot.x(), rot.y(), rot.z(), normalise);
  }

  Vec3D Translate(double x, double y, double z, bool normalise = true);
  const Vec3D Translate(const Vec3D& vec, bool normalise = true) 
  {
    return Translate(vec.x(), vec.y() , vec.z(), normalise);
  }

  Vec3D operator-(const Vec3D v2){
    return Vec3D(v - v2.v);
  }

  Vec3D operator-() const 
  {
      return Vec3D(-v);
      print();
  }

  void operator-=(Vec3D v2) 
  {
      auto& v1 = *this;
      v1.v = v1.v - v2.v;
  }

  Vec3D operator+(Vec3D v2){
    auto &v1 = *this;
    Vec3D out;
    out.v = v1.v + v2.v;
    return out;
  }

  void operator+=(Vec3D v2) {
      auto& v1 = *this;
      v1.v = v1.v + v2.v;
  }

  Vec3D operator*(Vec3D v2){
    auto &v1 = *this;
    Vec3D out;
    out.v = v1.v * v2.v;
    return out;
  }

  void operator*=(Vec3D v2) {
      auto &v1 = *this;
      v1.v = v1.v * v2.v;
  }

  Vec3D operator*(double lambda) {
      auto &v1 = *this;
      Vec3D out;
      out.v = v1.v * lambda;
      return out;
  }

  Vec3D operator*(Matrix M) {
      auto &v1 = *this;
      Vec3D out;
      out.v = M * v1.v;
      return out;
  }
  
  bool generalisedEquals(const Vec3D& v2)
    {
      return std::equal(std::begin(v), std::end(v), std::begin(v2.v));
    }

  bool operator==(const Vec3D& v2){
    return x() == v2.x()
        && y() == v2.y()
        && z() == v2.z();
  }

  bool operator!=(Vec3D v2){
    return !(*this==v2);
  }

  void print(bool wantW = false) const
  {
    std::cout << v[0]<<" "<<v[1]<<" "<<v[2];
    if (wantW) std::cout << " " << v[3];
    std::cout << std::endl;
  }
};

//space3D
namespace S3D 
{
  //2D polygon in 3D space
  
  typedef std::vector<Vec3D*> Polygon;
  inline void PrintPoly(const Polygon& poly, bool wantW = false)
  {
    for (auto vert : poly)
      {
        vert->print();
      }
      std::cout<<std::endl;
  }
  
  //xyz in radians
  Matrix rotateXMatrix(double x);
  Matrix rotateYMatrix(double y);
  Matrix rotateZMatrix(double z);
  Matrix rotateMatrix(double x, double y, double z);

  Matrix translateMatrix(double x, double y, double z);
  inline Matrix translateMatrix(const Vec3D& v) {return translateMatrix(v.x(), v.y(), v.z());}
}