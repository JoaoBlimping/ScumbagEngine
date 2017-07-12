#include "Level.h"

#include "Object.h"
#include "render.h"
#include "tmx/tmx.h"
#include <string.h>
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


void sortObjects(struct Level *level)
{
	struct Object **list = level->objects;
	int length = List_SIZE(level->objects);

	for (int i = 1;i < length;i++)
  {
    struct Object *temp = list[i];
    int j = i - 1;

    while (j >= 0 && (list[j]->x + list[j]->y + list[j]->z > temp->x + temp->y + temp->z || list[j]->z - list[j]->h > temp->z))
    {
      list[j + 1] = list[j];
      j--;
    }
    list[j + 1] = temp;
  }
}


void drawObjects(struct Level *level,int cameraX,int cameraY)
{
	int halfWidth = level->map->tile_width >> 1;
	int height = level->map->tile_height;
	int halfHeight = level->map->tile_height >> 1;



	List_ITERATE(level->objects,i)
	{
		struct Object *obj = level->objects[i];
		obj->dst.x = level->map->width - (obj->x - obj->y) * halfWidth - cameraX - halfWidth;
		obj->dst.y = (obj->x + obj->y) * halfHeight - obj->z * height - cameraY - (obj->src.h - height) + obj->h * height;

		SDL_RenderCopy(render_renderer,obj->texture,&obj->src,&obj->dst);
	}
}


void Level_init()
{
	tmx_img_load_func = textureLoader;
	tmx_img_free_func = SDL_DestroyTexture;
}



struct Level *Level_loadLevel(uint8_t const *filename)
{
	// Make the basic thing
	struct Level *level = calloc(sizeof(struct Level),1);
	List_INIT(level->objects);

	// Load in the tmx stuff
  level->map = tmx_load(filename);
  if (!level->map) tmx_perror("tmx_load");

	// Convert all layers into tiles, with -vertical offset of tiles setting z
	tmx_layer *layers = level->map->ly_head;
	while (layers)
	{
		float z = (0.0 - layers->offsety) / level->map->tile_height;


		for (int x = 0;x < level->map->height;x++)
	  {
			for (int y = 0;y < level->map->width;y++)
	    {
				int gid = GID_CLEAR_FLAG(layers->content.gids[(x * level->map->width) + y]);
				if (level->map->tiles[gid] != NULL)
	      {
					tmx_tileset *ts = level->map->tiles[gid]->tileset;
					struct Object *block = malloc(sizeof(struct Object));
					block->x = x;
					block->y = y;

					tmx_property *properties = level->map->tiles[gid]->properties;
					while (properties)
					{
						if (!strcmp(properties->name,"tallness"))
						{
							block->h = (float)level->map->tiles[gid]->properties->value.integer / level->map->tile_height;
							break;
						}
						properties = properties->next;
					}

					block->z = z + block->h;

					block->src.x = level->map->tiles[gid]->ul_x;
					block->src.y = level->map->tiles[gid]->ul_y;
					block->src.w = block->dst.w = level->map->tile_width;
					block->src.h = block->dst.h = ts->tile_height;

					block->texture = ts->image->resource_image;
					List_PUSH(level->objects,block);
				}
			}
		}
		layers = layers->next;
	}




  return level;
}


void Level_renderLevel(struct Level *level,int cameraX,int cameraY)
{
	sortObjects(level);
	drawObjects(level,cameraX,cameraY);
}
