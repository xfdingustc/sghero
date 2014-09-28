#ifndef SG_SKIRMISH_SCENE_H
#define SG_SKIRMISH_SCENE_H

#include "cocos2d.h"
#include "SGSkirmishSceneHero.h"
#include "SGSceneBase.h"
USING_NS_CC;
#include "tinyxml2/tinyxml2.h"

class SGSkirmishScene : public SGSceneBase
{
public:
  static Scene* createScene();

  CREATE_FUNC(SGSkirmishScene);
  virtual bool init();
  void update(float dt);
  virtual void onExit();

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
  void gameLogicFriendTurn();
  void gameLogicEnemyTurn();
  void switchToNextRound();

  void onHandleSettingMap(tinyxml2::XMLElement* setting);
  void onHandleHeroAdd(tinyxml2::XMLElement* setting, SGSkirmishSceneHero::HERO_SIDE side);
  void onHandleEventHeroAction(tinyxml2::XMLElement* event);
  void onHandleEventDelay(tinyxml2::XMLElement* event);
  void onHandleEventHeroRemove(tinyxml2::XMLElement* event);
  bool onHandleEventHeroTurn(tinyxml2::XMLElement* event);

  void onHandleEventDialog(tinyxml2::XMLElement* event);

  Vec2 mapPos2OpenGLPos(Vec2 origin);

  EventListenerTouchOneByOne* __event_listener;

  int __map_width;
  int __map_height;

  // state
  typedef enum {
    SKIRMISH_TURN_OUR,
    SKIRMISH_TURN_FRIEND,
    SKIRMISH_TURN_ENEMY,
  } SKIRMISH_TURN;
  SKIRMISH_TURN __turn;

  int __round;

  // Hero List
  typedef Vector<SGSkirmishSceneHero*> SGSKirmishSceneHeroList;
  SGSKirmishSceneHeroList __our_heroes;
  SGSKirmishSceneHeroList __friend_heroes;
  SGSKirmishSceneHeroList __enemy_heroes;
  SGSkirmishSceneHero* getHero(SGSKirmishSceneHeroList& list);

  
  SGSceneEventList __test_list;

};

#endif