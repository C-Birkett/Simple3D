#pragma once

#include <SDL2/SDL.h>
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
    std::vector<SDL_Point> Project3DPolyTo2D(const S3D::Polygon& p3D, bool* badVerts);
    std::vector<SDL_Point> Project3DPointsTo2D(const std::vector<Vec3D>& pts);

  public:
  
    Scene();
    Scene(SDL_Renderer* r);
    ~Scene(){};

    Camera* getCamera() { return camera; }

    double deltaTime;

    void Update();

    void Draw();
    
    void DrawPolys(const std::vector<S3D::Polygon>& polys);

    void DrawPoints(const std::vector<Vec3D>& pts);

    GameObject* CreateObject();

    GameObject* CreateCube(const Vec3D& pos, double size);
    
    /*  TODO figure this out
    template <class T>
    GameObject* CreateObject<T>(Vec3D pos);
    */

    GameObject* GetObject(int i) { return objects[i]; }
};
