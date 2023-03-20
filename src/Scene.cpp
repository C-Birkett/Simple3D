#include "Scene.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "3D.h"
#include "polyhedron.h"
#include "camera.h"
#include "Globals.h"

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

std::vector<SDL_Point> Scene::Project3DPolyTo2D(const S3D::Polygon& poly, bool* badEdges)
{
  // outputs
  SDL_Point projPoint;
  std::vector<SDL_Point> out;
  out.reserve(poly.size());

  // handle clipping
  bool badEdge = false;
  badEdges = nullptr;

  static Vec3D inFront, behind, clipped;
  double normalise;
  
  Vec3D* vert;
  Vec3D* prevVert = nullptr;
  for(int i = 0; i < poly.size(); i++)
  {
    vert = poly.at(i);

    projPoint = camera->Project(*vert, badEdge);
  
    out.emplace_back(projPoint);
    
    if (badEdge) 
      {
      if(!badEdges) badEdges = new bool[poly.size()-1];
      for (int b=0 ; b < poly.size()-1; b++) badEdges[b] = false;
      badEdges[i-1] = true;
      }
  }
  
  return out;
}

std::vector<SDL_Point> Scene::Project3DPointsTo2D(const std::vector<Vec3D>& pts)
{
  std::vector<SDL_Point> out;
  out.reserve(pts.size());
  bool negativeW;
  SDL_Point projPoint;

  for (auto& pt : pts)
  {
    projPoint = (camera->Project(pt, negativeW));
    if(negativeW) out.emplace_back(projPoint);
  }

  return out;
}

void Scene::DrawPolys(const std::vector<S3D::Polygon>& polys)
{
  bool* badEdges = nullptr;
  for(auto poly : polys)
  {
    std::vector<SDL_Point> pts2D = Project3DPolyTo2D(poly, badEdges);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(!badEdges)
    {
      SDL_RenderDrawLines(renderer, pts2D.data(), pts2D.size());
    }
    else // don't draw bad lines
    {
      for (int i = 1; i < pts2D.size(); i++)
        {
          SDL_Point prev = pts2D.at(i-1);
          SDL_Point pnt = pts2D.at(i);
          if(!badEdges[i-1])
            {
              SDL_RenderDrawLine(renderer, prev.x, prev.y, pnt.x, pnt.y);
            }
        }
      delete badEdges;
    }
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