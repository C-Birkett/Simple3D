#include <iostream>
#include <SDL2/SDL.h>
#include <valarray>

#include "matrix.h"
#include "3D.h"

const int WIDTH = 800, HEIGHT = 600;

Matrix test(3);

int main(int argv, char** args){

  //matrix test
  for(int r = 0; r<3; r++){
    for(int c = 0; c<3; c++){
      test(r,c) = c+1 + (r*3);
    } 
  }

  std::cout << std:: endl;

  test.print();

  test = test*test;

  test.print();

  //inner prod test
  std::valarray<double> a(3);
  std::valarray<double> b(3);
  for(int i = 0; i<3; i++){
    a[i] = i+1;
    b[i] = (i+1);
  }

  Matrix I(3);
  I.zeros();

  for(int i = 0; i <3; i++){
    I(i,i) = 1;
  }

  b = I*a;

  for(int i = 0; i <3; i++){
    std::cout << b[i] << " ";
  }


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
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

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
