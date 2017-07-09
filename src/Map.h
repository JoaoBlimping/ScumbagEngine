#ifndef MAP_H
#define MAP_H


#include "Tileset.h"
#include <stdint.h>


struct Map
{
  Tileset *tileset;
  uint8_t *music;
  int width;
  int height;
  uint8_t tiles[];
};


/** loads in a map, usually you will probably call some cache thing and not this directly */
struct Map *Map_loadMap(uint8_t const *filename);




#endif
