#ifndef SG_SKIRMISH_SCENE_HERO_H
#define SG_SKIRMISH_SCENE_HERO_H

#include "cocos2d.h"
#include "SGSkirmishObj.h"
USING_NS_CC;

class SGSkirmishHero : public SGSkirmishObj 
{
public:
  typedef enum {
    HERO_SIDE_OURS,
    HERO_SIDE_ENEMY,
    HERO_SIDE_FRIEND,
  } HERO_SIDE;

  typedef enum {
    HERO_CATAGORY_LORD,
    HERO_CATAGORY_INFANTRY,
    HERO_CATAGORY_ARCHER,
    HERO_CATAGORY_KNIGHT,
    HERO_CATAGORY_HORSEARCHER,
    HERO_CATAGORY_DEMOLISHER,
    HERO_CATAGORY_MARTIALIST,
    HERO_CATAGORY_THIEF,
    HERO_CATAGORY_MAGE,
    HERO_CATAGORY_PRIEST,
    HERO_CATAGORY_WARLOCK,
    HERO_CATAGORY_HORSEMAGE,
    HERO_CATAGORY_DANCER,
    HERO_CATAGORY_MAX,
  } HERO_CATAGORY;
  static SGSkirmishHero* create(const char* hero_name, HERO_SIDE side, SGObserver* observer);
  explicit SGSkirmishHero(SGObserver* observer) : SGSkirmishObj(observer) {}
  virtual bool init(const char* hero_name, HERO_SIDE side);
  bool initActions();
  bool initAttackActions();
  bool initSpecActions();

  bool isActive() { return (__active && isVisible());}
  void resetActivity() { __active = true; }

  // hero AI currently is dummy
  void oneMove() { __active = false; }

  void moveTo(Vec2& target_pos);
  
  HERO_CATAGORY getCatagory() { return __catagory; }
  void initCatagory();

    
  typedef enum {
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST, 
  } DIRECTION;
  
  void faceTo(const char* direction);
  void doAction(const char* action);
  void doAttackAction();

  void setStatus(std::string& status);
  bool onTouchBegin(Touch *touch, Event *unused_event);

  void showAvailablePath();

  bool isRival(SGSkirmishHero* hero);
private:
  
  std::string& getHeroResFile(const char* res_dir);
  std::string __name;

  HERO_SIDE __side;
  Vector<SpriteFrame*> __sprite_frames;
  Vector<SpriteFrame*> __attack_sprite_frames;
  Vector<SpriteFrame*> __spec_sprite_frames;

  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  ANIMATE_MAP __animate_map;

  DIRECTION getDirection(const char* direction);
  DIRECTION __face_direction;

  bool __active;
  HERO_CATAGORY __catagory;

  EventListenerTouchOneByOne* __event_listener;

  
};

#endif