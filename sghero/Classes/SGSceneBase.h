#ifndef SG_SCENE_BASE_H
#define SG_SCENE_BASE_H
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
USING_NS_CC;


class SGSceneBase : public Layer {

protected:
  void onHandleEventSoundEffect(tinyxml2::XMLElement* event);
  void onHandleEventSoundTrack(tinyxml2::XMLElement* event);
  void onHandleEventDialog(tinyxml2::XMLElement* event);


  void formatString(std::string& str);

  typedef std::list<tinyxml2::XMLElement*> SGSceneEventList;
  SGSceneEventList __event_list;
};

#endif