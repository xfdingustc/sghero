#ifndef SG_DRAMA_SCENE_H
#define SG_DRAMA_SCENE_H
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
USING_NS_CC;


class SGDramaScene : public Layer
{
public:
  static cocos2d::Scene* createScene();
   

  CREATE_FUNC(SGDramaScene);
  virtual bool init(); 

  void update(float dt);

private:
  bool parseDramaSceneXmlFile(const char* file);
  bool parseDrameSceneEvents(tinyxml2::XMLElement* event);

  typedef std::list<tinyxml2::XMLElement*> SGDramaSceneEventList;
  SGDramaSceneEventList __event_list;
  void startSceneScript(float dt);
  void handleDramaSceneScriptEvent(SGDramaSceneEventList& event_list);

  // coordination convert
  Vec2 convertCoordinate(Vec2 origin);

  bool __has_pending_event;
  int __ret_value;
};

#endif