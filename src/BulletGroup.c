#include "BulletGroup.h"

#include "Level.h"
#include "Bullet.h"
#include <stdlib.h>



struct BulletGroup *BulletGroup_create(int size,struct Bullet const *mother,struct Level *level)
{
  struct BulletGroup *group = malloc(sizeof(struct BulletGroup) + sizeof(struct Bullet) * size);
  group->nBullets = size;
  group->mother = mother;
  for (int i = 0;i < size;i++)
  {
    group->children[i].speed = mother->speed;
    Level_addBullet(group->children + i,level);
    group->children[i].object = Level_getObject(level);
    group->children[i].object->w = 1;
    group->children[i].object->h = 1;
    group->children[i].object->src.x = mother->object->src.x;
    group->children[i].object->src.y = mother->object->src.y;
    group->children[i].object->src.w = mother->object->src.w;
    group->children[i].object->src.h = mother->object->src.h;
    group->children[i].object->dst.w = mother->object->dst.w;
    group->children[i].object->dst.h = mother->object->dst.h;
    group->children[i].object->texture = mother->object->texture;
    group->children[i].object->alive = 0;
  }
  return group;
}


void BulletGroup_destroy(struct BulletGroup *group,struct Level *level)
{
  for (int i = 0;i < group->nBullets;i++)
  {
    group->children[i].object->alive = 0;
    group->children[i].object->reserved = 0;
    
  }
  free(group);
}


struct Bullet *BulletGroup_fire(float x,float y,float z,float angle,struct BulletGroup *group)
{
  for (int i = 0;i < group->nBullets;i++)
  {
    if (!group->children[i].object->alive)
    {
      group->children[i].vx = cos(angle);
      group->children[i].vy = sin(angle);
      group->children[i].vz = 0;
      group->children[i].object->x = x;
      group->children[i].object->y = y;
      group->children[i].object->z = z;
      group->children[i].object->alive = 1;
      return group->children + i;
    }
  }
  return NULL;
}
