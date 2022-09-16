#pragma once

#include <cmath>
#include <valarray>

#include "matrix.h"


//space3D
namespace S3D {
  
  class Point3D{
    public:
    // 0 by default
    std::valarray<double> v = {0,0,0};

    Point3D(){}
    Point3D(double x, double y, double z){
      v[0] = x;
      v[1] = y;
      v[2] = z;
    }

    ~Point3D();

    double x(){return v[0];}
    double y(){return v[1];}
    double z(){return v[2];}
  };

  struct Cube{
    Point3D center;
    std::valarray<Point3D> vertices;
  };
  
  //xyz in radians
  Matrix rotateX(double x);
  Matrix rotateY(double y);
  Matrix rotateZ(double z);
  Matrix rotate(double x, double y, double z);
}
