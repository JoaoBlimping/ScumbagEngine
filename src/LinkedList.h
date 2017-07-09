#ifndef LINKED_LIST_H
/** A rough linked list implementation
 * The mound beckons */
#define LINKED_LIST_H


#include <stdlib.h>


#define LinkedList_ITERATE(list,var) for(struct Node *var = list->first;var != NULL;var = var->next)



/** a node in a linked list */
struct Node
{
   /** the number stored in the node */
   void *data;

   /** points to the next node */
   struct Node *next;
};


/** wraps around the list of nodes for a few convenient things */
struct LinkedList
{
   /** the first node in the list */
   struct Node *first;

   /** the last node in the list, this is so it can add stuff fast */
   struct Node *last;

   /** stores the size of the list so it doesn't have to calculated */
   int size;
};


/** create the start of a linked list by creating the first element */
struct LinkedList *LinkedList_create();

/** add a node to the front of the list */
void LinkedList_pushNode(struct LinkedList *list,void *value);

/** add a node to the end of the list */
void LinkedList_addNode(struct LinkedList *list,void *value);

/** gets an item at a given index in the list
 * @param list points to the list
 * @param index is the index at which the item is gotten
 * @return your desired item, or NULL if you chose one past the end of the list */
struct LinkedList *LinkedList_get(struct LinkedList *list,int index);

/** converts the linked list to an array */
void **LinkedList_toArray(struct LinkedList *list);

/** returns the size of the list */
int LinkedList_getSize(struct LinkedList *list);

/** free list and all elements in it from a given index
 * @param list is a pointer to the list
 * @param index is the index to start slashing from */
void LinkedList_slash(struct LinkedList *list,int index);

/** frees a linked list's memory. It doesn't free the stuff in the list though so remember that  */
void LinkedList_free(struct LinkedList *list);

/** frees a linked list's memory. It does free the stuff in the list though so remember that  */
void LinkedList_destroy(struct LinkedList *list);


#endif
