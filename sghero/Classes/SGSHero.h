#ifndef SG_SKIRMISH_SCENE_HERO_H
#define SG_SKIRMISH_SCENE_HERO_H

#include "cocos2d.h"
#include "SGMessageHandler.h"
#include "SGSObj.h"
#include "SGCorpsRepo.h"
#include "SGCorpsRange.h"

USING_NS_CC;


NS_CC_BEGIN
typedef std::function<void()> SGSHeroActionFinishedCallback;

class SGSTerrain;
class SGSHero : public SGSObj, public SGMessageHandler
{
public:
  typedef enum {
    HERO_AI_ATTACK,
    HERO_AI_STAY,
    HERO_AI_DEFENSE,
  } HERO_AI;

  typedef enum {
    HERO_CATEGORY_LORD,
    HERO_CATEGORY_INFANTRY,
    HERO_CATEGORY_ARCHER,
    HERO_CATEGORY_CAVALRY,
    HERO_CATEGORY_HORSEARCHER,
    HERO_CATEGORY_DEMOLISHER,
    HERO_CATEGORY_MARTIALIST,
    HERO_CATEGORY_THIEF,
    HERO_CATEGORY_MAGE,
    HERO_CATEGORY_PRIEST,
    HERO_CATEGORY_WARLOCK,
    HERO_CATEGORY_HORSEMAGE,
    HERO_CATEGORY_DANCER,
    HERO_CATEGORY_MAX,
  } HERO_category;

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
  
  void            attackActionFinished(Node* hero, void* ptr);
  void            attackHero(SGSHero* defense_hero);
  void            attacked();
  void            counterAttackFinished(Node* hero, void* ptr);
  static          SGSHero* create(const char* hero_name, HERO_SIDE side, SGObserver* observer);
  explicit        SGSHero(SGObserver* observer) : SGSObj(observer) {}

  void            doAction(const char* action);
  void            doAttackAction();

  void            faceTo(const char* direction);
  void            faceTo(HERO_DIRECTION direction);

  int             getAgility() { return __agility; }
  HERO_AI         getAI() { return __ai; }
  Animate*        getAttackAnimate();
  SGSPointList*   getAttackArea();
  SGSPointList*   getAttackAreaFromPosition(SGSPoint* pos);
  HERO_category   getcategory() { return __category; }
  int             getCommand() { return __command; }
  int             getStrength() { return __strength; }
  int             getLuck() { return __luck; }
  int             getIntelligence() { return __intelligence; } 
  HERO_DIRECTION  getRelativeDirection(SGSHero* other_hero);

  HERO_SIDE       getSide() { return __side; }
  int             getStamina() { return __stamina; }
  HERO_STATUS     getStatus() { return __status; }
  Animate*        getWalkAnimate(HERO_DIRECTION direction);

  bool            init(const char* hero_name, HERO_SIDE side);
  bool            initActions();
  bool            initAttackActions();
  void            initCategory();
  void            initDataNum();
  bool            initSpecActions();

  bool            isActive() { return (__active && isVisible());}
  bool            isRival(SGSHero* hero);
 
  void            moveOneStep(SGSPointList* path);
  void            moveOneStepFinished(Node* node, void* ptr);
  float           moveTo(SGSPoint* target_pos);
  void            oneAIMove(const SGSHeroActionFinishedCallback& callback, SGSTerrain* terrain);

  void            setActionFinishedCallback(const SGSHeroActionFinishedCallback& callback);
  void            setActive(bool active); 
  void            setAI(HERO_AI ai) { __ai = ai; }
  void            setAI(std::string& ai);
  void            setDirection(HERO_DIRECTION direction);
  void            setStatus(std::string& status);
  void            setStatus(HERO_STATUS status);
  void            setTerrain(SGSTerrain* terrain) { __terrain = terrain; };

  void            update(float dt);

  SGSPoint        __previous_map_position;

private:
  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  
  void            addDelay(float delay);
  HERO_DIRECTION  getDirection(const char* direction);
  std::string&    getHeroResFile(const char* res_dir);
  HERO_DIRECTION  getRelativeDirection(SGSPoint& point);
  HERO_DIRECTION  getRelativeDirectionFrom(SGSPoint& point, SGSPoint& from);

  enum {
    kWhatAttack,
    kWhatAttacked,
    kWhatDefensed,
    kWhatMove,
    kWhatDelay,
  };

  void            handleMessage(SGMessage* message);

  void            onAttack(SGMessage* message);
  void            onAttacked(SGMessage* message);
  void            onDelay(SGMessage* message);
  void            onMoveTo(SGMessage* message);

  void            startUpdate(float dt);
  void            updataSprite(); 
  HERO_AI         __ai;
  int             __agility;
  ANIMATE_MAP     __animate_map;
  bool            __active;
  HERO_category   __category;
  int             __command;
  HERO_DIRECTION  __direction;
  int             __strength;
  int             __hp;
  int             __hp_max;
  int             __intelligence;
  int             __luck;
  int             __mp;
  int             __mp_max;
  std::string     __name;
  HERO_SIDE       __side;
  int             __stamina;
  HERO_STATUS     __status;
  SGSTerrain*     __terrain;
	int							__level;
	SGCorpsAttackRange::CORPS_ATTACK_RANGE	__range;



  Vector<SpriteFrame*> __sprite_frames;
  Vector<SpriteFrame*> __attack_sprite_frames;
  Vector<SpriteFrame*> __spec_sprite_frames;

  static SGSHeroActionFinishedCallback __action_finished_callback;
  
};

typedef Vector<SGSHero*> SGSHeroList;

NS_CC_END
#endif