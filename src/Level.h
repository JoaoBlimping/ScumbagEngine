#ifndef LEVEL_H
#define LEVEL_H


#include "List.h"
#include "Object.h"
#include "tmx/tmx.h"
#include <stdint.h>


#define OBJECT_LIST_SIZE 7000


struct Level
{
  struct Object *List_DEFINE(objects,OBJECT_LIST_SIZE);
  tmx_map *map;
};


void Level_init();


/** loads in a map, usually you will probably call some cache thing and not this directly */
struct Level *Level_loadLevel(uint8_t const *filename);


/** renders a map :) */
void Level_renderLevel(struct Level *level,int cameraX,int cameraY);




#endif
