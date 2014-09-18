#ifndef SG_SCENE_HERO_SPEAK_SCENE_H
#define SG_SCENE_HERO_SPEAK_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class SGSceneHeroSpeakScene : public Layer
{
public:
  static Scene* creatScene(const char* hero_name, const char* content);

  CREATE_FUNC(SGSceneHeroSpeakScene);
  virtual bool init(); 

  bool onTouchBegin(Touch *touch, Event *unused_event);
private:
  EventListenerTouchOneByOne* event_listener;

  
};

#endif