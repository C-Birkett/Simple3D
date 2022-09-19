#pragma once

#include <SDL.h>
#include <vector>

#include "3D.h"

class GameObject;
class Camera;

class Scene{
  private:
    SDL_Renderer* renderer;

    Camera* camera;

    std::vector<GameObject*> objects;

    //project using camera
    std::vector<SDL_Point> Project3DPolyTo2D(S3D::Polygon p3D);
    std::vector<SDL_Point> Project3DPointsTo2D(std::vector<Vec3D> pts);

  public:
  
    Scene();
    Scene(SDL_Renderer* r);
    ~Scene(){};

    void Draw();
    
    void DrawPolys(std::vector<S3D::Polygon> polys);

    void DrawPoints(std::vector<Vec3D> pts);

    GameObject* CreateObject();
};
