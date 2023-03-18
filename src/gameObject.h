#pragma once

#include "Scene.h"
#include "3D.h"

class GameObject{
  protected:
    

  public:
    Scene* scene;

    Vec3D pos;
    Vec3D vel;
    Vec3D acc;

    void setVel(Vec3D v) { this->vel = v; }

    Vec3D theta;
    Vec3D omega;

    GameObject(){};
    ~GameObject(){};

    virtual void Update(){
        //vel.v += acc.v;
        //pos.v += vel.v;
    }

    virtual void Draw(){};
};
