#ifndef SG_SKIRMISH_SCENE_H
#define SG_SKIRMISH_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGSceneBase.h"
#include "SGSkirmishHero.h"
#include "SGSkirmishTerrain.h"
#include "tinyxml2/tinyxml2.h"

class SGSkirmishScene : public SGSceneBase
{
  friend SGSkirmishHero;
public:
  static Scene* createScene();

  CREATE_FUNC(SGSkirmishScene);
  virtual bool init();

  virtual ~SGSkirmishScene();

  void update(float dt);
  

  bool onTouchBegan(Touch *touch, Event *unused_event) { return  true; };
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

};

#endif