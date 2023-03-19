#include "Scene.h"

#include "3D.h"
#include "polyhedron.h"
#include "camera.h"
#include <SDL2/SDL_rect.h>

Scene::Scene(){}

Scene::Scene(SDL_Renderer* r)
{
  renderer = r;
  camera = new Camera(this);
  objects.push_back(camera);
}

void Scene::Draw() 
{
    for (auto& o : objects) { o->Draw(); }
}

void Scene::Update() 
{
    for (auto& o : objects) { o->Update(); }
    camera->Update();
}

std::vector<SDL_Point> Scene::Project3DPolyTo2D(const S3D::Polygon& poly)
{
  std::vector<SDL_Point> out;
  out.reserve(poly.size());

  for(auto& vert : poly)
  {
    //TODO
      /*
      //check for lines intersecting near clip plane
      //if vert outside near clip
      if (this->camera->ViewClip(vert->generalise())) {
          
          
          // check next vert
          if (this->camera->ViewClip((vert + 1)->generalise())) {
              continue; //don't draw
          }
          // find intersection
          else {

          }
      }
      else {
          // find intersection of vert with near clip plane


      }
      */

      out.emplace_back(camera->Project(*vert));
  }
  
  return out;
}

std::vector<SDL_Point> Scene::Project3DPointsTo2D(const std::vector<Vec3D>& pts)
{
  std::vector<SDL_Point> out(pts.size());
    for(int i=0; i < (int)pts.size(); i++)
    {
      out.at(i) = camera->Project(pts.at(i));
    }

  return out;
}

void Scene::DrawPolys(const std::vector<S3D::Polygon>& polys)
{
  for(auto poly : polys)
  {
    std::vector<SDL_Point> pts2D = Project3DPolyTo2D(poly);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLines(renderer, pts2D.data(), pts2D.size());
  }
}

void Scene::DrawPoints(const std::vector<Vec3D>& pts)
{
    std::vector<SDL_Point> pts2D = Project3DPointsTo2D(pts);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(renderer, pts2D.data(), pts2D.size());
}

GameObject* Scene::CreateObject()
{
  Vec3D pos;
  auto testCube = new Cube(pos, 100);
  testCube->scene = this;
  objects.push_back(testCube);
  return testCube;
}

GameObject* Scene::CreateCube(const Vec3D& pos, double size) 
{
    auto myCube = new Cube(pos, size);
    myCube->scene = this;
    objects.push_back(myCube);
    return myCube;
}

/*
template <class T>
Scene::CreateObject<T>(Vec3D pos) {
    auto newObject = new T(pos, 100);
    newObject->scene = this;
    this->objects.push_back(newObject);
    return testCube;
}
*/