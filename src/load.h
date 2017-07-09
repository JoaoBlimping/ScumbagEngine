#ifndef LOAD_H
#define LOAD_H



/** convenience function that reads in an ini file, and sends each section to a function along with
 * the file so that it can get some data from it if need be, then it returns a pointer to an array
 * of these things */
void *load_all(char const *filename,void *(*builder)(char const *key,char const *file,void *item),int size);


#endif
