#pragma once

#include "gameObject.h"
#include "3D.h"

class Polyhedron : public GameObject{
  protected:
    std::vector<Vec3D> vertices;
    std::vector<S3D::Polygon> polys;

  public:
    
    Polyhedron(){};
    ~Polyhedron(){};

    void Update();
    void Draw(){scene->DrawPolys(polys);}
    //void Draw() { scene->DrawPoints(vertices); }

    void Rotate(double x, double y, double z);
    void Rotate(Vec3D rot);

    void Translate(double x, double y, double z);
    void Translate(Vec3D t);

    std::vector<Vec3D> getVerts(){return vertices;}
    std::vector<S3D::Polygon> getPolys(){return polys;}
};

class Cube : public Polyhedron{
  public:

    //default 1 side length, at origin
    Cube();
    Cube(Vec3D p, double l);
    
    ~Cube(){};
};
