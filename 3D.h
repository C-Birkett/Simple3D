#pragma once

#include <cmath>
#include <valarray>
#include <vector>
#include <iostream>

#include "matrix.h"

class Vec3D{
  public:
  // 0 by default
  std::valarray<double> v = {0,0,0};

  Vec3D(){}
  Vec3D(double x, double y, double z){
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }

  ~Vec3D(){};

  Vec3D cross(Vec3D v2);

  double dot(Vec3D v2);

  Vec3D normalise();

  double x(){return v[0];}
  double y(){return v[1];}
  double z(){return v[2];}

  Vec3D operator-(Vec3D v2){
    auto v1 = *this;
    auto tmp = v1.v - v2.v;
    Vec3D out;
    out.v = tmp;
    return out;
  }

  Vec3D operator+(Vec3D v2){
    auto v1 = *this;
    auto tmp = v1.v + v2.v;
    Vec3D out;
    out.v = tmp;
    return out;
  }

  Vec3D operator*(Vec3D v2){
    auto v1 = *this;
    auto tmp = v1.v * v2.v;
    Vec3D out;
    out.v = tmp;
    return out;
  }

  bool operator==(Vec3D v2){
    auto v1 = *this;
    if((v1.x() != v2.x())||(v1.y() != v2.y())||(v1.z() != v2.z())){
      return false;
    }else{
      return true;
    }
  }

  bool operator!=(Vec3D v2){
    auto v1 = *this;
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
  Matrix rotateX(double x);
  Matrix rotateY(double y);
  Matrix rotateZ(double z);
  Matrix rotate(double x, double y, double z);
}
