#ifndef LEVEL_H
/*
 *     \\ || //
 *      \\||//
 *       \  /   I am very lonely
 *        ||
 *        ||
 */
#define LEVEL_H


#include "List.h"
#include "Object.h"
#include "Bullet.h"
#include "tmx/tmx.h"
#include <stdint.h>


#define Level_OBJECT_LIST_SIZE 7000
#define Level_BULLET_LIST_SIZE 2000


/** a level in the game */
struct Level
{
  /** size of map on x axis */
  int width;
  /** size of map on y axis */
  int breadth;
  /** width of tiles from left to right */
  int tileWidth;
  /** width of tiles according to map from top to bottom */
  int tileHeight;
  /** background colour of the level */
  int backgroundColour;
  /** all the objects in the map that have to get sorted and displayed and that */
  struct Object *objects[Level_OBJECT_LIST_SIZE];
  /** all of the bullets in the level */
  struct Bullet *List_DEFINE(bullets,Level_BULLET_LIST_SIZE);
  /** the neumber of layers */
  int nLayers;
  /** this is an array of pointers to arrays of ints where each one is a layer of the map, each
   * value is the height of that given tile. the heihts of each layer are given by the heights
   * property */
  float **collisions;
  /** tells you how high up each layer is */
  float *heights;
  /** this is not used for anything, but it is kept so that it can be freed only when it's stuff is
   * no longer needed */
  tmx_map *tiledMap;
};


void Level_init();


/** loads in a map, usually you will probably call some cache thing and not this directly */
struct Level *Level_loadLevel(char const *filename);


/** checks if a given area contains any level blocks in it
 * @param level is the level this is being checked for
 * @param x is the position on the x axis
 * @param y is the position on the y axis
 * @param z is the position on the z axis so how high up it is
 * @param w is the length of the space on both x and y axes
 * @param h is the distance downwards the space extends
 * @return 0 iff the space is empty */
int Level_checkSpace(struct Level *level,float x,float y,float z,float w,float h);


/** finds the floor level below some point
 * @param level is the level we are looking in
 * @param x is the position on the x axis of this point
 * @param y is the position on the y axis of this point
 * @param z is the position on the z axis of this point
 * @return height of the floor below the point */
float Level_floor(struct Level *level,float x,float y,float z);


/** gets you a fresh objecy
 * @param level is the level
 * @return a fresh level which is now set as in use which you must unset yourself */
struct Object *Level_getObject(struct Level *level);


/** adds a bullet to the level
 * @param bullet is the bullet
 * @param level is the level we are adding to */
void Level_addBullet(struct Bullet *bullet,struct Level *level);


/** updates the level and does nice stuff like move things
 * @param level is the level */
void Level_update(struct Level *level);


/** renders a map :) */
void Level_renderLevel(struct Level *level,int cameraX,int cameraY);


/** deltes the level */
void Level_free(struct Level *level);




#endif
