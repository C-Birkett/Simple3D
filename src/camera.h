#pragma once

#include <SDL2/SDL.h>

#include "Scene.h"
#include "gameObject.h"
#include "3D.h"
#include "matrix.h"

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
    
    void HandleKeyboardInput();

  public:
    
    Camera(Scene* s){
      scene = s;
      target.Setz(1); //look in world z
      up.Sety(1); //up = world y

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
    
    void incrementFar(double far) { 
        this->far += far;
        this->genClipMat();
    }

    void Draw(){};

    void Update();

    bool ViewClip(std::valarray<double> v3D);

    SDL_Point Project(Vec3D v3D);
    //SDL_Point Project(Vec3D* v3D) {return Project(*v3D);};
};
