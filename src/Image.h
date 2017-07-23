#ifndef IMAGE_H
#define IMAGE_H


#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




/** gives you an image by it's index */
SDL_Texture *Image_get(char const *key);



#endif
