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
  HERO_SIDE getSide() { return __side; }
  bool isRival(SGSkirmishHero* hero);

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
  void setActive(bool active); 


  // hero AI currently is dummy
  typedef enum {
    HERO_AI_ATTACK,
    HERO_AI_STAY,
    HERO_AI_DEFENSE,
  } HERO_AI;
  void setAI(HERO_AI ai) { __ai = ai; }
  void setAI(std::string& ai);
  HERO_AI getAI() { return __ai; }

  void oneMove();

  void moveTo(SGSkirmishMapPos& target_pos);

  HERO_CATAGORY getCatagory() { return __catagory; }




  int getStamina() { return __stamina; }
  void initCatagory();
  void initDataNum();

    
  typedef enum {
    HERO_DIRECTION_NORTH,
    HERO_DIRECTION_WEST,
    HERO_DIRECTION_SOUTH,
    HERO_DIRECTION_EAST, 
  } HERO_DIRECTION;
  
  void faceTo(const char* direction);
  void faceTo(HERO_DIRECTION direction);
  void doAction(const char* action);
  void doAttackAction();

  typedef enum {
    HERO_STATUS_NORMAL,
    HERO_STATUS_CHAOS,
  } HERO_STATUS;
  void setStatus(std::string& status);
  void setStatus(HERO_STATUS status);
  HERO_STATUS getStatus() { return __status; }


  SGSkirmishMapPos __previous_map_position;

private:
  void updataSprite();
  std::string& getHeroResFile(const char* res_dir);
  std::string __name;

  HERO_SIDE __side;
  Vector<SpriteFrame*> __sprite_frames;
  Vector<SpriteFrame*> __attack_sprite_frames;
  Vector<SpriteFrame*> __spec_sprite_frames;

  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  ANIMATE_MAP __animate_map;

  HERO_DIRECTION getDirection(const char* direction);
  HERO_DIRECTION __direction;

  bool __active;
  HERO_CATAGORY __catagory;

  HERO_STATUS __status;
  int __stamina;

  HERO_AI __ai;
  
};

#endif