#include "gui.h"

#include "Image.h"
#include "load.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct load_Bucket *elements;



void buildElement(char const *key,char const *file,struct gui_Element *item)
{


}



void gui_init()
{
  elements = load_all("gui.ini",buildElement,sizeof(struct gui_Element));
}


struct gui_Element *gui_get(char const *key)
{
  struct gui_Element *element = load_get(key,elements);
  if (element == NULL)
  {
    printf("can't get gui element at %s\n",key);
    return NULL;
  }
  return element;
}


int gui_update()
{

}


void gui_render()
{

}
