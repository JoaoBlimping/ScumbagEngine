#include "Bullet.h"

#include "load.h"
#include "Image.h"
#include "Object.h"
#include "ini.h"



struct HashMap *bullets;


void buildBullet(char const *key,char const *file,void *item)
{
  struct Bullet *bullet = (struct Bullet *)item;
  bullet->speed = ini_readFloat(file,key,"speed",1);
  bullet->object = calloc(sizeof(struct Object),1);
  bullet->object->texture = Image_get(ini_readString(file,key,"key","sproingo"));
  bullet->object->w = ini_readFloat(file,key,"width",1);
  bullet->object->h = ini_readFloat(file,key,"height",1);

  bullet->object->src.x = 0;
  bullet->object->src.y = 0;
  bullet->object->src.w = 60;
  bullet->object->src.h = 60;
  bullet->object->dst.w = 40;
  bullet->object->dst.h = 40;
}


void Bullet_init()
{
  bullets = load_all("bullets.ini",buildBullet,sizeof(struct Bullet));
}


struct Bullet const *Bullet_get(char const *key)
{
  struct Bullet *bullet = HashMap_get(bullets,key);
  if (bullet == NULL)
  {
    printf("can't get bullet at %s\n",key);
    return NULL;
  }
  return bullet;
}
