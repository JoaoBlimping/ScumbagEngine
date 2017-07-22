#include "Bullet.h"

#include "load.h"
#include "Image.h"
#include "Object.h"
#include "ini.h"



struct load_Bucket *bullets;


void buildBullet(char const *key,char const *file,struct Bullet *item)
{
  item->speed = ini_readFloat(file,key,"speed",1);
  item->object = calloc(sizeof(struct Object),1);
  item->object->texture = Image_get(ini_readString(file,key,"key","sproingo"));
  item->object->w = ini_readFloat(file,key,"width",1);
  item->object->h = ini_readFloat(file,key,"height",1);

  item->object->src.x = 0;
  item->object->src.y = 0;
  item->object->src.w = 60;
  item->object->src.h = 60;
  item->object->dst.w = 40;
  item->object->dst.h = 40;
}


void Bullet_init()
{
  bullets = load_all("bullets.ini",buildBullet,sizeof(struct Bullet));
}


struct Bullet const *Bullet_get(char const *key)
{
  struct Bullet *bullet = load_get(key,bullets);
  if (bullet == NULL)
  {
    printf("can't get bullet at %s\n",key);
    return NULL;
  }
  return bullet;
}
