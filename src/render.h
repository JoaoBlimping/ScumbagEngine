#ifndef RENDER_H
#define RENDER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



SDL_Window *render_window;
SDL_Renderer *render_renderer;



int render_init(char const *title,int width,int height,int fullscreen);

void render_close();

void render_update();

void render_setFillColour(int colour);


#endif
