/**  _     || || /   / VAEDSOM GEDARMEM SOMOARSE
 *  |_\ /\ || || >  / VAEDSOM GEDARMEM SOMOARSE
 *  |   \/ \/ || \ / VAEDSOM GEDARMEM SOMOARSE
 *   \____________/ */
#include "Image.h"
#include "BulletGroup.h"
#include "Level.h"
#include "load.h"
#include "Bullet.h"
#include "render.h"
#include <stdint.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



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





void loop()
{
  struct Level *level = Level_loadLevel("maps/street.tmx");

  struct Object *dude = Level_getObject(level);
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


  struct Object *shadow = Level_getObject(level);
  shadow->w = 1;
  shadow->h = 0.1;
  shadow->alive = 69;
  shadow->src.x = shadow->src.y = 0;
  shadow->src.w = shadow->dst.w = 64;
  shadow->src.h = shadow->dst.h = 48;
  shadow->texture = Image_get("images/shadow.png");

  struct Bullet const *bullet = Bullet_get("dart");

  struct BulletGroup *bullets = BulletGroup_create(50,bullet,level);




  int x = 0;
  int y = 100;

  float angle = 0;


  render_setFillColour(level->backgroundColour);



  SDL_Event e;
  while (69)
  {
    while(SDL_PollEvent(&e) != 0) if(e.type == SDL_QUIT) return;

    SDL_RenderClear(render_renderer);
    Level_update(level);
    Level_renderLevel(level,x,y);
    render_update();


    const uint8_t *currentKeyStates = SDL_GetKeyboardState(NULL);



    float vx = 0;
    float vy = 0;
    float vz = -0.1;
    if (currentKeyStates[SDL_SCANCODE_O]) vy = -0.1;
    if (currentKeyStates[SDL_SCANCODE_P]) vx = -0.1;
    if (currentKeyStates[SDL_SCANCODE_K]) vx = 0.1;
    if (currentKeyStates[SDL_SCANCODE_L]) vy = 0.1;
    if (currentKeyStates[SDL_SCANCODE_SPACE]) vz = 0.2;

    if ((vx != 0 || vy != 0) && !currentKeyStates[SDL_SCANCODE_LSHIFT]) angle = atan2(vy,vx);

    if (currentKeyStates[SDL_SCANCODE_Z]) BulletGroup_fire(dude->x,dude->y,dude->z,angle,bullets);

    x = 50 - (dude->x - dude->y) * 32 - 500;
    y = (dude->x + dude->y) * 24 - 500;



    move(level,dude,vx,vy,vz);

    shadow->x = dude->x;
    shadow->y = dude->y;
    shadow->z = Level_floor(level,dude->x + dude->w / 2,dude->y + dude->w / 2,dude->z) + shadow->h + 0.03;
  }
}



int main(int argc,char **argv)
{
  // Get the render system working
  render_init("big boopwreopwr",900,666,argc > 1);

  // Now load some images
  Image_init();
  Level_init();
  Bullet_init();

  // Now do something cool
  loop();

  // Closing up
  render_close();

  return 0;
}


/**************************************************************************************************
 * Hey did you notice how I am putting the whole program's args into the starting scene?          *
 *          That is going to be real handy for some testing features and shit                     *
 *    sadly, only linux users are likely to ever get to use it, no actually, anywhere you have a  *
 * commandline run of it, you should be able to put in commanline arguments and get it to do weird*
 *                             stuff             .                                                *
 *                                              / \                                               *
 *               .                  C)         /   \                                              *
 *              / \                 C )       /  .  \                                             *
 *      .      /   \                         /  / \  \    ,                                       *
 *     / \    /     \                       /. /   \  \  / \                                      *
 *    /   \  /       \                     /. /     \  \/   \                                     *
 * __/     \/.        \___________________/  /       \ /  .  \___________________________________ *
 *  /       \     .    \            ~     ~ /         /       \                  ~                *
 * /         \          \   ~           ~  /         /         ~                                  *
 **************************************************************************************************
 ########Oo::::................OOOO888888888########88888888OOOoooOOOo:... .oOOO:... ..:. ........*
 ########8oo:::................O8Oo8888888#######88888888OOOooooooooooo:.. :oOOo:... . .o: .......*
 ########Ooo::::..............:O8OO88888888####888OOOOOOOOoo::o::..:::oo: .:OOoo:... ... .... ....*
 #####88OOoo::::..............:O8OOOO888888#888OOOoooooOOOo:::...::::ooo:. .:ooOO:.... ........ ..*
 OOOOOOoooo:::::..............:O8OOOO88888888Ooo::::::ooOOo::...:::::::::. ::oooo:.... ......:::oo*
 oooooooo::::::...............:O8OOoOOO8888Oo::::::::::o888o:....:::::::::. .:oooO::.....::::::...*
 ooo::::::::::..o::...........:O8OoOOOO888OooooOOo::::.o8#8O:........:::::.. .:ooooo::::::........*
 ::::::::::::....::...........:O8ooOOOO888OooOOOOOo:::.o8##8o:......::ooo::. .:ooooOo:............*
 ::::::::::...................:OOoOOOoO888OooooOOo:::::O8##8Oo:.....::oooo:.. :ooooOo:............*
 ::::::::.....................:oOOOOooO888Oooooo....:o8888##Oooo::::oooooo:....oooooOo:...........*
 ::::::.......................::o8oOooO8888OOOOo:::::O888###8OooOO88888OOoo. ..:ooooOo:...........*
 ::::::......................:::O8ooooO88888#88Oo::oO8888###88OOoO888888Ooo. .:::oOOoo::..........*
 ::::::::....................:::O8OooOO8#8#######88#8888###88OOOooOOOOOOOoo: ::::oooOo:...........*
 :::::::::::.................::oO8O8OOO8#8888#######88O888OOoo::::oOOOooooo: .:::ooooOo:..........*
 OOOooooo::::....... ........:oOO88o:OOO888888####88OooOo:::::..:::oooo::::: .::::oooOo::.:.......*
 888OOOooo::::...... ...::..::ooo8O:.oOO8888888#888Ooo:o:...::..:::::::::::: ..::::oooOOo:..:.....*
 8888OOoo::::........ ...:.::oooo88:.oOoO888888888OOo::oo.....::::::..:::::: ..::::oooOOOo:.......*
 OOOooo:::.......:........:::oooo88Oo8OooO88888OOOoo:::oOO:...::oo:::..::::: .:::::oooOOO::.......*
 o:::....::::::::..:::::::::ooooo888O8OooO88OOOOoo:::::o888Oo:::::::..:::::: .:::::ooooOOo:::.....*
 o:.::::::...::::::::::::::oo::oo888OOOO8O88OOOoo::::::O88Oo:..........::::: .:::::oooOOOo:::.... *
 :::...::::::::::::::::::::o:::oo88888OO88O88OOOoo:::::OOo.......:::::.::::: .::::o:oOoOOo::... ..*
 ::::::::::::::::::::....:::::o:oO88888888oO8OOOOoo::...::oOOOoo:::::::::::. ::::::oooOOo::......:*
 :::::::::::::::::::.....:::::::OO88888OO:..OOOOoooo::.oOOOoooo::::::::::::. ..:::::oooOO:::::....*
 :::::::::::::::::::.....::::::ooOO8888OOo::oOOOOoo:::oO8OOo:::::::oooo:::: ..:::::ooooOo:::::....*
 :.......:::..::::.......:::::o:ooOO888OO8OOOOOOOooo::OO88OOOoooOOOOooo:::. .::::::oooOo:..::.....*
 ........:......::.::....:.::o:ooooO888OO8888OOOoooooOO88888##8888OOoo:::. .::::::ooooO::..::.....*
 .........:..::::........:::::::ooo8O88OO8O888oooooooOO88888888OOOooo:::. ..::::::ooooOo::..:.....*
 .........::.::::.........:::::::oOOO88OO88O88Oo:oooooOO88888OOoo::::::. .:.:::::ooooO::..........*
 ...............:.........:::::::oooOO8OO888O8OO:::oooooOOOOOoo::::::... . .:.::::::oooOo.::......*
 ...........................:::::ooo:O8OOO888OOOO:..:::::::::::........ . ..:::::::ooooo:.:.......*
 ...........................:::::oo::o8OOO888OOOOo:....::::........... . ..:::.:::oooo::..........*
 ..........................:...:oooo:oOoooO888OOOOo.. ................ .. ..::::.::ooooo:.........*
 .............................:::o:::ooO::oO88OOOOO:.................. .. ...:::.:::oooo::.:......*
 .....................:......:::::.::::O:.:o8O8OO8Oo:................. .... ..::::.:::ooo:::..... *
 .........................::o::::::....oo:::oOOOoOOoo................ .... ..:::::.::oooo:::... ..*
 ........................oo:..::.::....:o:::.oOOOoOooo............... .... .:::::::::ooo::::... . *
 ......................::::..:..........o:::.:OOOooooo:.............. ..... ...::::::::::oo:::....*/
