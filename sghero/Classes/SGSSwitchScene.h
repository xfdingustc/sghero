#ifndef SG_SKIRMISH_SWITCH_SCENE_H
#define SG_SKIRMISH_SWITCH_SCENE_H

#include "cocos2d.h"
#include "json/document.h"
USING_NS_CC;

class SGSSwitchScene : public LayerColor
{
public:
  static Scene* createScene(int round, int turn);
  CREATE_FUNC(SGSSwitchScene);
  virtual bool init();
  void exitScene(float dt);
private:
  static rapidjson::Document __text_json_doc;
  static bool __json_parsed;
  LabelTTF* __content_ttf;
};

#endif