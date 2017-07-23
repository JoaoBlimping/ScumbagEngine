#ifndef GUI_H
#define GUI_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/** the different types of elements that there are */
enum gui_ElementType
{
  /** for a box full of gui elements that displays the horizontally */
  HBOX,
  /** for a box full of gui elements that displays them vertically */
  VBOX,
  /** contains some text */
  TEXT,
  /** basically does nothing except show the background picture it has */
  IMAGE,
  /** like a vbox, but you get to select an element and return it's index to the script running the
   * gui */
  CHOOSER
};


/** a single gui element like a box or a piece of text or w/e */
struct gui_Element
{
  int x,y,w,h;
  /** the type of element that it is */
  enum gui_ElementType type;
  /** the amount of content such as length of text in a text, or number of children in a hbox */
  int contentLength;
  /** the content, whatever it may be from other elements to text or whatever else */
  void *content;
  /** all elements show a texture behind them (unless this is null) */
  SDL_Texture *texture;
};



/** loads in some default window sizes */
void gui_init();


/** gives you a basic window shape for you to enjoy */
struct gui_Element *gui_get(char const *key);


/** updates the current gui if there is one
 * @return 0 iff there is no gui to update */
int gui_update();


/** renders the gui stuff if there is any */
void gui_render();





#endif
