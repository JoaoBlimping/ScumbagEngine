#include "HashMap.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



unsigned int HashMap_hash(char const *key)
{
  unsigned int h = 0;
  for (int i = 0;key[i];i++)
  {
    unsigned int high = h & 0xf8000000;
    h = h << 5;
    h = h ^ (high >> 27);
    h = h ^ key[i];
  }
  return h;
}


struct HashMap *HashMap_create(int size)
{
  struct HashMap *map = malloc(sizeof(struct HashMap) + sizeof(struct HashMap_Bucket) * size);
  map->size = size;
  for (int i = 0;i < map->size;i++)
  {
    map->buckets[i].key = NULL;
    map->buckets[i].next = NULL;
  }
  return map;
}


void HashMap_add(struct HashMap *map,char const *key,void *value)
{
  unsigned int hash = HashMap_hash(key) % map->size;

  // virgin
  if (map->buckets[hash].key == NULL)
  {
    map->buckets[hash].key = key;
    map->buckets[hash].value = value;
  }

  // collision
  else
  {
    printf("collision at %d/%d\n",hash,map->size);
    struct HashMap_Bucket *bucket = map->buckets + hash;
    while (bucket->next) bucket = bucket->next;
    bucket->next = malloc(sizeof(struct HashMap_Bucket));
    bucket->next->key = key;
    bucket->next->value = value;
    bucket->next->next = NULL;
  }
}


void *HashMap_get(struct HashMap *map,char const *key)
{
  unsigned int hash = HashMap_hash(key) % map->size;
  struct HashMap_Bucket *bucket = map->buckets + hash;

  do
  {
    if (bucket->key && !strcmp(bucket->key,key)) return bucket->value;
    bucket = bucket->next;
  } while (bucket);

  return NULL;
}
