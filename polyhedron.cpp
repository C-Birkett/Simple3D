#include "polyhedron.h"

void Polyhedron::Update() {
    double dt = this->scene->deltaTime;

    //accellerate
    Vec3D dv = this->acc * dt;
    this->vel.translate(dv);

    Vec3D dTheta = this->omega * dt;
    this->theta.translate(dTheta);
    //this->theta.print();
    
    //move
    Vec3D dx = this->vel * dt;
    this->pos.translate(dx);

    //move vertices
    for (auto& v : this->vertices) {
        v.translate(dx);
        v.rotate(pos, dTheta);
    }
}

void Polyhedron::Rotate(double x, double y, double z) {
    for (auto& v : this->vertices) {
        v.rotate(this->pos, x,y,z);
    }
}

void Polyhedron::Rotate(Vec3D rot) {
    for (auto& v : this->vertices) {
        v.rotate(this->pos, rot);
    }
}

void Polyhedron::Translate(double x, double y, double z) {
    this->pos.setX(this->pos.x() + x);
    this->pos.setY(this->pos.y() + y);
    this->pos.setZ(this->pos.z() + z);

    for (auto& v : this->vertices) {
        v.translate(x,y,z);
    }
}

void Polyhedron::Translate(Vec3D t) {
    this->pos = this->pos + t;
   
    for (auto& v : this->vertices) {
        v.translate(t);
    }
}

Cube::Cube() {
    this->pos.v = { 0,0,0 };
    this->vel.v = { 0,0,0 };
    this->acc.v = { 0,0,0 };
    this->theta.v = { 0,0,0 };
    this->omega.v = { 0,0,0 };

    this->theta.print();

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
    int faceIndices[24] = { 1,2,3,4, 5,6,7,8, 1,2,6,5, 3,4,8,7, 2,3,7,6, 1,4,8,5 };   //1 indexed

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
    
    /*
        Cube* out= new Cube;
        out.pos = p
        for(auto& v : out->vertices){
            v.scale(l)
            v.translate(p);
        }
        this = out;
    */
    this->pos.v = { 0,0,0 };
    this->vel.v = { 0,0,0 };
    this->acc.v = { 0,0,0 };
    this->theta.v = { 0,0,0 };
    this->omega.v = { 0,0,0 };

    this->theta.print();
  
  this->vertices.reserve(8);
  this->polys.reserve(6);

  //gen vertices scaled to l
  for (int i = 0; i <= 1; i++) {
      this->vertices.emplace_back(Vec3D(i, 0, 0)*l);
      this->vertices.emplace_back(Vec3D(i, 1, 0)*l);
      this->vertices.emplace_back(Vec3D(i, 1, 1)*l);
      this->vertices.emplace_back(Vec3D(i, 0, 1)*l);
  }

  //move to pos
  this->Translate(p);

  //store all 6 faces as polys
  //tedious but works -> probably a smarter way of finding these polys
  int faceIndices[24] = { 1,2,3,4, 5,6,7,8, 1,2,6,5, 3,4,8,7, 2,3,7,6, 1,4,8,5 };   //1 indexed

  for (int i = 0; i < 6; i++) {
      S3D::Polygon p;
      p.verts.reserve(5);
      p.nverts = 5;
      for (int j = 0; j < 4; j++) {
          p.verts.push_back(&this->vertices.at(faceIndices[4 * i + j] - 1));
      }
      p.verts.push_back(p.verts.at(0));   //close polys for drawing
      this->polys.push_back(p);
  }
}
