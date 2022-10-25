#pragma once

#include <cmath>
#include <valarray>
#include <vector>
#include <iostream>

#include "matrix.h"

// generalised vectors for linear transformations
class Vec3D{
  public:
  // 0 by default
  std::valarray<double> v = {0,0,0};
  int w = 1;

  Vec3D(){}
  Vec3D(double x, double y, double z){
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }

  ~Vec3D(){};

  //cross and dot product
  Vec3D cross(Vec3D v2);

  double dot(Vec3D v2);

  Vec3D normalise();

  //access individual coords
  double x(){return v[0];}
  double y(){return v[1];}
  double z(){return v[2];}
  //double w() { return w; }

  void setX(double x) { v[0] = x; }
  void setY(double y) { v[1] = y; }
  void setZ(double z) { v[2] = z; }
  //void setW(double newW) { w = newW; }

  //generalised vector
  std::valarray<double> generalise() {
      std::valarray<double> v3Dgen(0.0, 4);
      for (int i = 0; i < 3; i++) {
          v3Dgen[i] = this->v[i];
      }
      v3Dgen[3] = w;  //w = 1 by default
      return v3Dgen;
  }

  //normalise generalised back to Vec3D
  /*
  Vec3D GenToV3D() {
      //normalise wrt w
      double w = this->v[3];
      this->v = this->v / w;
      return *this;
  }
  */

  Vec3D GenToV3D(std::valarray<double> gen) {
      //normalise wrt w
      this->w = gen[3];
      gen = gen / w;
      for (int i = 0; i < 3; i++) {
          this->v[i] = gen[i];
      }
      this->w = 1;
      return *this;
  }

  //linear transformations
  Vec3D rotate(double x, double y, double z); //wrt axes

  Vec3D rotate(Vec3D pivot,  double x, double y, double z); //wrt a point
  Vec3D rotate(Vec3D pivot, Vec3D rot) {return this->rotate(pivot, rot.x(), rot.y(), rot.z());}

  Vec3D translate(double x, double y, double z);
  Vec3D translate(Vec3D v) {return this->translate(v.x(), v.y(), v.z());}

  Vec3D operator-(Vec3D v2){
    auto &v1 = *this;
    Vec3D out;
    out.v = v1.v - v2.v;
    return out;
  }

  Vec3D operator-() {
      auto &v1 = *this;
      Vec3D v2; //zeros
      return v2-v1;
  }

  void operator-=(Vec3D v2) {
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

  bool operator==(Vec3D v2){
    auto &v1 = *this;
    //return v1.v == v2.v;
    if((v1.x() != v2.x())||(v1.y() != v2.y())||(v1.z() != v2.z())){
      return false;
    }else{
      return true;
    }
  }

  bool operator!=(Vec3D v2){
    auto &v1 = *this;
    return !(v1==v2);
  }

  void print(){
    std::cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;}
};


//space3D
namespace S3D {

  //2D polygon in 3D space
  struct Polygon{
    std::vector<Vec3D*> verts;
    int nverts;
  };
  
  //xyz in radians
  Matrix rotateXMatrix(double x);
  Matrix rotateYMatrix(double y);
  Matrix rotateZMatrix(double z);
  Matrix rotateMatrix(double x, double y, double z);

  Matrix translateMatrix(double x, double y, double z);
  Matrix translateMatrix(Vec3D v);
  

}