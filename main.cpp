#include <iostream>
#include <SDL.h>
#include <valarray>

#include "matrix.h"
#include "3D.h"
#include "Scene.h"
#include "gameObject.h"
#include "polyhedron.h"
#include "camera.h"

#define FPS_POLL_INTERVAL 1.0 //seconds
#define FPS_TARGET 60.0f

//const int WIDTH = 600, HEIGHT = 600;

int main(int argc, char* argv[]) {

  bool quit = false;
  
  // setup SDL window
  SDL_Window *window;
  SDL_Renderer *renderer;
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("C++ Example",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT,
                                        SDL_WINDOW_ALLOW_HIGHDPI);
  if(window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  // setup SDL renderer and game scene
  renderer = SDL_CreateRenderer(window, -1, 0);

  Scene* gameScene = new Scene(renderer);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // fps counting

  Uint64 fps_now = SDL_GetPerformanceCounter(); //current time
  Uint64 fps_last = 0; //the last recorded time.

  double fps_deltatime = 0; // time between frames
  
  Uint64 fps_lasttime = SDL_GetTicks(); //last time fps recorded
  Uint64 fps_current; //the current FPS.
  Uint64 fps_frames = 0; //frames passed since the last recorded fps.

  //testing:
  gameScene->CreateObject();

  //Cube test:
  Vec3D p2 = {-5, -5, 10 };
  Cube test2(p2, 10);
  Vec3D p3 = { -100, -100, 100 };
  Cube test3(p3, 20);
  //test2.Rotate(3.14159 / 4, 0, 0);

  //gameScene->DrawPoints(test2.getVerts());
  gameScene->DrawPolys(test2.getPolys());
  gameScene->DrawPolys(test3.getPolys());

  //auto cube = gameScene->GetObject(0);
  //cube->omega = { 1,0,0 };

  //gameScene->Draw();

  SDL_RenderPresent(renderer);
  
  SDL_Event event;
  while(!quit) {
    //exit if quit



    if(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w: 
                    gameScene->getCamera()->vel = Vec3D(0, 0, 10);
                    break;

                case SDLK_a:
                    gameScene->getCamera()->vel = Vec3D(-10, 0, 0);
                    break;

                case SDLK_s:
                    gameScene->getCamera()->vel = Vec3D(0, 0, -10);
                    break;
                
                case SDLK_d:
                    gameScene->getCamera()->vel = Vec3D(10, 0, 0);
                    break;
                case SDLK_SPACE:
                    gameScene->getCamera()->vel = Vec3D(0, -10, 0);
                    break;
                case SDLK_LSHIFT:
                    gameScene->getCamera()->vel = Vec3D(0, 10, 0);
                    break;

            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;
                
                case SDLK_a:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;

                case SDLK_s:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;

                case SDLK_d:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;

                case SDLK_SPACE:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;

                case SDLK_LSHIFT:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    break;
            }
            break;
      }
    }



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    gameScene->Update();
    gameScene->Draw();

    SDL_RenderPresent(renderer);

    //get deltatime between frames
    fps_last = fps_now;
    fps_now = SDL_GetPerformanceCounter();
    fps_deltatime = (double)(fps_now - fps_last) / (double)SDL_GetPerformanceFrequency();

    //scene can communicate dt to objects
    gameScene->deltaTime = fps_deltatime;

    //poll framerate every FPS_POLL_INTERVAL
    fps_frames++;
    if (fps_lasttime < SDL_GetTicks() - FPS_POLL_INTERVAL * 1000)
    {
        fps_lasttime = SDL_GetTicks();
        fps_current = fps_frames;
        fps_frames = 0;
        //std::cout << fps: << fps_current << std::endl;
    }

    //wait to maintain target framerate
    SDL_Delay(1000.0f / (FPS_TARGET - fps_deltatime));
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
