/** linked list implementation */


#include "LinkedList.h"

#include <stdlib.h>



struct LinkedList *LinkedList_create()
{
   struct LinkedList *list = (struct LinkedList *)calloc(1,sizeof(struct LinkedList));
   list->first = NULL;
   list->last = NULL;
   list->size = 0;
   return list;
};


void LinkedList_pushNode(struct LinkedList *list,void *value)
{
  struct Node *newNode = (struct Node *)calloc(1,sizeof(struct Node));
  newNode->next = list->first;
  list->first = newNode;
  list->size++;
};


void LinkedList_addNode(struct LinkedList *list,void *value)
{
   list->size++;
   struct Node *newNode = (struct Node *)calloc(1,sizeof(struct Node));
   newNode->next = NULL;
   newNode->data = value;

   if (list->first == NULL)
   {
      list->first = newNode;
      list->last = newNode;
   }
   else
   {
      list->last->next = newNode;
      list->last = newNode;
   }
}


struct Node *LinkedList_get(struct LinkedList *list,int index)
{
  int i = 0;
  struct Node *node = list->first;
  while (node != NULL)
  {
    if (i == index) return node;
    i++;
    node = node->next;
  }
  return NULL;
}


void **LinkedList_toArray(struct LinkedList *list)
{
   void **array = (void **)calloc(sizeof(void *) * list->size,1);
   struct Node *node = list->first;
   int i; for (i = 0;i < list->size;i++)
   {
      array[i] = node->data;
      node = node->next;
   }
   return array;
}


int LinkedList_getSize(struct LinkedList *list)
{
   return list->size;
}

void LinkedList_slash(struct LinkedList *list,int index)
{
  struct Node *node = LinkedList_get(list,index);
  while (node->next != NULL)
  {
     struct Node *newNode = node->next;
     free(node->data);
     free(node);
     node = newNode;
  }
}


void LinkedList_free(struct LinkedList *list)
{
   struct Node *node = list->first;
   while (node->next != NULL)
   {
      struct Node *newNode = node->next;
      free(node);
      node = newNode;
   }
   free(list);
}

void LinkedList_destroy(struct LinkedList *list)
{
   struct Node *node = list->first;
   while (node->next != NULL)
   {
      struct Node *newNode = node->next;
      free(node->data);
      free(node);
      node = newNode;
   }
   free(list);
}
