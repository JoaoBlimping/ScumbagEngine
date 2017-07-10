#include "Level.h"

#include "render.h"
#include "tmx/tmx.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



#define GID_CLEAR_FLAG(gid) (gid & TMX_FLIP_BITS_REMOVAL)


SDL_Texture *textureLoader(uint8_t const *file)
{
	SDL_Surface *surface = IMG_Load(file);
  if (surface == NULL)
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n",file,IMG_GetError());
    return NULL;
  }
  SDL_Texture *item = SDL_CreateTextureFromSurface(render_renderer,surface);
  if (item == NULL)
  {
    printf( "Unable to create texture from %s! SDL Error: %s\n",file,SDL_GetError());
  }
  SDL_FreeSurface(surface);
	return item;
}




void drawLayer(tmx_map *map,tmx_layer *layer,int offsetX,int offsetY)
{
	unsigned int gid;
	float op;
	tmx_tileset *ts;
	SDL_Rect src,dst;
	SDL_Texture *tileset;
	op = layer->opacity;


	gid = GID_CLEAR_FLAG(layer->content.gids[0]);
	ts = map->tiles[gid]->tileset;
	src.w = dst.w = ts->tile_width;
	src.h = dst.h = ts->tile_height;

	int halfWidth = map->tile_width >> 1;
	int halfHeight = map->tile_height >> 1;


	for (int x = 0;x < map->height;x++)
  {
		for (int y = 0;y < map->width;y++)
    {
			gid = GID_CLEAR_FLAG(layer->content.gids[(x * map->width) + y]);
			if (map->tiles[gid] != NULL)
      {
				ts = map->tiles[gid]->tileset;
				src.x = map->tiles[gid]->ul_x;
				src.y = map->tiles[gid]->ul_y;

				dst.x = map->width - (x - y) * halfWidth - offsetX;
				dst.y = (x + y) * halfHeight - offsetY;
				SDL_RenderCopy(render_renderer,ts->image->resource_image,&src,&dst);
			}
		}
	}
}


void Level_init()
{
	tmx_img_load_func = textureLoader;
	tmx_img_free_func = SDL_DestroyTexture;
}



struct Level *Level_loadLevel(uint8_t const *filename)
{
	struct Level *level = calloc(sizeof(struct Level),1);
  level->map = tmx_load(filename);
  if (!level->map) tmx_perror("tmx_load");
  return level;
}


void Level_renderLevel(struct Level *level,int cameraX,int cameraY)
{
  drawLayer(level->map,level->map->ly_head,cameraX,cameraY);
}
