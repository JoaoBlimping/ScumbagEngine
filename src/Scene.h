#ifndef SCENE_H
#define SCENE_H


/** a scene in the game as in like some screen where shit goes on like level scene or menu scene
 * etc */
struct Scene
{
  /** the name of the scene so you can get it in a list */
  char const *name;
  /** this is called each time the scene starts so it is ready, and it provides arguments so that
   * you can eg tell it what level to open or whatever else you desire
   * @param argc is the number of arguments
   * @param is the content of the arguments */
  void (*birth)(int argc,char **argv);
  /** updates the scene */
  void (*update)();
  /** displays the scene */
  void (*render)();
  /** this is called when the scene is getting replaced so that it can clean up after itself */
  void (*death)();
};

/** adds a scene to the list of scenes that can be set to
 * @param scene is a pointer to the new scene */
void Scene_add(struct Scene *scene);

/** sets the current scene, calls the previous one's death method, and then calls the new one's
 * birth method */
void Scene_set(char const *name,int argc,char **argv);

/** checks if there is any gui stuff going on, and if not, it updates the scene */
void Scene_update();

/** renders the scene, and the gui on top if there is some */
void Scene_render();



#endif
