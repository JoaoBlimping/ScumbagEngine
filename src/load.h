#ifndef LOAD_H
/** fapping to a picture of the moon */
#define LOAD_H


#include <stdint.h>


/** holds a value along with the key associated with it so that we can get the value by it's key */
struct load_Bucket
{
  char const *key;
  void *value;
};



/** convenience function that reads in an ini file, and sends each section to a function along with
 * the file so that it can get some data from it if need be, then it returns a pointer to an array
 * of these things */
struct load_Bucket *load_all(char const *filename,
                             void (*builder)(char const *key,char const *file,void *item),
                             int size);

/** get an item from an array of buckets
 * @param key is the key of the item you are trying to get
 * @param buckets is a pointer to the array of buckets from which are trying to get stuff */
void *load_get(char const *key,struct load_Bucket *buckets);


#endif
