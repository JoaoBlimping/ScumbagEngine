#ifndef FONT_H
#define FONT_H


/** initialises the font system and loads in the fonts */
void font_init();


/** renders a piece of text to a texture
 * @param text is the text to render
 * @param font is the key of the font to use, or NULL for the default
 * @param size is the font size
 * @param colour is the colour the text should be */
SDL_Texture *font_renderText(char const *text,char const *font,int size,int colour);



#endif
