#include "Image.h"

#include "ini.h"
#include "List.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>


#define MAX_IMAGES 0xff


SDL_Texture *List_CREATE(images,MAX_IMAGES);


void buildImage(char const *key)
{
  char *url = ini_readString(file,key,"url","images/default.png");

  SDL_Surface *surface = IMG_Load(url);
  if (surface == NULL) printf( "can't load image %s, SDL_image Error: %s\n",url,IMG_GetError());

  SDL_Texture *item = SDL_CreateTextureFromSurface(render_renderer,surface);
  if (item == NULL) printf( "can't create texture from %s, SDL Error: %s\n",url,SDL_GetError());
  SDL_FreeSurface(surface);

  return item;
}



SDL_Texture *Image_get(char const *key)
{
  // Try and get if it already exists
  List_ITERATE(images,i)
  {
    if (!strcmp(images[i] FUCK ))

  }

}
