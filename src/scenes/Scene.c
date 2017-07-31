#include "Scene.h"

#include "../List.h"
#include "../gui.h"


#define MAX_SCENES 10



struct Scene *List_CREATE(scenes,MAX_SCENES);
struct Scene *currentScene;




void Scene_add(struct Scene *scene)
{
  List_PUSH(scenes,scene);
}


void Scene_set(char const *name,int argc,char **argv)
{
  List_ITERATE(scenes,i)
  {
    if (!strcmp(scenes[i]->name,name))
    {
      if (currentScene) currentScene->death();
      currentScene = scenes[i];
      currentScene->birth(argc,argv);
      return;
    }
  }
  printf("No scene named %s, idiot.\n",name);
}


void Scene_update()
{
  if (!gui_update()) currentScene->update();
}


void Scene_render()
{
  currentScene->render();
  gui_render();
}
