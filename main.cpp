#include <iostream>
#include <SDL.h>
#include <valarray>

#include "matrix.h"
#include "3D.h"
#include "Scene.h"
#include "gameObject.h"
#include "polyhedron.h"

const int WIDTH = 600, HEIGHT = 600;

int main(int argc, char* argv[]) {

  Vec3D p = {0, 0, 15};
  Cube test;
  Cube test2(p, 10);

  bool quit = false;
  
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

  renderer = SDL_CreateRenderer(window, -1, 0);

  Scene* gameScene = new Scene(renderer);
  gameScene->CreateObject();

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  //gameScene->DrawPoints(test2.getVerts());
  gameScene->DrawPolys(test.getPolys());

  //gameScene->Draw();

  SDL_RenderPresent(renderer);
  
  SDL_Event event;
  while(!quit) {
    if(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          quit = true;
          break;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
