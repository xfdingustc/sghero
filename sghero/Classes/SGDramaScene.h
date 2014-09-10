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
  void parseDrameSceneSubEvents(tinyxml2::XMLElement* sub_event);

  void formatString(std::string& str);

  typedef std::list<tinyxml2::XMLElement*> SGDramaSceneEventList;
  SGDramaSceneEventList __event_list;
  void startSceneScript(float dt);
  void handleDramaSceneScriptEvent(SGDramaSceneEventList& event_list);

  void onHandleEventBackgroundImage(tinyxml2::XMLElement* event);
  void onHandleEventHeroFaceShow(tinyxml2::XMLElement* event);
  void onHandleEventHeroFaceMove(tinyxml2::XMLElement* event);
  void onHandleEventHeroFaceHide(tinyxml2::XMLElement* event);
  void onHandleEventMapInfoShow(tinyxml2::XMLElement* event);

  // coordination convert
  Vec2 convertCoordinate(Vec2 origin);
  Vec2 chinaMapPosConvert(Vec2 origin);
  // for drama select window
  bool __has_pending_event;
  int __ret_value;

  // for drama forks
  typedef std::map<std::string, int> VAL_MAP_TYPE;
  VAL_MAP_TYPE __internal_val_map;
};

#endif