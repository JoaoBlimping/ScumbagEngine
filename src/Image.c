#include "Image.h"

#include "ini.h"
#include "load.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>



struct load_Bucket *images;


void buildImage(char const *key,char const *file,SDL_Texture **item)
{
  char *url = ini_readString(file,key,"url","images/default.png");

  SDL_Surface *surface = IMG_Load(url);
  if (surface == NULL)
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n",url,IMG_GetError());
  }

  *item = SDL_CreateTextureFromSurface(render_renderer,surface);
  if (*item == NULL)
  {
    printf( "Unable to create texture from %s! SDL Error: %s\n",url,SDL_GetError());
  }
  SDL_FreeSurface(surface);
}



void Image_init()
{
  images = load_all("images.ini",buildImage,sizeof(SDL_Texture *));
}


SDL_Texture *Image_get(char const *key)
{
  SDL_Texture **image = load_get(key,images);
  if (image == NULL)
  {
    printf("can't get image at %s\n",key);
    return NULL;
  }
  return *image;
}
