#ifndef SG_SCENE_BASE_H
#define SG_SCENE_BASE_H
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "SGObserver.h"
USING_NS_CC;


class SGSceneBase : public Layer, public SGObserver {

protected:
  void onHandleEventSoundEffect(tinyxml2::XMLElement* event);
  void onHandleEventSoundTrack(tinyxml2::XMLElement* event);
  virtual void onHandleEventDialog(tinyxml2::XMLElement* event);


  void formatString(std::string& str);

  typedef std::list<tinyxml2::XMLElement*> SGSceneEventList;
  SGSceneEventList __event_list;
  
};

#endif