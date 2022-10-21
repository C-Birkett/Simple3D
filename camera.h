#pragma once

#include <SDL.h>

#include "Scene.h"
#include "gameObject.h"
#include "3D.h"
#include "matrix.h"

const int WIDTH = 600, HEIGHT = 600;

class Camera : public GameObject{
  private:
    Vec3D target;
    Vec3D up;

    double fov; //degrees
    double aspectRatio; // x:y
    // clipping planes in z
    double near;
    double far;

    // transform space coords to camera
    Matrix* camMat;
    void genCamMat();

    // clip camera space
    Matrix* clipMat;
    void genClipMat();

  public:
    
    Camera(Scene* s){
      this->scene = s;
      //pos = {0,0,0};
      pos = {3,3,3};
      target = {0,0,0}; //look in world z
      up = {0,1,0}; //up = world y

      fov = 1.0/tan(90/2.0);
      aspectRatio = 1;
      near = 0.1;
      far = 10;

      camMat = new Matrix(4);
      clipMat = new Matrix(4);

      genCamMat();
      genClipMat();
    }

    ~Camera(){};
    
    void Draw(){};

    void Update();

    bool ViewClip(std::valarray<double> v3D);

    SDL_Point Project(Vec3D* v3D);
};
