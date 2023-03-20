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

  out(0, 0) = fov * aspectRatio;
  out(1, 1) = fov;
  out(2, 2) = (far + near) / (far - near);
  out(2, 3) = 1;
  out(3, 2) = (2 * near * far) / (near - far);

  *clipMat = out;
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

 SDL_Point Camera::Project(Vec3D v3D, bool& badEdge)
 {
    static Vec3D prev, inFront, behind, clipped;
    static bool prevNegativeW = false;
    Vec3D vec(v3D);

    //apply inverse camera transform and clipping matrices
    // TODO dont do this transform twice
    vec.Transform(camMat, false);
    vec.Transform(clipMat, false);
    
    //bool negativeW = vec.w() < GLOBAL::CAMERA_NEAR_CLIP;
    bool negativeW = vec.w() <= 0.0;

    SDL_Point out;
    
    if(!negativeW && !prevNegativeW) // normal case
    {
      out.x = (vec.x()*GLOBAL::WINDOW_WIDTH) / (2.0*vec.w()) + (GLOBAL::WINDOW_WIDTH/2.0);
      out.y = (vec.y()*GLOBAL::WINDOW_HEIGHT) / (2.0*vec.w()) + (GLOBAL::WINDOW_HEIGHT/2.0);
    }
    else if(negativeW && prevNegativeW)
    {
        badEdge = true;
    }
    else // one point on edge is behind camera, find intersection with clip plane
    {
      if(negativeW && !prevNegativeW)
      {
        inFront = prev;
        behind = vec;
      }
      else
      {
        inFront = vec;
        behind = prev;
      }
      
      inFront.print(true);
      behind.print(true);

      double normalise = (inFront.w() - GLOBAL::CAMERA_NEAR_CLIP) / (inFront.w() - behind.w());
      
      clipped.Setx((normalise * inFront.x()) + ((1-normalise) * behind.x()));
      clipped.Sety((normalise * inFront.y()) + ((1-normalise) * behind.y()));
      clipped.Setz((normalise * inFront.z()) + ((1-normalise) * behind.z()));
      clipped.Setw(GLOBAL::CAMERA_NEAR_CLIP);

      clipped.print(true);
      std::cout<< clipped.x()*GLOBAL::WINDOW_WIDTH << std::endl;
      std::cout<< (2.0*clipped.w()) + (GLOBAL::WINDOW_WIDTH/2.0) << std::endl;
      std::cout<< clipped.x()*GLOBAL::WINDOW_WIDTH / ((2.0*clipped.w()) + (GLOBAL::WINDOW_WIDTH/2.0)) << std::endl;

      out.x = (clipped.x()*GLOBAL::WINDOW_WIDTH) / (clipped.w()) + (GLOBAL::WINDOW_WIDTH/2.0);
      out.y = (clipped.y()*GLOBAL::WINDOW_HEIGHT) / (clipped.w()) + (GLOBAL::WINDOW_HEIGHT/2.0);
    }
    
    prev = vec;
    prevNegativeW = negativeW;
    return out;
}

void Camera::Update()
{
  HandleKeyboardInput();

  Vec3D zero;
  if(vel != zero
  || acc != zero)
  {
        vel += acc;
        pos += vel;

        genCamMat();
      } 
};

void Camera::HandleKeyboardInput()
  {
    static const Uint8* kb = SDL_GetKeyboardState(nullptr);
    
    vel.Setx(10 * (kb[SDL_SCANCODE_D] - kb[SDL_SCANCODE_A]));
    vel.Sety(10 * (kb[SDL_SCANCODE_LSHIFT] - kb[SDL_SCANCODE_SPACE]));
    vel.Setz(10 * (kb[SDL_SCANCODE_W] - kb[SDL_SCANCODE_S]));
  }