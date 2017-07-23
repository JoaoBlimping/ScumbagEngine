#include "Gameplay.h"

#include "Scene.h"


#define LEVEL_ARG 1


struct Scene scene;

struct Level *level;

struct Object dude;
struct Object shadow;


struct Bullet *bullet

struct BulletGroup *bullets;


void birth(int argc,char **argv)
{
  level = Level_loadLevel(argv[LEVEL_ARG]);

  dude.x = 20;
  dude.y = 20;
  dude.z = 1.6;
  dude.w = 0.8;
  dude.h = 1.5;
  dude.alive = 69;
  dude.src.x = dude.src.y = 0;
  dude.src.w = dude.dst.w = 64;
  dude.src.h = dude.dst.h = 128;
  dude.texture = Image_get("images/sproingo.png");

  shadow.w = 1;
  shadow.h = 0.1;
  shadow.alive = 69;
  shadow.src.x = shadow.src.y = 0;
  shadow.src.w = shadow.dst.w = 64;
  shadow.src.h = shadow.dst.h = 48;
  shadow.texture = Image_get("images/shadow.png");

  bullet = Bullet_get("dart");
  bullets = BulletGroup_create(10,bullet,level);
}


void update()
{

}


void render()
{

}

void death()
{

}




struct Scene *Gameplay_get()
{
  scene->birth = birth;
  scene->update = update;
  scene->render = render;
  scene->death = death;
  return scene;
}
