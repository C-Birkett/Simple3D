#include "polyhedron.h"
#include "3D.h"
#include <cassert>
#include <array>

void Polyhedron::Update() 
{
    double dt = scene->deltaTime;

    // accellerate
    Vec3D dv = acc * dt;
    vel.Translate(dv);

    // rotate
    omega.v *= 0.975;   // damping
    Vec3D dTheta = omega * dt;
    theta.Translate(dTheta);
    
    // move
    Vec3D dx = vel * dt;
    pos.Translate(dx);

    // move vertices
    for (auto& v : vertices) 
    {
        v.Translate(dx, false);
        v.Rotate(pos, dTheta, true);
    }
}

inline void Polyhedron::Rotate(double x, double y, double z) {
    for (auto& v : vertices) v.Rotate(pos, x,y,z);
}

inline void Polyhedron::Rotate(Vec3D rot) {
    for (auto& v : vertices) v.Rotate(pos, rot);
}

inline void Polyhedron::Translate(double x, double y, double z) {
    pos.Translate(x, y, z);
    for (auto& v : vertices) v.Translate(x,y,z);
}

inline void Polyhedron::Translate(Vec3D t) 
{
    pos.Translate(t);
    for (auto& v : vertices) v.Translate(t);
}

Cube::Cube() 
{
    vertices.reserve(8);
    polys.reserve(6);

    //gen vertices
    for (int i = 0; i <= 1; i++) 
    {
        vertices.emplace_back(Vec3D(-0.5 + i, -0.5, -0.5));
        vertices.emplace_back(Vec3D(-0.5 + i, 0.5, -0.5));
        vertices.emplace_back(Vec3D(-0.5 + i, 0.5, 0.5));
        vertices.emplace_back(Vec3D(-0.5 + i, -0.5, 0.5));
    }

    //store all 6 faces as polys
    //tedious but works -> probably a smarter way of finding these polys
    static const int faceIndices[24] = { 1,2,3,4, 5,6,7,8, 1,2,6,5, 3,4,8,7, 2,3,7,6, 1,4,8,5 };   //1 indexed

    for (int i = 0; i < 6; i++) {
        S3D::Polygon poly;
        poly.reserve(5);
        for (int j = 0; j < 4; j++) {
            poly.push_back(&vertices.at(faceIndices[4 * i + j] -1));
        }
        poly.push_back(poly.at(0));   //close polys for drawing
        polys.push_back(poly);
    }
}

//create scaled cube
Cube::Cube(Vec3D pos, double len)
{
  vertices.reserve(8);
  polys.reserve(6);

  //gen vertices scaled to len
  double halflen = 0.5*len;
  double xOffset = 0;
  for (int i = 0; i <= 1; i++) 
  {
      xOffset = i*len;
      vertices.emplace_back(Vec3D(-halflen + xOffset, -halflen, -halflen));
      vertices.emplace_back(Vec3D(-halflen + xOffset, halflen, -halflen));
      vertices.emplace_back(Vec3D(-halflen + xOffset, halflen, halflen));
      vertices.emplace_back(Vec3D(-halflen + xOffset, -halflen, halflen));
  }

  //move to pos
  Translate(pos);

  //store all 6 faces as polys
  //tedious but works -> probably a smarter way of finding these polys
  static const std::array<std::array<int, 4>, 6> faceIndices = {{{ 1,2,3,4}, {5,6,7,8}, {1,2,6,5}, {3,4,8,7}, {2,3,7,6}, {1,4,8,5}}};   //1 indexed

  for (int i = 0; i < 6; i++) 
  {
      S3D::Polygon poly;
      poly.reserve(5);
      for (int j = 0; j < 4; j++) 
      {
          poly.push_back(&vertices.at(faceIndices[i][j] - 1));
      }
      poly.push_back(poly.at(0));   //close polys for drawing
      polys.push_back(poly);
  }
}
