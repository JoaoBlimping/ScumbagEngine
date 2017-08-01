#include "font.h"

#include "load.h"
#include "render.h"
#include "HashMap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#define HASH_SIZE 0x100
#define TEXT_SIZE 200


struct HashMap *fontMap;

char const *defaultFont;


TTF_Font *buildFont(char const *key)
{
  TTF_Font *font = TTF_OpenFont(key,TEXT_SIZE);
  if(!font) printf("Failed to load font %s! SDL_ttf Error: %s\n",key,TTF_GetError());
  return font;
}


TTF_Font *getFont(char const *key)
{
  TTF_Font *font = HashMap_get(fontMap,(key ? key : defaultFont));
  if (!font)
  {
    font = buildFont(key);
    HashMap_add(fontMap,key,font);
  }
  return font;
}



void font_init(char const *pDefaultFont)
{
  // turn on TTF fonts
  if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());

  // set up the hashmap
  fontMap = HashMap_create(HASH_SIZE);

  // load and set the default
  getFont(pDefaultFont);
  defaultFont = pDefaultFont;
}


SDL_Texture *font_renderText(char const *text,char const *font,int colour)
{
  TTF_Font *renderFont = getFont(font);
  SDL_Color renderColour;
  render_setColour(&renderColour,colour);
  SDL_Surface* textSurface = TTF_RenderText_Solid(renderFont,text,renderColour);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(render_renderer,textSurface);
  SDL_FreeSurface(textSurface);
  return texture;
}
