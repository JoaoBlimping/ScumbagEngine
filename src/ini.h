#ifndef INI_H
/**  _     || || /
 *  |_\ /\ || || >  /
 *  |   \/ \/ || \ /
 *   \____________/ */
#define INI_H

#include "LinkedList.h"
#include <stdint.h>


/** Opens the file and reads the whole thing in and gives you a copy of it.
 * This is primarily for .ini files. Also keep in mind that you need to delete this data yourself
 * if you want to avoid memory leaks.
 * @param filename is a pointer to the name of the file you are opening
 * @returns a pointer to a sequence containing the whole file data, 0 escaped */
uint8_t *ini_openFile(uint8_t const *filename);

/** Tells you all of the section names in an .ini file
 * Keep in mind all of this stuff later has to be erased
 * @param file is the pointer to the file contents data
 * @returns a pointer to a vector of section names, 0 escaped */
struct LinkedList *ini_getSections(uint8_t const *file);

/** Reads a string from an .ini file, or gives you a fallback value if it's not there
 * @param file is a pointer to the file data
 * @param section is a pointer to the section name to look in
 * @param param is a pointer to the name of the parameter to look for
 * @param fallback is a pointer to the string to return if the parameter cannot be found
 * @returns either the found parameter or the fallback */
uint8_t *ini_readString(uint8_t const *file,uint8_t const *section,uint8_t const *param,uint8_t *fallback);

/** Reads a string from an .ini file, or gives you a fallback value if it's not there
 * @param file is a pointer to the file data
 * @param section is a pointer to the section name to look in
 * @param param is a pointer to the name of the parameter to look for
 * @param fallback is a number to return if the parameter cannot be found
 * @returns either the found parameter or the fallback */
int ini_readInt(uint8_t const *file,uint8_t const *section,uint8_t const *param,int fallback);

/** Reads a string from an .ini file, or gives you a fallback value if it's not there
 * @param file is a pointer to the file data
 * @param section is a pointer to the section name to look in
 * @param param is a pointer to the name of the parameter to look for
 * @param fallback is a number to return if the parameter cannot be found
 * @returns either the found parameter or the fallback */
float ini_readFloat(uint8_t const *file,uint8_t const *section,uint8_t const *param,float fallback);


#endif
