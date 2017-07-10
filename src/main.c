/**  _     || || /   / VAEDSOM GEDARMEM SOMOARSE
 *  |_\ /\ || || >  / VAEDSOM GEDARMEM SOMOARSE
 *  |   \/ \/ || \ / VAEDSOM GEDARMEM SOMOARSE
 *   \____________/ */
#include "Image.h"
#include "Level.h"
#include "render.h"
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>





void loop()
{
  struct Level *level = Level_loadLevel("maps/street.tmx");

  int x = 0;
  int y = 0;

  render_setFillColour(level->map->backgroundcolor);

  

  int i = 0;
  SDL_Event e;
  while (69)
  {
    while(SDL_PollEvent(&e) != 0) if(e.type == SDL_QUIT) return;

    //SDL_RenderClear(render_renderer);
    Level_renderLevel(level,x,y);
    render_update();


    const uint8_t *currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_UP]) y -= 3;
    if(currentKeyStates[SDL_SCANCODE_DOWN]) y += 3;
    if(currentKeyStates[SDL_SCANCODE_LEFT]) x -= 3;
    if(currentKeyStates[SDL_SCANCODE_RIGHT]) x += 3;
  }






}



int main(int argc, uint8_t **argv)
{
  // Get the render system working
  render_init("big boopwreopwr",900,666,argc > 1);

  // Now load some images
  Image_init();
  Level_init();

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
 ########Oo::::................OOOO888888888########88888888OOOoooOOOo:... .oOOO:... ..:. ........
########8oo:::................O8Oo8888888#######88888888OOOooooooooooo:.. :oOOo:... . .o: ........
########Ooo::::..............:O8OO88888888####888OOOOOOOOoo::o::..:::oo: .:OOoo:... ... .... .....
#####88OOoo::::..............:O8OOOO888888#888OOOoooooOOOo:::...::::ooo:. .:ooOO:.... ........ ...
OOOOOOoooo:::::..............:O8OOOO88888888Ooo::::::ooOOo::...:::::::::. ::oooo:.... ......:::ooo
oooooooo::::::...............:O8OOoOOO8888Oo::::::::::o888o:....:::::::::. .:oooO::.....::::::....
ooo::::::::::..o::...........:O8OoOOOO888OooooOOo::::.o8#8O:........:::::.. .:ooooo::::::.........
::::::::::::....::...........:O8ooOOOO888OooOOOOOo:::.o8##8o:......::ooo::. .:ooooOo:.............
::::::::::...................:OOoOOOoO888OooooOOo:::::O8##8Oo:.....::oooo:.. :ooooOo:.............
::::::::.....................:oOOOOooO888Oooooo....:o8888##Oooo::::oooooo:....oooooOo:............
::::::.......................::o8oOooO8888OOOOo:::::O888###8OooOO88888OOoo. ..:ooooOo:............
::::::......................:::O8ooooO88888#88Oo::oO8888###88OOoO888888Ooo. .:::oOOoo::...........
::::::::....................:::O8OooOO8#8#######88#8888###88OOOooOOOOOOOoo: ::::oooOo:............
:::::::::::.................::oO8O8OOO8#8888#######88O888OOoo::::oOOOooooo: .:::ooooOo:...........
OOOooooo::::....... ........:oOO88o:OOO888888####88OooOo:::::..:::oooo::::: .::::oooOo::.:........
888OOOooo::::...... ...::..::ooo8O:.oOO8888888#888Ooo:o:...::..:::::::::::: ..::::oooOOo:..:......
8888OOoo::::........ ...:.::oooo88:.oOoO888888888OOo::oo.....::::::..:::::: ..::::oooOOOo:........
OOOooo:::.......:........:::oooo88Oo8OooO88888OOOoo:::oOO:...::oo:::..::::: .:::::oooOOO::........
o:::....::::::::..:::::::::ooooo888O8OooO88OOOOoo:::::o888Oo:::::::..:::::: .:::::ooooOOo:::......
o:.::::::...::::::::::::::oo::oo888OOOO8O88OOOoo::::::O88Oo:..........::::: .:::::oooOOOo:::.... .
:::...::::::::::::::::::::o:::oo88888OO88O88OOOoo:::::OOo.......:::::.::::: .::::o:oOoOOo::... ...
::::::::::::::::::::....:::::o:oO88888888oO8OOOOoo::...::oOOOoo:::::::::::. ::::::oooOOo::......:.
:::::::::::::::::::.....:::::::OO88888OO:..OOOOoooo::.oOOOoooo::::::::::::. ..:::::oooOO:::::.....
:::::::::::::::::::.....::::::ooOO8888OOo::oOOOOoo:::oO8OOo:::::::oooo:::: ..:::::ooooOo:::::.....
:.......:::..::::.......:::::o:ooOO888OO8OOOOOOOooo::OO88OOOoooOOOOooo:::. .::::::oooOo:..::......
........:......::.::....:.::o:ooooO888OO8888OOOoooooOO88888##8888OOoo:::. .::::::ooooO::..::......
.........:..::::........:::::::ooo8O88OO8O888oooooooOO88888888OOOooo:::. ..::::::ooooOo::..:......
.........::.::::.........:::::::oOOO88OO88O88Oo:oooooOO88888OOoo::::::. .:.:::::ooooO::...........
...............:.........:::::::oooOO8OO888O8OO:::oooooOOOOOoo::::::... . .:.::::::oooOo.::.......
...........................:::::ooo:O8OOO888OOOO:..:::::::::::........ . ..:::::::ooooo:.:........
...........................:::::oo::o8OOO888OOOOo:....::::........... . ..:::.:::oooo::...........
..........................:...:oooo:oOoooO888OOOOo.. ................ .. ..::::.::ooooo:..........
.............................:::o:::ooO::oO88OOOOO:.................. .. ...:::.:::oooo::.:.......
.....................:......:::::.::::O:.:o8O8OO8Oo:................. .... ..::::.:::ooo:::..... .
.........................::o::::::....oo:::oOOOoOOoo................ .... ..:::::.::oooo:::... ...
........................oo:..::.::....:o:::.oOOOoOooo............... .... .:::::::::ooo::::... . .
......................::::..:..........o:::.:OOOooooo:.............. ..... ...::::::::::oo:::.... */
