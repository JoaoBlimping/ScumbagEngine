#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct Object
{
  float x;
  float y;
  float z;
  float h;
  SDL_Rect src;
  SDL_Rect dst;
  SDL_Texture *texture;
};



#endif
