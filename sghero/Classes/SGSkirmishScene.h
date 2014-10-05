#ifndef SG_SKIRMISH_SCENE_H
#define SG_SKIRMISH_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGSceneBase.h"
#include "SGSkirmishHero.h"
#include "SGSkirmishTerrain.h"


class SGSkirmishScene : public SGSceneBase
{
  friend SGSkirmishHero;
public:
  static Scene* createScene();

  CREATE_FUNC(SGSkirmishScene);
  virtual bool init();

  virtual ~SGSkirmishScene();

  void update(float dt);
  

  bool onTouchBegan(Touch *touch, Event *unused_event);
  void onTouchMoved(Touch *touch, Event *unused_event);
   
private:

  void startSceneScript(float dt);
  void mapMove(Vec2& delta);
  void requireFocus(const Vec2& pos);

  void notify();

  bool parseSkirmishSceneXmlFile(const char* file);
  bool parseSkirmishSettings(tinyxml2::XMLElement* setting);
  bool parseSkrimishEvents(tinyxml2::XMLElement* events);
  bool parseSkrimishTests(tinyxml2::XMLElement* tests);

  void checkTests();
  void gameLogic();
  bool gameLogicFriendTurn();
  bool gameLogicEnemyTurn();
  void switchToNextRound();
  void resetAllHeroActivity();
  void showHeroAvailabePath(SGSkirmishHero* hero);

  bool onHandleSettingMap(tinyxml2::XMLElement* setting);
  bool onHandleSettingTerrain(tinyxml2::XMLElement* setting);
  bool onHandleHeroAdd(tinyxml2::XMLElement* setting, SGSkirmishHero::HERO_SIDE side);
  bool onHandleEventHeroAction(tinyxml2::XMLElement* event);
  bool onHandleEventDelay(tinyxml2::XMLElement* event);
  bool onHandleEventHeroRemove(tinyxml2::XMLElement* event);
  bool onHandleEventHeroTurn(tinyxml2::XMLElement* event);
  bool onHandleEventHidenHeroAppear(tinyxml2::XMLElement* event);
  bool onHandleEventDialog(tinyxml2::XMLElement* event);
  bool onHandleEventHeroMove(tinyxml2::XMLElement* event);
  bool onHandleEventObjAdd(tinyxml2::XMLElement* event);
  bool onHandleEventMagicCall(tinyxml2::XMLElement* event);
  bool onHandleEventHeroStatusChange(tinyxml2::XMLElement* event);
  Vec2 mapPos2OpenGLPos(Vec2 origin);

  EventListenerTouchOneByOne* __event_listener;
  SGSkirmishHero* __selected_hero;
  int __map_width;
  int __map_height;
  SGSkirmishTerrain* __terrain;

  // state
  typedef enum {
    SKIRMISH_TURN_OUR,
    SKIRMISH_TURN_FRIEND,
    SKIRMISH_TURN_ENEMY,
  } SKIRMISH_TURN;
  SKIRMISH_TURN __turn;

  int __round;

  // Hero List
  typedef Vector<SGSkirmishHero*> SGSkirmishHeroList;
  SGSkirmishHeroList __our_heroes;
  SGSkirmishHeroList __friend_heroes;
  SGSkirmishHeroList __enemy_heroes;
  SGSkirmishHero* getHero(SGSkirmishHeroList& list);

  
  SGSceneEventList __test_list;

  

  // event handle state machine
  typedef enum {
    EVENT_HANDLE_STATE_NO_HERO_SELECTED,
    EVENT_HANDLE_STATE_HERO_SELECTED,
    EVENT_HANDLE_STATE_HERO_MOVED,
    EVENT_HANDLE_STATE_ATTACK_SELECTED,
    EVENT_HANDLE_STATE_MAGIC_SELECTED,
    EVENT_HANDLE_STATE_ITEM_SELECTED,
    EVENT_HANDLE_STATE_CANCEL_SELECTED,
    EVENT_HANDLE_STATE_IDLE_SELECTED,
  } EVENT_HANDLE_STATE;
  EVENT_HANDLE_STATE __event_handle_state;

  bool touchHandleStateMachine(Touch *touch);
  void onAttack(Ref* pSender);
  void onMagic(Ref* pSender) ;
  void onItem(Ref* pSender);
  void onIdle(Ref* pSender);
  void onCancel(Ref* pSender);
  void createActionSelectMenu();
  bool showAttackArea();

  void showInfo(std::string& info);

  // const char var
  static const char* WALK_PATH; 
  static const char* HERO_ACTION_MENU;

};

#endif