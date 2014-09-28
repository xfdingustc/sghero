#ifndef SG_SKIRMISH_SCENE_OBJ_H
#define SG_SKIRMISH_SCENE_OBJ_H

#include "cocos2d.h"
USING_NS_CC;


class SGSkirmishSceneObj : public Sprite 
{
public:
  static SGSkirmishSceneObj* create(const char* name);
  bool init(const char* name);

};

#endif