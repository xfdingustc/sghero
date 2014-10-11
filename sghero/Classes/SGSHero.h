#ifndef SG_SKIRMISH_SCENE_HERO_H
#define SG_SKIRMISH_SCENE_HERO_H

#include "cocos2d.h"
#include "SGSObj.h"
USING_NS_CC;

typedef std::function<void()> SGSHeroActionFinishedCallback;

class SGSTerrain;
class SGSHero : public SGSObj 
{
public:
  typedef enum {
    HERO_AI_ATTACK,
    HERO_AI_STAY,
    HERO_AI_DEFENSE,
  } HERO_AI;

  typedef enum {
    HERO_category_LORD,
    HERO_category_INFANTRY,
    HERO_category_ARCHER,
    HERO_category_KNIGHT,
    HERO_category_HORSEARCHER,
    HERO_category_DEMOLISHER,
    HERO_category_MARTIALIST,
    HERO_category_THIEF,
    HERO_category_MAGE,
    HERO_category_PRIEST,
    HERO_category_WARLOCK,
    HERO_category_HORSEMAGE,
    HERO_category_DANCER,
    HERO_category_MAX,
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
  void            counterAttackFinished(Node* hero, void* ptr);
  static          SGSHero* create(const char* hero_name, HERO_SIDE side, SGObserver* observer);
  explicit        SGSHero(SGObserver* observer) : SGSObj(observer) {}

  void            doAction(const char* action);
  void            doAttackAction();

  void            faceTo(const char* direction);
  void            faceTo(HERO_DIRECTION direction);

  HERO_AI         getAI() { return __ai; }
  Animate*        getAttackAnimate();
  SGSPointList*   getAttackArea();
  SGSPointList*   getAttackAreaFromPosition(SGSPoint& pos);
  HERO_category   getcategory() { return __category; }
  HERO_DIRECTION  getRelativeDirection(SGSHero* other_hero);
  HERO_DIRECTION  getRelativeDirection(SGSPoint& point);
  HERO_DIRECTION  getRelativeDirectionFrom(SGSPoint& point, SGSPoint& from);
  HERO_SIDE       getSide() { return __side; }
  int             getStamina() { return __stamina; }
  HERO_STATUS     getStatus() { return __status; }
  Animate*        getWalkAnimate(HERO_DIRECTION direction);

  bool            init(const char* hero_name, HERO_SIDE side);
  bool            initActions();
  bool            initAttackActions();
  void            initcategory();
  void            initDataNum();
  bool            initSpecActions();

  bool            isActive() { return (__active && isVisible());}
  bool            isRival(SGSHero* hero);
 
  void            moveOneStep(SGSPointList& path);
  void            moveOneStepFinished(Node* node, void* ptr);
  void            moveTo(SGSPoint& target_pos);
  void            moveToAndAttack(SGSPoint& target_pos, SGSHero* enemy_hero);
  void            oneAIMove(const SGSHeroActionFinishedCallback& callback, SGSTerrain* terrain);

  void            setActionFinishedCallback(const SGSHeroActionFinishedCallback& callback);
  void            setActive(bool active); 
  void            setAI(HERO_AI ai) { __ai = ai; }
  void            setAI(std::string& ai);
  void            setDirection(HERO_DIRECTION direction);
  void            setStatus(std::string& status);
  void            setStatus(HERO_STATUS status);
  void            setTerrain(SGSTerrain* terrain) { __terrain = terrain; };



  SGSPoint        __previous_map_position;

private:
  typedef std::map<std::string, Animate*> ANIMATE_MAP;
  HERO_DIRECTION  getDirection(const char* direction);
  std::string&    getHeroResFile(const char* res_dir);

  void            updataSprite(); 
  HERO_AI         __ai;
  ANIMATE_MAP     __animate_map;
  bool            __active;
  HERO_category   __category;
  HERO_DIRECTION  __direction;
  std::string     __name;
  HERO_SIDE       __side;
  int             __stamina;
  HERO_STATUS     __status;
  SGSTerrain*     __terrain;

  Vector<SpriteFrame*> __sprite_frames;
  Vector<SpriteFrame*> __attack_sprite_frames;
  Vector<SpriteFrame*> __spec_sprite_frames;

  static SGSHeroActionFinishedCallback __action_finished_callback;
  
};

typedef Vector<SGSHero*> SGSHeroList;


#endif