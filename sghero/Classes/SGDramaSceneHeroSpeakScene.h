#ifndef SG_DRAMA_SCENE_HERO_SPEAK_SCENE_H
#define SG_DRAMA_SCENE_HERO_SPEAK_SCENE_H

#include "cocos2d.h"

USING_NS_CC;

class SGDramaSceneHeroSpeakScene : public Layer
{
public:
  static Scene* creatScene();

  CREATE_FUNC(SGDramaSceneHeroSpeakScene);
  virtual bool init(); 

  bool onTouchBegin(Touch *touch, Event *unused_event);
private:
  EventListenerTouchOneByOne* event_listener;
};

#endif