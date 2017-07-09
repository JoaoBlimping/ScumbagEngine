#ifndef TILESET_H
#define TILESET_H


#include <stdint.h>
#include <SDL2/SDL.h>


/** a tileset with which you can diplay a level and also detect it's collision stuff */
struct Tileset
{
  /** this also hols the tile width and height */
  SDL_Rect src;

  SDL_Rect dst;

  /** graphics of the tileset */
  SDL_Texture *texture;

  /** an array of true/false values for collisions, where each int is one block to save time */
  uint8_t collisions[0x100];
};


/** loads in all the tilesets for your enjoyment */
void Tileset_init();

struct Tileset *Tileset_get(int index);

/** renders a tile somewhere on the screen */
void Tileset_render(struct Tileset *tileset,uint8_t tile,int x,int y);




#endif
