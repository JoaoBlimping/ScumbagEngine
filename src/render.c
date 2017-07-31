#include "render.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


int render_init(char const *title,int width,int height,int fullscreen)
{
  // Create window
  if (fullscreen)
  {
    render_window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,
                                    height,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
  }
  else
  {
    render_window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,
                                    height,SDL_WINDOW_SHOWN);
  }

  if (render_window == NULL)
  {
    printf("sdl can't make window, error: %s\n",SDL_GetError());
    return 1;
  }

  // Create renderer for window
  render_renderer = SDL_CreateRenderer(render_window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (render_renderer == NULL)
  {
    printf("Couldn't get SDL Renderer going :( SDL Error:%s\n",SDL_GetError());
    return 1;
  }
  SDL_SetRenderDrawColor(render_renderer,0xFF,0xaa,0x69,0xFF);

  // Turn on PNG Loading
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",IMG_GetError());
    return 1;
  }

  // turn on TTF fonts
  if(TTF_Init() == -1)
  {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());
      return 1;
  }


  // TODO: move this to it's own file later to allow multiple fonts and cool shit like that
  render_font = TTF_OpenFont("font.ttf",28);
  if(render_font == NULL)
  {
    printf("Failed to load font.ttf! SDL_ttf Error: %s\n",TTF_GetError());
    return 1;
  }



  return 0;
}


void render_close()
{
  SDL_DestroyRenderer(render_renderer);
  SDL_DestroyWindow(render_window);
  IMG_Quit();
  TTF_Quit();
}


void render_update()
{
  SDL_Color colour = {255,0,0,0};
  TTF_RenderText_Solid(render_font,"idiota",colour);
  SDL_RenderPresent(render_renderer);
}


void render_setFillColour(int colour)
{
	SDL_SetRenderDrawColor(render_renderer,(colour >> 16) & 0xff,(colour >> 8) & 0xff,colour & 0xff,0xff);
}
