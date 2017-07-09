#include "Tileset.h"

#include "Image.h"
#include "load.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define TILESET_WIDTH 16



struct Tileset *tilesets;


void buildTileset(char const *key,char const *file,struct Tileset *item)
{
  char *image = ini_readString(file,key,"image","default");
  item->texture = Image_get(1);
  SDL_QueryTexture(item->texture,NULL,NULL,&item->src.w,&item->src.h);
  item->src.w /= TILESET_WIDTH * 2;
  item->src.h /= TILESET_WIDTH;
  item->dst.w = item->src.w;
  item->dst.h = item->src.h;
}





void Tileset_init()
{
  tilesets = load_all("tilesets.ini",buildTileset,sizeof(struct Tileset));
}


struct Tileset *Tileset_get(int index)
{
  return tilesets + index;
}


void Tileset_render(struct Tileset *tileset,uint8_t tile,int x,int y)
{
  tileset->src.x = tile % TILESET_WIDTH * tileset->src.w;
  tileset->src.y = tile / TILESET_WIDTH * tileset->src.h;
  tileset->dst.x = x;
  tileset->dst.y = y;
  SDL_RenderCopy(render_renderer,tileset->texture,&tileset->src,&tileset->dst);
}
