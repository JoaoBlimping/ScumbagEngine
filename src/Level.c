#include "Level.h"

#include "Bullet.h"
#include "Object.h"
#include "render.h"
#include "tmx/tmx.h"
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define BUFFER_SIZE 0xf
#define TILE_INDEX(x,y,width) (x * width) + y
#define GID_CLEAR_FLAG(gid) (gid & TMX_FLIP_BITS_REMOVAL)



SDL_Texture *textureLoader(char const *file)
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
	int halfWidth = level->tileWidth >> 1;
	int height = level->tileHeight;
	int halfHeight = level->tileHeight >> 1;

	List_ITERATE(level->objects,i)
	{
		struct Object *obj = level->objects[i];
		if (!obj->alive) continue;
		obj->dst.x = level->width - (obj->x - obj->y) * halfWidth - cameraX - halfWidth;
		obj->dst.y = (obj->x + obj->y) * halfHeight - obj->z * height - cameraY - (obj->src.h - height) + obj->h * height;
		SDL_RenderCopy(render_renderer,obj->texture,&obj->src,&obj->dst);
	}
}


void Level_init()
{
	tmx_img_load_func = textureLoader;
	tmx_img_free_func = SDL_DestroyTexture;
}



struct Level *Level_loadLevel(char const *filename)
{
	// Load in the tmx stuff
  tmx_map *map = tmx_load(filename);
  if (!map) tmx_perror("tmx_load");

	// Make the basic thing
	struct Level *level = calloc(sizeof(struct Level),1);
	List_INIT(level->objects);
	List_INIT(level->bullets);
	level->width = map->width;
	level->breadth = map->height;
	level->tileWidth = map->tile_width;
	level->tileHeight = map->tile_height;
	level->backgroundColour = map->backgroundcolor;
	level->tiledMap = map;

	// Create buffers for the things we don't know the length of yet
	float *collisionBuffer[BUFFER_SIZE];
	float heightBuffer[BUFFER_SIZE];

	// Convert all layers into tiles, with -vertical offset of tiles setting z
	int i = 0;
	tmx_layer *layers = map->ly_head;
	while (layers)
	{
		heightBuffer[i] = (0.0 - layers->offsety) / map->tile_height;
		collisionBuffer[i] = calloc(sizeof(int),map->width * map->height);

		for (int x = 0;x < map->height;x++)
	  {
			for (int y = 0;y < map->width;y++)
	    {
				int gid = GID_CLEAR_FLAG(layers->content.gids[(x * map->width) + y]);
				if (map->tiles[gid] != NULL)
	      {
					tmx_tileset *ts = map->tiles[gid]->tileset;
					struct Object *block = malloc(sizeof(struct Object));
					block->x = x;
					block->y = y;
					block->alive = 69;

					tmx_property *properties = map->tiles[gid]->properties;
					while (properties)
					{
						if (!strcmp(properties->name,"tallness"))
						{
							float blockHeight = (float)map->tiles[gid]->properties->value.integer / map->tile_height;
							block->h = blockHeight;
							collisionBuffer[i][TILE_INDEX(x,y,map->width)] = blockHeight;
							break;
						}
						properties = properties->next;
					}

					block->z = heightBuffer[i] + block->h;

					block->src.x = map->tiles[gid]->ul_x;
					block->src.y = map->tiles[gid]->ul_y;
					block->src.w = block->dst.w = map->tile_width;
					block->src.h = block->dst.h = ts->tile_height;

					block->texture = ts->image->resource_image;
					List_PUSH(level->objects,block);
				}
			}
		}
		level->nLayers++;
		layers = layers->next;
		i++;
	}

	// put the bufferss into the level
	level->collisions = malloc(sizeof(int *) * level->nLayers);
	level->heights = malloc(sizeof(int) * level->nLayers);
	memcpy(level->collisions,collisionBuffer,sizeof(int *) * level->nLayers);
	memcpy(level->heights,heightBuffer,sizeof(int) * level->nLayers);

  return level;
}


int Level_checkSpace(struct Level *level,float x,float y,float z,float w,float h)
{
	for (int l = 0;l < level->nLayers;l++)
	{
		float layerBottom = level->heights[l];
		float layerTop;
		if (l < level->nLayers) layerTop = level->heights[l + 1];
		else layerTop = layerBottom;

		// If this layer intersects the space
		if ((layerTop >= z) || (layerBottom <= z))
		{
			for (int ix = (int)x;ix < (int)ceil(x + w);ix++)
			{
				for (int iy = (int)y;iy < (int)ceil(y + w);iy++)
				{
					float tileHeight = level->collisions[l][TILE_INDEX(ix,iy,level->width)];
					if ((layerBottom + tileHeight >= z - h) && tileHeight) return 0;
					if (x < 0 || y < 0 || ix >= level->width || iy >= level->breadth) return 0;
				}
			}
		}
	}
	return 69;
}


float Level_floor(struct Level *level,float x,float y,float z)
{
	float height = -100;
	for (int l = 0;l < level->nLayers;l++)
	{
		float layerBottom = level->heights[l];
		if (z >= layerBottom )
		{
			float tileHeight = level->collisions[l][TILE_INDEX((int)x,(int)y,level->width)];
			if (layerBottom + tileHeight > height && tileHeight) height = layerBottom + tileHeight;
		}
	}
	return height;
}


struct Object *Level_addObject(struct Level *level)
{
	struct Object *obj = calloc(sizeof(struct Object),1);
	List_PUSH(level->objects,obj);
	return obj;
}


void Level_addBullet(struct Bullet *bullet,struct Level *level)
{
	List_PUSH(level->bullets,bullet);
}


void Level_update(struct Level *level)
{
	List_ITERATE(level->bullets,i)
	{
		if (!level->bullets[i]->object->alive) continue;
		float x = level->bullets[i]->object->x + level->bullets[i]->vx;
		float y = level->bullets[i]->object->y + level->bullets[i]->vy;
		float z = level->bullets[i]->object->z + level->bullets[i]->vz;

		if (!Level_checkSpace(level,x,y,z,level->bullets[i]->object->w,level->bullets[i]->object->h))
		{
			level->bullets[i]->object->alive = 0;
		}
		else
		{
			level->bullets[i]->object->x += level->bullets[i]->vx;
			level->bullets[i]->object->y += level->bullets[i]->vy;
			level->bullets[i]->object->y += level->bullets[i]->vz;
		}
	}

}


void Level_renderLevel(struct Level *level,int cameraX,int cameraY)
{
	sortObjects(level);
	drawObjects(level,cameraX,cameraY);
}


void Level_free(struct Level *level)
{
	for (int i = 0;i < level->nLayers;i++) free(level->collisions[i]);
	free(level->collisions);
	free(level->heights);
	List_ITERATE(level->objects,i) free(level->objects[i]);
	tmx_map_free(level->tiledMap);
}
