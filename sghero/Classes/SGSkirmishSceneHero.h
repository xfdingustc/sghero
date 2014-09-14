#ifndef SG_SKIRMISH_SCENE_HERO_H
#define SG_SKIRMISH_SCENE_HERO_H

#include "cocos2d.h"
USING_NS_CC;

class SGSkirmishSceneHero : public Sprite 
{
public:
  typedef enum {
    HERO_SIDE_OURS,
    HERO_SIDE_ENEMY,
    HERO_SIDE_FRIEND,
  } HERO_SIDE;
  static SGSkirmishSceneHero* create(const char* hero_name, HERO_SIDE side);
  virtual bool init(const char* hero_name, HERO_SIDE side);

private:
  HERO_SIDE __side;
};

#endif