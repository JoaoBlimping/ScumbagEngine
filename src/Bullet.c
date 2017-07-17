#include "Bullet.h"

#include "load.h"
#include "Image.h"
#include "Object.h"
#include "ini.h"



struct load_Bucket *bullets;


void buildBullet(char const *key,char const *file,struct Bullet *item)
{
  item->object = calloc(sizeof(struct Object),1);
  char *textureKey = ini_readString(file,key,"key","sproingo");
  item->vx = 1;
  item->object->texture = Image_get(textureKey);
  item->object->w = ini_readFloat(file,key,"width",1);
  item->object->h = ini_readFloat(file,key,"height",1);
}


void Bullet_init()
{
  bullets = load_all("bullets.ini",buildBullet,sizeof(struct Bullet));
}


struct Bullet *Bullet_get(char const *key)
{
  struct Bullet *bullet = load_get(key,bullets);
  if (bullet == NULL)
  {
    printf("can't get bullet at %s\n",key);
    return NULL;
  }
  return bullet;
}
