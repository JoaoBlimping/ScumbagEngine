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
  /** like a vbox, but you get to select an element and return it's index to the script running the
   * gui */
  CHOOSER
};


/** a single gui element like a box or a piece of text or w/e */
struct gui_Element
{
  /** contains the dimensions of the element */
  SDL_Rect dst;
  /** the type of element that it is */
  enum gui_ElementType type;
  /** contains some other thing this element uses */
  void *content;
  /** link to the first child element */
  struct gui_Element *child;
  /** link to the next element if this is one of many children */
  struct gui_Element *next;
};


/** loads in some default window sizes */
void gui_init();

/** sets the current gui thing, and frees whatever is in there if there is anything
 * @param element is the new gui thing to be on the screen */
void gui_set(struct gui_Element *element);

/** gives you a basic window shape for you to enjoy */
struct gui_Element *gui_get(char const *key);

/** adds a new child element to the start of the parent's list of child elements
 * @param parent is the parent element
 * @param child is the child to add */
void gui_prepend(struct gui_Element *parent,struct gui_Element *child);

/** adds a new child element to the end of the parent's list of child elements
 * @param parent is the parent element
 * @param child is the child to add */
void gui_append(struct gui_Element *parent,struct gui_Element *child);

/** frees this thingo for your pleasure
 * @param element is the element that we are erasing from the face of the earth */
void gui_free(struct gui_Element *element);

/** updates the current gui if there is one
 * @return 0 iff there is no gui to update */
int gui_update();

/** renders the gui stuff if there is any */
void gui_render();


#endif
