#ifndef SG_SKIRMISH_SCENE_H
#define SG_SKIRMISH_SCENE_H

#include "cocos2d.h"
USING_NS_CC;
#include "tinyxml2/tinyxml2.h"

class SGSkirmishScene : public Layer
{
public:
  static Scene* createScene();

  CREATE_FUNC(SGSkirmishScene);
  virtual bool init();

  virtual void onExit();

  bool onTouchBegan(Touch *touch, Event *unused_event) { return  true; };
  void onTouchMoved(Touch *touch, Event *unused_event);
private:
  bool parseSkirmishSceneXmlFile(const char* file);
  bool parseSkirmishSettings(tinyxml2::XMLElement* setting);

  void onHandleSettingMap(tinyxml2::XMLElement* setting);
  void onHandleSettingFriend(tinyxml2::XMLElement* setting);

  Vec2 mapPos2OpenGLPos(Vec2 origin);

  EventListenerTouchOneByOne* __event_listener;
  
};

#endif