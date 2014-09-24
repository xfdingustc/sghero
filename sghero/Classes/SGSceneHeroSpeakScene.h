#ifndef SG_SCENE_HERO_SPEAK_SCENE_H
#define SG_SCENE_HERO_SPEAK_SCENE_H

#include "cocos2d.h"
#include "SGObserver.h"

USING_NS_CC;



class SGSceneHeroSpeakScene : public Layer, public SGObservable
{
public:
  static Scene* creatScene(const char* hero_name, const char* content, const Vec2& pos = Vec2::ZERO);
  
  CREATE_FUNC(SGSceneHeroSpeakScene);
  virtual bool init(); 

  bool onTouchBegin(Touch *touch, Event *unused_event);
private:
  EventListenerTouchOneByOne* event_listener;
 
};

#endif