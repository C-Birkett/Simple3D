#pragma once

#include "Scene.h"
#include "3D.h"

class GameObject{
  protected:
    Scene* scene;

    Vec3D pos;
    Vec3D vel;
    Vec3D acc;

  public:
  GameObject(){};
  ~GameObject(){};

  virtual void Update(){
    vel.v += acc.v;
    pos.v += vel.v;
  }

  virtual void Draw(){};
};
