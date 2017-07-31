#include "load.h"

#include "ini.h"
#include "HashMap.h"
#include <string.h>




struct HashMap *load_all(char const *filename,void (*builder)(char const *,char const *,void *),int size)
{
    char *file = ini_openFile(filename);
    struct LinkedList *keys = ini_getSections(file);
    struct HashMap *map = HashMap_create(keys->size * 2);

    // put in all the actual ones
    LinkedList_ITERATE(keys,node)
    {
      void *item = malloc(size);
      builder(node->data,file,item);
      HashMap_add(map,node->data,item);
    }

    // Clean up time :)
    LinkedList_free(keys);
    free(file);

    return map;
}
