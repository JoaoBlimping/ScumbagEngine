#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>



struct Sprite
{
  SDL_Texture *texture;
  SDL_Rect rect;
  float elapsed;
};



#endif
