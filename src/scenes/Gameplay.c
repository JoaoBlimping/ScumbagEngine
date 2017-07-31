#include "Gameplay.h"

#include "Scene.h"
#include "../Image.h"
#include "../Level.h"
#include "../Bullet.h"
#include "../BulletGroup.h"
#include "../Object.h"
#include "../render.h"


#define LEVEL_ARG 0


struct Level *level;
struct Object *dude;
struct Object *shadow;
struct Bullet const *bullet;
struct BulletGroup *bullets;



// TODO: this definitely doesn't belong here
void move(struct Level *level,struct Object *dude,float vx,float vy,float vz)
{
  if (!Level_checkSpace(level,dude->x + vx,dude->y,dude->z,dude->w,dude->h)) vx = 0;
  if (!Level_checkSpace(level,dude->x,dude->y + vy,dude->z,dude->w,dude->h)) vy = 0;
  if (!Level_checkSpace(level,dude->x,dude->y,dude->z + vz,dude->w,dude->h)) vz = 0;
  dude->x += vx;
  dude->y += vy;
  dude->z += vz;
}


void birth(int argc,char **argv)
{
  level = Level_loadLevel(argv[LEVEL_ARG]);
  render_setFillColour(level->backgroundColour);

  bullet = Bullet_get("dart");
  bullets = BulletGroup_create(10,bullet,level);

  dude = Level_getObject(level);
  dude->x = 20;
  dude->y = 20;
  dude->z = 1.6;
  dude->w = 0.8;
  dude->h = 1.5;
  dude->alive = 69;
  dude->src.x = dude->src.y = 0;
  dude->src.w = dude->dst.w = 64;
  dude->src.h = dude->dst.h = 128;
  dude->texture = Image_get("images/sproingo.png");

  shadow = Level_getObject(level);
  shadow->w = 1;
  shadow->h = 0.1;
  shadow->alive = 69;
  shadow->src.x = shadow->src.y = 0;
  shadow->src.w = shadow->dst.w = 64;
  shadow->src.h = shadow->dst.h = 48;
  shadow->texture = Image_get("images/shadow.png");
}


void update()
{
  Level_update(level);

  const uint8_t *currentKeyStates = SDL_GetKeyboardState(NULL);



  float vx = 0;
  float vy = 0;
  float vz = -0.1;
  if (currentKeyStates[SDL_SCANCODE_O]) vy = -0.1;
  if (currentKeyStates[SDL_SCANCODE_P]) vx = -0.1;
  if (currentKeyStates[SDL_SCANCODE_K]) vx = 0.1;
  if (currentKeyStates[SDL_SCANCODE_L]) vy = 0.1;
  if (currentKeyStates[SDL_SCANCODE_SPACE]) vz = 0.2;

  if (currentKeyStates[SDL_SCANCODE_Z]) BulletGroup_fire(dude->x,dude->y,dude->z,0,bullets);



  move(level,dude,vx,vy,vz);

  shadow->x = dude->x;
  shadow->y = dude->y;
  shadow->z = Level_floor(level,dude->x + dude->w / 2,dude->y + dude->w / 2,dude->z) + shadow->h + 0.03;
}


void render()
{
  SDL_RenderClear(render_renderer);
  Level_renderLevel(level,50 - (dude->x - dude->y) * 32 - 500,(dude->x + dude->y) * 24 - 500);
}


void death()
{
  BulletGroup_destroy(bullets,level);
  Level_free(level);
}





void Gameplay_init()
{
  struct Scene *scene = malloc(sizeof(struct Scene));
  scene->name = "gameplay";
  scene->birth = birth;
  scene->update = update;
  scene->render = render;
  scene->death = death;
  Scene_add(scene);
}
