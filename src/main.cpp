#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <iostream>
#include <valarray>
#include <cassert>

#include "Globals.h"

#include "matrix.h"
#include "3D.h"
#include "Scene.h"
#include "gameObject.h"
#include "polyhedron.h"
#include "camera.h"

#define FPS_POLL_INTERVAL 1.0 //seconds
#define FPS_TARGET 60.0f

//#define PRINT_FPS
//#define PRINT_PERFORMANCE

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
                                        GLOBAL::WINDOW_WIDTH, GLOBAL::WINDOW_HEIGHT,
                                        SDL_WINDOW_ALLOW_HIGHDPI);
  if(window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  // setup SDL renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  // fps counting
  Uint64 time_last = SDL_GetTicks(); //last time fps recorded

  Uint64 fps_now = SDL_GetPerformanceCounter(); //current time
  Uint64 fps_last = 0; //the last recorded time.

  double fps_deltatime = 0; // time between frames
  
  Uint64 fps_current; //the current FPS.
  Uint64 fps_frames = 0; //frames passed since the last recorded fps.
  
  // update and draw performance
  Uint64 time_update = 0;
  Uint64 time_draw = 0;
  double dt_update = 0;
  double dt_draw = 0;

  // seed randoms
  srand(fps_now);

  // Initialise scene
  Scene* gameScene = new Scene(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // initialise some cubes
  std::vector<Cube*> myCubes;

    // onecube
  //Cube* cube = (Cube*)gameScene->CreateCube(Vec3D(0,0,250), 100);
  //myCubes.emplace_back(cube);

    // 3x3 cube array
  myCubes.reserve(9);
  for (int i = -1; i <= 1; i++) 
  {
      for (int j = -1; j <= 1; j++) 
      {
          auto newCube = (Cube*)gameScene->CreateCube(Vec3D(200 * i, 200 * j, 250), 100);
          myCubes.push_back(newCube);
      }
  }

  // event handling
  SDL_Event event;
    
    // keyboard handling
    const Uint8* kb = SDL_GetKeyboardState(nullptr);

  // main loop
  while(!quit) \
  {
    // poll events & handle inputs
    SDL_PumpEvents();

    if(SDL_PollEvent(&event)) 
    {
      switch(event.type) 
      {
        case SDL_QUIT:
          quit = true;
          break;
      }
    }

    if(kb[SDL_SCANCODE_ESCAPE])
    {
        quit = true;
    }
    if(kb[SDL_SCANCODE_R]) //spinem
    {
        for (auto& c : myCubes) 
        {
            c->omega = Vec3D(rand() % 10 * (M_PI_2), rand() % 10 * (M_PI_2), rand() % 10 * (M_PI_2));
        }
    }
    if(kb[SDL_SCANCODE_P])
    {
        for (auto c : myCubes) 
        {
            c->omega = Vec3D(0, 0, 0);
        }
    }

/*
                // not working currently
                case SDLK_t:
                    gameScene->getCamera()->incrementFar(100);
                    break;
                case SDLK_g:
                    gameScene->getCamera()->incrementFar(-100);
                    break;
                    */

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    time_update = SDL_GetPerformanceCounter();
    gameScene->Update();
    time_update = SDL_GetPerformanceCounter() - time_update;

    time_draw = SDL_GetPerformanceCounter();
    gameScene->Draw();
    time_draw = SDL_GetPerformanceCounter() - time_draw;
    
    SDL_RenderPresent(renderer);
    
    // Framerate and timing:

    //get deltatime between frames
    fps_last = fps_now;
    fps_now = SDL_GetPerformanceCounter();
    fps_deltatime = (double)(fps_now - fps_last) / (double)SDL_GetPerformanceFrequency();

    //scene can communicate dt to objects
    gameScene->deltaTime = fps_deltatime;

    //poll framerate every FPS_POLL_INTERVAL
    fps_frames++;
    if (time_last < SDL_GetTicks() - FPS_POLL_INTERVAL * 1000)
    {
        time_last = SDL_GetTicks();
        fps_current = fps_frames;
        fps_frames = 0;
        #ifdef PRINT_FPS
            std::cout << "fps: " << fps_current << std::endl << std::endl;
        #endif
        #ifdef PRINT_PERFORMANCE
            dt_update = time_update / (double)SDL_GetPerformanceFrequency();
            dt_draw = time_draw / (double)SDL_GetPerformanceFrequency();
            std::cout << "-Update time: " << dt_update << std::endl;
            std::cout << "-Draw time: " << dt_draw << std::endl;
        #endif
    }

    //wait to maintain target framerate
    SDL_Delay(1000.0f / (FPS_TARGET - fps_deltatime));
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
