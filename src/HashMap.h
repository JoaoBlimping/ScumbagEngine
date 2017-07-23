#ifndef HASH_MAP_H
#define HASH_MAP_H


/** a bucket that contains stuff for your pleasure */
struct HashMap_Bucket
{
  /** the key of this bucket */
  char const *key;
  /** the value that this bucket contains */
  void *value;
  /** if there has been a collision then this contains the next element */
  struct HashMap_Bucket *next;
};


/** wrapper for the hashmap to store stuff like it's size */
struct HashMap
{
  /** the number of buckets there are */
  int size;
  /** the buckets */
  struct HashMap_Bucket buckets[];
};





/** turns a string into a hash
 * @param key is the string to be hashed
 * @return the hash value */
unsigned int HashMap_hash(char const *key);


/** creates a hashmap of a given size
 * @param size is the number of buckets the hashmap has
 * @return the hashmap */
struct HashMap *HashMap_create(int size);

/** adds an item to the hashmap
 * @param map is a pointer to the hashmap
 * @param key is the key to add it under
 * @param value is the thing to add */
void HashMap_add(struct HashMap *map,char const *key,void *value);

/** gets an item out of the hashmap
 * @param map is the map
 * @param is the key to get something under
 * @return the item with this key */
void *HashMap_get(struct HashMap *map,char const *key);


// TODO: I will need to add a forall free thingy which will be a pain, at least all my hashed stuff is persistent










#endif
