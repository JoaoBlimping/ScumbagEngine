/**  _     || || /   / VAEDSOM GEDARMEM SOMOARSE
 *  |_\ /\ || || >  / VAEDSOM GEDARMEM SOMOARSE
 *  |   \/ \/ || \ / VAEDSOM GEDARMEM SOMOARSE
 *   \____________/ */
#include "Image.h"
#include "Level.h"
#include "Bullet.h"
#include "render.h"
#include "gui.h"
#include "scenes/Scene.h"
#include "scenes/Gameplay.h"
#include <stdint.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int main(int argc,char **argv)
{
  // Get the render system working
  render_init("big boopwreopwr",900,666,argc > 1);

  // Now load some images
  Image_init();
  gui_init();
  Level_init();
  Bullet_init();
  Gameplay_init();

  // Put in the first scene
  char *file = "maps/street.tmx";
  Scene_set("gameplay",1,&file);

  // set up some random gui
  gui_set(gui_get("textbox"));

  // Now do something cool
  while (69)
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) if(e.type == SDL_QUIT) return 0;
    Scene_update();
    Scene_render();
    render_update();
  }

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
