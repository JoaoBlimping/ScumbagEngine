#ifndef ACTOR_H
#define ACTOR_H


struct Actor
{
  char const *name;

  struct Object *body;
  struct Object *shadow;
};


#endif
