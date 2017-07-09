#include "load.h"

#include "ini.h"


void *load_all(char const *filename,void *(*builder)(char const *,char const *,void *),int size)
{
    uint8_t *file = ini_openFile(filename);
    struct LinkedList *keys = ini_getSections(file);

    void *items = calloc(keys->size,size);
    int i = 0;
    LinkedList_ITERATE(keys,node)
    {
      builder(node->data,file,items + size * i);
      i++;
    }

    // Clean up time :)
    LinkedList_destroy(keys);
    free(file);

    return items;
}
