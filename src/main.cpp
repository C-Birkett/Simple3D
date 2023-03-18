#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <iostream>
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

  // setup SDL renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  // fps counting
  Uint64 fps_now = SDL_GetPerformanceCounter(); //current time
  Uint64 fps_last = 0; //the last recorded time.

  double fps_deltatime = 0; // time between frames
  
  Uint64 fps_lasttime = SDL_GetTicks(); //last time fps recorded
  Uint64 fps_current; //the current FPS.
  Uint64 fps_frames = 0; //frames passed since the last recorded fps.

  // seed randoms
  srand(fps_now);

  // Initialise scene
  Scene* gameScene = new Scene(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // initialise some cubes
  std::vector<Cube*> myCubes;
  myCubes.reserve(9);
  for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
          auto newCube = (Cube*)gameScene->CreateCube(Vec3D(200 * i, 200 * j, 250), 100);
          myCubes.push_back(newCube);
      }
  }

  // event handling
  SDL_Event event;

  // main loop
  while(!quit) {

      // poll events & handle inputs
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

                case SDLK_r:
                    for (auto& c : myCubes) {
                        c->omega = Vec3D(rand() % 10 * (M_PI / 2), rand() % 10 * (M_PI / 2), rand() % 10 * (M_PI / 2));
                    }
                    break;
                case SDLK_p:
                    for (auto c : myCubes) {
                        c->omega = Vec3D(0, 0, 0);
                    }
                    break;
                // not working currently
                case SDLK_t:
                    gameScene->getCamera()->incrementFar(100);
                    break;
                case SDLK_g:
                    gameScene->getCamera()->incrementFar(-100);
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(0, 0, 10);
                    break;
                
                case SDLK_a:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(-10, 0, 0);
                    break;

                case SDLK_s:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(0, 0, -10);
                    break;

                case SDLK_d:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(10, 0, 0);
                    break;

                case SDLK_SPACE:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(0, -10, 0);
                    break;

                case SDLK_LSHIFT:
                    gameScene->getCamera()->vel = Vec3D(0, 0, 0);
                    //gameScene->getCamera()->vel -= Vec3D(0, 10, 0);
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
        std::cout << "fps: " << fps_current << std::endl;
    }

    //wait to maintain target framerate
    SDL_Delay(1000.0f / (FPS_TARGET - fps_deltatime));
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
