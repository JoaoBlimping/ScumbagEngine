#ifndef LIST_H
/**
 * ᛞᛖᚾᛁ
 * yeah this gives you lists which work, but their order is not reliable
 */
#define LIST_H


#define List_DEFINE(list,length) list[length];int list##l;int list##r

/** used after type to create a list. Important */
#define List_CREATE(list,length) list[length];int list##l = 0;int list##r = 0

/** used if List_CREATE can't be used for some reason afterwards to initialise the list in special
 * important ways */
#define List_INIT(list) list##l = 0;list##r = 0

/** add an item onto the end of the list */
#define List_PUSH(list,item) list[list##l] = item;list##l++

/** remove an item from the end of the list and return it, so use like:
 * int item = List_POP(list); */
#define List_POP(list) list[list##l - 1];list##l--

/** makes like a for loop over a list */
#define List_ITERATE(list,var) for (int var = 0;var < list##l;i++)

/** removes an item from an arbitrary spoit in the list and also messes with the order of the
 * items */
#define List_REMOVE(list,index) list[index] = list[list##l - 1];list##l--

#define List_CONCURRENT_REMOVE(list,index) list[index] = list[list##l - 1];list##r++

#define List_FLUSH(list) list##l -= list##r;list##r = 0

/** puts the size of the list */
#define List_SIZE(list) list##l


#endif
