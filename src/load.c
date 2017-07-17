#include "load.h"

#include "ini.h"
#include <string.h>




struct load_Bucket *load_all(char const *filename,void *(*builder)(char const *,char const *,void *),int size)
{
    char *file = ini_openFile(filename);
    struct LinkedList *keys = ini_getSections(file);
    struct load_Bucket *items = calloc(sizeof(struct load_Bucket),keys->size + 1);

    // Add in empty first item containing size
    items[0].key = "size";
    items[0].value = keys->size;

    // put in all the actual ones
    int i = 1;
    LinkedList_ITERATE(keys,node)
    {
      items[i].key = node->data;
      items[i].value = malloc(size);
      builder(node->data,file,items[i].value);
      i++;
    }

    // Clean up time :)
    LinkedList_free(keys);
    free(file);

    return items;
}


void *load_get(char const *key,struct load_Bucket *buckets)
{
  for (int i = 1;i <= (int)(buckets[0].value);i++)
  {
    if (!strcmp(buckets[i].key,key)) return buckets[i].value;
  }
  return NULL;
}
