#include "Scene.h"

#include "3D.h"
#include "polyhedron.h"
#include "camera.h"

Scene::Scene(){}

Scene::Scene(SDL_Renderer* r){
  renderer = r;
  camera = new Camera(this);
}

void Scene::Draw() {
    for (auto& o : this->objects) { o->Draw(); }
}

void Scene::Update() {
    //for (auto& o : this->objects) { o->Update(); }
    this->camera->Update();
}

std::vector<SDL_Point> Scene::Project3DPolyTo2D(S3D::Polygon p3D){
  int nverts = p3D.verts.size();
  std::vector<SDL_Point> out(nverts);

  for(int i=0; i < nverts; i++){
      auto& vert = p3D.verts.at(i);
      
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

      out.at(i) = (this->camera->Project(vert));
  }

  return out;
}

std::vector<SDL_Point> Scene::Project3DPointsTo2D(std::vector<Vec3D> pts){
  std::vector<SDL_Point> out(pts.size());
    for(int i=0; i < (int)pts.size(); i++){
      out.at(i) = this->camera->Project(&(pts.at(i)));
    }

  return out;
}

void Scene::DrawPolys(std::vector<S3D::Polygon> polys){
  for(const auto &p : polys){
    std::vector<SDL_Point> pts2D = this->Project3DPolyTo2D(p);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLines(this->renderer, pts2D.data(), pts2D.size());
  }
}

void Scene::DrawPoints(std::vector<Vec3D> pts){
    std::vector<SDL_Point> pts2D = this->Project3DPointsTo2D(pts);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(this->renderer, pts2D.data(), pts2D.size());
}

GameObject* Scene::CreateObject(){
  Vec3D pos(0,0,20);
  auto testCube = new Cube(pos, 100);
  testCube->scene = this;
  this->objects.push_back(testCube);
  return testCube;
}
