#include "BulletGroup.h"

#include "Bullet.h"


struct BulletGroup *BulletGroup_create(int size,struct Bullet const *mother,struct Level *level)
{
  struct BulletGroup *group = malloc(sizeof(struct BulletGroup) + sizeof(struct Bullet *) * size);
  group->nBullets = size;
  group->mother = mother;
  for (int i = 0;i < size;i++) group->children[i] = Level_addObject(level);
}


struct Bullet *BulletGroup_add(float x,float y,struct BulletGroup *group)
{
  for (int i = 0;i < group->nBullets;i++)
  {
    if (!group->children[i]->alive)
    {
      group->children[i]->object->x = x;
      group->children[i]->object->y = y;
      group->children[i]->object->z = z;
      group->children[i]->alive = 69;
      return group->children[i];
    }
  }
  return NULL;
}
