#include "camera.h"

void Camera::genCamMat(){
  Matrix out(4);
  out.zeros();

  Vec3D zAxis = (this->target - this->pos).normalise();
  Vec3D xAxis = (this->up.cross(zAxis)).normalise();
  Vec3D yAxis = (zAxis.cross(xAxis)).normalise();
  
  //xAxis.v[2] = -xAxis.v[2];

  //gen each col
  for(int i = 0; i < 3; i++){
    out(i, 0) = xAxis.v[i];
    out(i, 1) = yAxis.v[i];
    out(i, 2) = zAxis.v[i];
  }
  //final row
  out(3, 0) = -xAxis.dot(pos);
  out(3, 1) = -yAxis.dot(pos);
  out(3, 2) = -zAxis.dot(pos);
  out(3, 3) = 1;

  out.print();

  *this->camMat = out;
}

void Camera::genClipMat(){
  Matrix out(4);
  out.zeros();

  out(0,0) = this->fov*this->aspectRatio;
  out(1,1) = this->fov;
  out(2,2) = (far+near)/(far-near);
  out(2,3) = (2*near*far)/(near-far);
  out(3,2) = 1;

  *this->clipMat = out;
}

SDL_Point Camera::Project(Vec3D v3D){
  //generalised vector
  std::valarray<double> v3Dgen(0.0, 4);
  for(int i=0; i<3; i++){
    v3Dgen[i] = v3D.v[i];
  }

  //set w = 1
  v3Dgen[3] = 1;

  v3Dgen = *this->camMat * v3Dgen;
  v3Dgen = *this->clipMat * v3Dgen;

  SDL_Point out;
  out.x = (v3Dgen[0]*WIDTH) / (2.0*v3Dgen[3]) + (WIDTH/2);
  out.y = (v3Dgen[1]*HEIGHT) / (2.0*v3Dgen[3]) + (HEIGHT/2);
  return out;
}

void Camera::Update(){
  Vec3D zero;
  if((this->vel != zero) || (this->acc != zero)){
        this->vel.v *= this->acc.v;
        this->pos.v *= this->vel.v;

        this->genCamMat();
      } 
};
