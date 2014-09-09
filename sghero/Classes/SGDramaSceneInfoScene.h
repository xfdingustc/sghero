#ifndef SG_DRAMA_SCENE_INFO_SCENE_H
#define SG_DRAMA_SCENE_INFO_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

class SGDramaSceneInfoScene : public Layer 
{
public:
  static Scene* createScene(const char* content);
  CREATE_FUNC(SGDramaSceneInfoScene);
  virtual bool init();
  bool onTouchBegin(Touch *touch, Event *unused_event);
private:
  std::string __content;
  EventListenerTouchOneByOne* __event_listener;
};
#endif