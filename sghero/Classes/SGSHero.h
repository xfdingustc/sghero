#ifndef SG_SKIRMISH_SCENE_HERO_H
#define SG_SKIRMISH_SCENE_HERO_H

#include "cocos2d.h"
#include "SGSObj.h"
USING_NS_CC;

class SGSHero : public SGSObj 
{
public:
  typedef enum {
    HERO_AI_ATTACK,
    HERO_AI_STAY,
    HERO_AI_DEFENSE,
  } HERO_AI;

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

  typedef enum {
    HERO_DIRECTION_NORTH,
    HERO_DIRECTION_WEST,
    HERO_DIRECTION_SOUTH,
    HERO_DIRECTION_EAST, 
  } HERO_DIRECTION;

  typedef enum {
    HERO_SIDE_OURS,
    HERO_SIDE_ENEMY,
    HERO_SIDE_FRIEND,
  } HERO_SIDE;

  typedef enum {
    HERO_STATUS_NORMAL,
    HERO_STATUS_CHAOS,
  } HERO_STATUS;


  static          SGSHero* create(const char* hero_name, HERO_SIDE side, SGObserver* observer);
  explicit        SGSHero(SGObserver* observer) : SGSObj(observer) {}

  void            doAction(const char* action);
  void            doAttackAction();

  void            faceTo(const char* direction);
  void            faceTo(HERO_DIRECTION direction);

  bool            init(const char* hero_name, HERO_SIDE side);
  bool            initActions();
  bool            initAttackActions();
  void            initCatagory();
  void            initDataNum();
  bool            initSpecActions();

  bool            isActive() { return (__active && isVisible());}
  bool            isRival(SGSHero* hero);
 
  void            moveTo(SGSPoint& target_pos);

  void            setActive(bool active); 
  void            setAI(HERO_AI ai) { __ai = ai; }
  void            setAI(std::string& ai);
  void            setStatus(std::string& status);
  void            setStatus(HERO_STATUS status);


  HERO_AI         getAI() { return __ai; }
  HERO_CATAGORY   getCatagory() { return __catagory; }
  HERO_SIDE       getSide() { return __side; }
  int             getStamina() { return __stamina; }
  HERO_STATUS     getStatus() { return __status; }
  SGSPointList*      getAttackArea();
  SGSPointList*      getAttackAreaFromPosition(SGSPoint& pos);

  SGSPoint __previous_map_position;

private:
  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  HERO_DIRECTION  getDirection(const char* direction);
  std::string&    getHeroResFile(const char* res_dir);

  void            updataSprite(); 
  HERO_AI         __ai;
  ANIMATE_MAP     __animate_map;
  bool            __active;
  HERO_CATAGORY   __catagory;
  HERO_DIRECTION  __direction;
  std::string     __name;
  HERO_SIDE       __side;
  int             __stamina;
  HERO_STATUS     __status;


  Vector<SpriteFrame*> __sprite_frames;
  Vector<SpriteFrame*> __attack_sprite_frames;
  Vector<SpriteFrame*> __spec_sprite_frames;
  
};

typedef Vector<SGSHero*> SGSHeroList;


#endif