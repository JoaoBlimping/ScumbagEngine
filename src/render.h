#ifndef RENDER_H
#define RENDER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


/** the window */
SDL_Window *render_window;
/** the renderer used to render stuff onto the screen */
SDL_Renderer *render_renderer;


/** gets the renderer ready to render stuff */
int render_init(char const *title,int width,int height,int fullscreen);

/** turns off the renderer and gets rid of the stuff that it has in memory */
void render_close();

/** renders the stuff that you have put into the renderer right oN THE SSCREEENNENE!!!! */
void render_update();

/** set's sdl's background colour
 * @param colour is the colour to set it to */
void render_setFillColour(int colour);

/** fills an existing sdl colour with a certain colour defined in an int
 * @param colourObject is the sdl colour we are filling
 * @param colour is the colour that we are filling it with */
void render_setColour(SDL_Color *colourObject,int colour);


#endif
