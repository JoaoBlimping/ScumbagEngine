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
#define List_ITERATE(list,var) for (int var = 0;var < list##l + list##r;i++)

/** removes an item from an arbitrary spoit in the list and also messes with the order of the
 * items */
#define List_REMOVE(list,index) list[index] = list[list##l - 1];list##l--

/** copies end element into this element, and then says to remove that element from the end later */
#define List_CONCURRENT_REMOVE(list,index) list[index] = list[list##l - 1];list##r++;list##l--

/** this is called after the stuff where concurrent remove is used and this actually removes them
 * truly */
#define List_FLUSH(list) list##r = 0

/** puts the size of the list */
#define List_SIZE(list) list##l


#endif
