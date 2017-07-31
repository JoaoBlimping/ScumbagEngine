#include "gui.h"

#include "Image.h"
#include "load.h"
#include "render.h"
#include "ini.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct HashMap *elements;
struct gui_Element *gui = NULL;


void buildElement(char const *key,char const *file,void *item)
{
  struct gui_Element *element = (struct gui_Element *)item;
  element->dst.x = ini_readInt(file,key,"x",0);
  element->dst.y = ini_readInt(file,key,"y",0);
  element->dst.w = ini_readInt(file,key,"w",100);
  element->dst.h = ini_readInt(file,key,"h",100);
  element->content = Image_get(ini_readString(file,key,"skin","default"));
  element->type = ini_readInt(file,key,"type",0);
}



void gui_init()
{
  elements = load_all("gui.ini",buildElement,sizeof(struct gui_Element));
}


void gui_set(struct gui_Element *element)
{
  if (gui) gui_free(gui);
  gui = element;
}


struct gui_Element *gui_get(char const *key)
{
  struct gui_Element *element = HashMap_get(elements,key);
  if (!element)
  {
    printf("can't get gui element at %s\n",key);
    return NULL;
  }
  return element;
  //TODO: make it return a duplicate.
}



void gui_free(struct gui_Element *element)
{
  if (element->next) gui_free(element->next);
  if (element->child) gui_free(element->child);
  if (element->type == TEXT) free(element->content);
  free(element);
}


int gui_update()
{
  return (gui) ? 1 : 0;
}


void gui_render()
{
  if (!gui) return;

  SDL_RenderCopy(render_renderer,(SDL_Texture *)gui->content,NULL,&gui->dst);

  switch (gui->type)
  {
    case HBOX:
    //display all the children horizontally
    break;

    case VBOX:
    // display all the children vertically
    break;

    case TEXT:
    // display the text textually
    break;

    case CHOOSER:
    // display the children vertically, and with the selected one highlighted
    break;
  }
}
