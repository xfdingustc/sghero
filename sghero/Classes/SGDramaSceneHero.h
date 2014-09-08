#ifndef SG_DRAMA_SCENE_HERO_H
#define SG_DRAMR_SCENE_HERO_H

#include "cocos2d.h"
USING_NS_CC;

class SGDramaSceneHero : public Sprite 
{
public:
  static SGDramaSceneHero* create(const char* hero_name);

  typedef enum {
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST, 
  } DIRECTION;
  void moveTo(Vec2 target_pos, const char* direction);
  void faceTo(const char* direction);
  void doAction(const char* action);

  bool init(const char* hero_name);

  bool initActions();

  void speak(const char* content);

  void actionFinished();



private:
  DIRECTION getDirection(const char* direction);
  DIRECTION __face_direction;

  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  ANIMATE_MAP __animate_map;

  typedef std::map<std::string, SpriteFrame*> FRAME_MAP;
  FRAME_MAP __frame_map;


};

#endif