#ifndef BULLET_GROUP_H
#define BULLET_GROUP_H


#include "Bullet.h"


/** a whole bunch of reusable bullets that are all of the same kind.
 * when one is destroyed, it can then be used again, and in that way, we are able to save from
 * instantiating shit all the time */
struct BulletGroup
{
  /** the size of the group */
  int nBullets;
  /** the bullet that all others are based on */
  struct Bullet const *mother;
  /** this is the lot of bullets */
  struct Bullet *children[];
};


/** create a bullet group of the given size
 * @param size is the number of bullets in this group
 * @param mother is the bullet that the other bullets will be like
 * @param level is the level we are creating this in
 * @return the new bullet group */
struct BulletGroup *BulletGroup_create(int size,struct Bullet const *mother,struct Level *level);


/** adds a bullet to the bullet group unless it is full
 * @param x is the x position to add the bullet at
 * @param y is the y position to add the bullet at
 * @param z is the z position to add the bullet at
 * @param group is the group we are doing this for */
struct Bullet *BulletGroup_add(float x,float y,struct BulletGroup *group);


#endif
