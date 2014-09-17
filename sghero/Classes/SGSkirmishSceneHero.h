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

  
  typedef enum {
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST, 
  } DIRECTION;
  
  void faceTo(const char* direction);

private:
  HERO_SIDE __side;
  Vector<SpriteFrame*> __sprite_frames;

  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  ANIMATE_MAP __animate_map;

  DIRECTION getDirection(const char* direction);
  DIRECTION __face_direction;
};

#endif