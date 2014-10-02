#ifndef SG_SKIRMISH_INFO_H
#define SG_SKIRMISH_INFO_H

#include "cocos2d.h"
USING_NS_CC;

class SGSkirmishInfo : Layer
{
public:
  static Scene* createScene(std::string& content);
  CREATE_FUNC(SGSkirmishInfo);

  virtual bool init();
  bool onTouchBegin(Touch *touch, Event *unused_event);
private:
  std::string __content;
  EventListenerTouchOneByOne* __event_listener;
};


#endif