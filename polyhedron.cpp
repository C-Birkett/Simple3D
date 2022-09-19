#include "polyhedron.h"

void Polyhedron::Update(){}

Cube::Cube() {
    this->pos.v = { 0,0,0 };
    this->vertices.reserve(8);
    this->polys.reserve(6);

    //gen vertices
    for (int i = 0; i <= 1; i++) {
        this->vertices.emplace_back(Vec3D(i, 0, 0));
        this->vertices.emplace_back(Vec3D(i, 1, 0));
        this->vertices.emplace_back(Vec3D(i, 1, 1));
        this->vertices.emplace_back(Vec3D(i, 0, 1));
    }

    //store all 6 faces as polys
    //tedious but works -> probably a smarter way of finding these polys
    int faceIndices[24] = {1,2,3,4, 5,6,7,8, 1,2,6,5, 3,4,8,7, 2,3,7,6, 1,4,5,8};   //1 indexed

    for (int i = 0; i < 6; i++) {
        S3D::Polygon p;
        p.verts.reserve(5);
        p.nverts = 5;
        for (int j = 0; j < 4; j++) {
            p.verts.push_back(&this->vertices.at(faceIndices[4 * i + j] -1));
        }
        p.verts.push_back(p.verts.at(0));   //close polys for drawing
        this->polys.push_back(p);
    }
}

//create scaled cube
Cube::Cube(Vec3D p, double l){
  this->pos.v = p.v;
  this->vertices.reserve(8);
  this->polys.reserve(6);

  //gen vertices
  for (int i = 0; i <= 1; i++) {
      this->vertices.emplace_back(Vec3D(i, 0, 0));
      this->vertices.emplace_back(Vec3D(i, 1, 0));
      this->vertices.emplace_back(Vec3D(i, 1, 1));
      this->vertices.emplace_back(Vec3D(i, 0, 1));
  }
  //gen vertices
  for(int i=0; i<=1; i++){
    for(int j=0; j<=1; j++){
      for(int k=0; k<=1; k++){
        this->vertices.emplace_back(Vec3D(i*l+p.x(),j*l+p.y(),k*l+p.z()));
      }
    }
  }

  //store all 6 faces as polys
  for(int i=0; i<3; i++){
    S3D::Polygon p1, p2;
    p1.verts.reserve(5);
    p1.nverts = 5;
    p2.verts.reserve(5);
    p2.nverts = 5;
    for(auto &v : this->vertices){
      if(v.v[i] == p.v[i]){
        p1.verts.push_back(&v);
      }else{
        p2.verts.push_back(&v);
      }
    }

    //close polys
    p1.verts.push_back(p1.verts[0]);
    p2.verts.push_back(p2.verts[0]);

    this->polys.push_back(p1);
    this->polys.push_back(p2);
  }
}
