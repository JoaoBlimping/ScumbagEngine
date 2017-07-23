#include "Image.h"

#include "ini.h"
#include "HashMap.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>


#define HASH_SIZE 0x100



struct HashMap *imageMap;


SDL_Texture *buildImage(char const *key)
{
  SDL_Surface *surface = IMG_Load(key);
  if (surface == NULL) printf( "can't load image %s, SDL_image Error: %s\n",key,IMG_GetError());

  SDL_Texture *item = SDL_CreateTextureFromSurface(render_renderer,surface);
  if (item == NULL) printf( "can't create texture from %s, SDL Error: %s\n",key,SDL_GetError());
  SDL_FreeSurface(surface);

  return item;
}




void Image_init()
{
  imageMap = HashMap_create(HASH_SIZE);
}



SDL_Texture *Image_get(char const *key)
{
  SDL_Texture *image = HashMap_get(imageMap,key);
  if (image == NULL)
  {
    image = buildImage(key);
    HashMap_add(imageMap,key,image);
  }
  return image;
}
