#include "camera.h"
#include "3D.h"
#include "Globals.h"
#include <cassert>

void Camera::genCamMat()
{
  // translate to camera pos
  Matrix out = S3D::translateMatrix(-pos);

  /*
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
  */
  //out.print();

  *this->camMat = out;
}

void Camera::genClipMat()
{
  Matrix out(4);
  out.zeros();

  out(0, 0) = this->fov * this->aspectRatio;
  out(1, 1) = this->fov;
  out(2, 2) = (this->far + this->near) / (this->far - this->near);
  out(2, 3) = 1;
  out(3, 2) = (2 * this->near * this->far) / (this->near - this->far);

  *this->clipMat = out;
}


bool Camera::ViewClip(std::valarray<double> v3D) 
{
    //apply inverse camera transform and clipping matrices
    v3D = *this->camMat * v3D;

    // geometry clipping
    if (v3D[3] < near) {
        return false;
    }
    else  return true;
}

 SDL_Point Camera::Project(Vec3D v3D)
 {
    Vec3D vec(v3D);
    //apply inverse camera transform and clipping matrices
    // TODO dont fo this transform twice
    vec.Transform(camMat, false);
    vec.Transform(clipMat, false);

    SDL_Point out;
    out.x = (vec.x()*GLOBAL::WINDOW_WIDTH) / (2.0*vec.w()) + (GLOBAL::WINDOW_WIDTH/2);
    out.y = (vec.y()*GLOBAL::WINDOW_HEIGHT) / (2.0*vec.w()) + (GLOBAL::WINDOW_HEIGHT/2);
  
    return out;
}

void Camera::Update()
{
  Vec3D zero;
  if(vel != zero
  || acc != zero)
  {
        vel += acc;
        pos += vel;

        genCamMat();
      } 
};
