#include "Map.h"

#include <libxml2.h>



struct Map *Map_loadMap(uint8_t const *filename)
{
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseFile(filename);

  if (doc == NULL )
  {
		printf("map %s couldn't be parsed\n",filename);
		return NULL;
	}

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL)
  {
		printf("map %s is an empty file\n",filename);
		xmlFreeDoc(doc);
		return NULL;
	}

  if (xmlStrcmp(cur->name, (const xmlChar *) "map"))
  {
		printf("map %s is not a tiled map\n",filename);
		xmlFreeDoc(doc);
		return NULL;
	}



}
