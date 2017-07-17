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
    group->children[i].object = Level_addObject(level);
    group->children[i].object->src.x = mother->object->src.x;
    group->children[i].object->src.y = mother->object->src.y;
    group->children[i].object->src.h = mother->object->src.w;
    group->children[i].object->src.x = mother->object->src.h;
    group->children[i].object->dst.h = mother->object->dst.w;
    group->children[i].object->dst.x = mother->object->dst.h;
  }
  return group;
}


struct Bullet *BulletGroup_add(float x,float y,float z,struct BulletGroup *group)
{
  for (int i = 0;i < group->nBullets;i++)
  {
    if (!group->children[i].object->alive)
    {
      group->children[i].object->x = x;
      group->children[i].object->y = y;
      group->children[i].object->z = z;
      group->children[i].object->alive = 69;
      return group->children + i;
    }
  }
  return NULL;
}
