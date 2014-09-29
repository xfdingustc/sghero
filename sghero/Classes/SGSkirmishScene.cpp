#include "SGSkirmishScene.h"
#include "SimpleAudioEngine.h"
#include "SGGlobalSettings.h"
#include "SGSKirmishSwitchScene.h"
#include "SGSkirmishSceneObj.h"
#include "SGSkirmishSceneMagicCall.h"
using namespace CocosDenshion;

Scene* SGSkirmishScene::createScene()
{
  Scene* scene = Scene::create();

  SGSkirmishScene* layer = SGSkirmishScene::create();

  scene->addChild(layer);

  return scene;
}


bool SGSkirmishScene::init()
{
  if (!Layer::init()) {
    return false;
  }

  parseSkirmishSceneXmlFile("Skirmish/YingChuanZhiZhan.xml");

  // add touch handler
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  __event_listener = EventListenerTouchOneByOne::create();
  __event_listener->onTouchBegan = CC_CALLBACK_2(SGSkirmishScene::onTouchBegan, this);
  __event_listener->onTouchMoved = CC_CALLBACK_2(SGSkirmishScene::onTouchMoved, this);
  __event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(__event_listener,this);

  //init turn:
  __turn = SKIRMISH_TURN_OUR;

  //init round;
  __round = 0;
  return true;
}

void SGSkirmishScene::onExit()
{
  //Director::getInstance()->getEventDispatcher()->removeEventListener(__event_listener);
  Layer::onExit();
}


void SGSkirmishScene::mapMove(Vec2& delta)
{
  Vec2 cur_postion = this->getPosition();
  CCLOG("cur position x = %f y = %f", cur_postion.x, cur_postion.y);
  Vec2 new_pos = cur_postion + delta;
  Size size = Director::getInstance()->getVisibleSize();
  Sprite* map = (Sprite*)this->getChildByName("map");
  Size map_size = map->getContentSize();

  if (new_pos.x > 0) {
    new_pos.x = 0;
  }

  if (new_pos.y > map_size.height - size.height) {
    new_pos.y = map_size.height - size.height;
  }

  if (new_pos.y < 0) {
    new_pos.y = 0;
  }

  if (map_size.width < size.width) {
    new_pos.x = cur_postion.x;
  }

  Vec2 new_pos_diff = new_pos - cur_postion;

  this->setPosition(this->getPosition() + new_pos_diff);
}

void SGSkirmishScene::requireFocus(const Vec2& pos)
{
  Size size = Director::getInstance()->getVisibleSize();
  Vec2 center(size.width / 2, size.height / 2);

  Vec2 delta = center - pos;

  mapMove(delta);
}

void SGSkirmishScene::notify()
{
  this->removeChildByName("arrow");
}


void SGSkirmishScene::onTouchMoved(Touch *touch, Event *unused_event)
{
  mapMove(touch->getDelta());
  
}



bool SGSkirmishScene::parseSkirmishSceneXmlFile(const char* file_name)
{
  tinyxml2::XMLDocument* skirmish_scene_xml = new tinyxml2::XMLDocument();
  if (NULL == skirmish_scene_xml) {
    return false;
  }


  tinyxml2::XMLError error = skirmish_scene_xml->LoadFile(file_name);
  if (tinyxml2::XML_SUCCESS != error) {
    CCLOG("Parsing skirmish xml file error!!!");
    return false;
  }

  tinyxml2::XMLElement* scene = skirmish_scene_xml->RootElement();
  tinyxml2::XMLElement* section = scene->FirstChildElement("Section");
  tinyxml2::XMLElement* settings = section->FirstChildElement();
  while (settings) {
    parseSkirmishSettings(settings);
    settings = settings->NextSiblingElement();
  }

  tinyxml2::XMLElement* events = section->FirstChildElement("Event");
  if (events) {
    parseSkrimishEvents(events);
  }

  tinyxml2::XMLElement* tests = section->FirstChildElement("Test");
  if (tests) {
    parseSkrimishTests(tests);
  }

  scheduleUpdate();
  return true;
}

bool SGSkirmishScene::parseSkirmishSettings(tinyxml2::XMLElement* setting)
{
  std::string name = setting->Name();
  if (name == "Map") {
    onHandleSettingMap(setting);
  } else if (name == "OurSetting") {
    onHandleHeroAdd(setting, SGSkirmishSceneHero::HERO_SIDE_OURS);
  } else if (name == "FriendSetting") {
    onHandleHeroAdd(setting, SGSkirmishSceneHero::HERO_SIDE_FRIEND);
  } else if (name == "EnemySetting") {
    onHandleHeroAdd(setting, SGSkirmishSceneHero::HERO_SIDE_ENEMY);
  }
  return true;
}

bool SGSkirmishScene::parseSkrimishEvents(tinyxml2::XMLElement* events)
{
  tinyxml2::XMLElement* one_event = events->FirstChildElement();
  while(one_event) {
    __event_list.push_back(one_event);
    one_event = one_event->NextSiblingElement();
  }
  return true;
}

bool SGSkirmishScene::parseSkrimishTests(tinyxml2::XMLElement* tests)
{
  tinyxml2::XMLElement* one_test = tests->FirstChildElement();
  while(one_test) {
    __test_list.push_back(one_test);
    one_test = one_test->NextSiblingElement();
  }
  return true;
}

bool SGSkirmishScene::onHandleSettingMap(tinyxml2::XMLElement* setting)
{
  std::string map = setting->Attribute("map");
  __map_width = atoi(setting->Attribute("width"));
  __map_height = atoi(setting->Attribute("height"));

  
  std::string map_full_path = FileUtils::getInstance()->fullPathForFilename(map);
  Sprite* bg_map = Sprite::create(map_full_path);
  bg_map->setName("map");
  
  
  Size size = Director::getInstance()->getVisibleSize();

  
  bg_map->setAnchorPoint(Vec2(0.0f, 1.0f));
  bg_map->setPosition(Vec2(0.0f, size.height));
  this->addChild(bg_map);
  return true;
 
}

bool SGSkirmishScene::onHandleHeroAdd(tinyxml2::XMLElement* setting, SGSkirmishSceneHero::HERO_SIDE side)
{
  tinyxml2::XMLElement* one_friend_hero = setting->FirstChildElement();

  while(one_friend_hero) {
    std::string hero_name = one_friend_hero->Attribute("hero");
    int x = atoi(one_friend_hero->Attribute("x"));
    int y = atoi(one_friend_hero->Attribute("y"));
    std::string direction = one_friend_hero->Attribute("face");
    const char* hide = one_friend_hero->Attribute("hide");

    SGSkirmishSceneHero* hero = SGSkirmishSceneHero::create(hero_name.c_str(), side);
    hero->faceTo(direction.c_str());
    hero->setPosition(mapPos2OpenGLPos(Vec2(x,y)));
    if (!strcmp(hide, "true")) {
      hero->setVisible(false);
    }

    this->addChild(hero);
    // add into hero list
    switch (side)
    {
    case SGSkirmishSceneHero::HERO_SIDE_OURS:
      __our_heroes.pushBack(hero);
      break;
    case SGSkirmishSceneHero::HERO_SIDE_FRIEND:
      __friend_heroes.pushBack(hero);
      break;
    case SGSkirmishSceneHero::HERO_SIDE_ENEMY:
      __enemy_heroes.pushBack(hero);
      break;
    default:
      break;
    }
    one_friend_hero = one_friend_hero->NextSiblingElement();
  }
  return true;
}

bool SGSkirmishScene::onHandleEventHeroAction(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string action = event->Attribute("action");

  SGSkirmishSceneHero* hero = (SGSkirmishSceneHero*)this->getChildByName(hero_name);

  hero->doAction(action.c_str());
  return true;
}


bool SGSkirmishScene::onHandleEventHeroMove(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  SGSkirmishSceneHero* hero = (SGSkirmishSceneHero*)this->getChildByName(hero_name);
  hero->moveTo(mapPos2OpenGLPos(Vec2(x, y)));
  std::string direction = event->Attribute("face");
  hero->faceTo(direction.c_str());
  return true;
}


bool SGSkirmishScene::onHandleEventDelay(tinyxml2::XMLElement* event)
{
  float time = float(atoi(event->Attribute("time"))) ;
  unscheduleUpdate();
  scheduleOnce(schedule_selector(SGSkirmishScene::startSceneScript), time*0.1f);
  return true;
}

bool SGSkirmishScene::onHandleEventHeroRemove(tinyxml2::XMLElement* event)
{
  std::string name = event->Attribute("hero");
  this->removeChildByName(name);
  return true;

}

bool SGSkirmishScene::onHandleEventHeroTurn(tinyxml2::XMLElement* event)
{
  std::string direction;
  std::string hero_name = event->Attribute("hero");
  SGSkirmishSceneHero* hero_sprite = (SGSkirmishSceneHero*)this->getChildByName(hero_name);
  if (event->Attribute("face")) {
    direction = event->Attribute("face");
  } else {
    std::string target_hero_name = event->Attribute("target_hero");
   
    SGSkirmishSceneHero* target_hero_sprite = (SGSkirmishSceneHero*)this->getChildByName(target_hero_name);

    Vec2 hero_pos = hero_sprite->getPosition();
    Vec2 target_hero_pos = target_hero_sprite->getPosition();

  
    if (target_hero_pos.x > hero_pos.x) {
      direction = "east";
    } else if (target_hero_pos.x < hero_pos.x) {
      direction = "west";
    } else if (target_hero_pos.y > hero_pos.y) {
      direction = "north";
    } else {
      direction = "south";
    }
  }
  hero_sprite->faceTo(direction.c_str());
  return true;
}


bool SGSkirmishScene::onHandleEventDialog(tinyxml2::XMLElement* event)
{
  return true;
  std::string hero_name = event->Attribute("hero");
  SGSkirmishSceneHero* hero = (SGSkirmishSceneHero*)this->getChildByName(hero_name);
  requireFocus(hero->getPosition());
  Vec2 dialog_win_pos;
  Vec2 hero_pos = hero->getPosition();
  Size hero_size = hero->getContentSize();
  Size win_size = Director::getInstance()->getVisibleSize();
  
  Sprite* arrow = Sprite::create(DIAGLOG_WINDOW_ARROW_UP);
  arrow->setAnchorPoint(Vec2(0.5f, 0.0f));
  arrow->setPosition(Vec2(hero_pos.x + hero_size.width/2, hero_pos.y + hero_size.height));
  arrow->setName("arrow");
  this->addChild(arrow);

  dialog_win_pos.x = hero_pos.x + hero_size.width / 2;
  dialog_win_pos.y = hero_pos.y + hero_size.height + arrow->getContentSize().height;

  dialog_win_pos = convertToWorldSpace(dialog_win_pos);

  event->SetAttribute("x", dialog_win_pos.x);
  event->SetAttribute("y", dialog_win_pos.y);

  return SGSceneBase::onHandleEventDialog(event);
}

bool SGSkirmishScene::onHandleEventHidenHeroAppear(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  SGSkirmishSceneHero* hero = (SGSkirmishSceneHero*)this->getChildByName(hero_name);
  if (hero) {
    requireFocus(hero->getPosition());
    
    hero->setVisible(true);
  }
  return true;
}

bool SGSkirmishScene::onHandleEventObjAdd(tinyxml2::XMLElement* event)
{
  std::string obj_name = event->Attribute("obj");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  //currently only fire is supported so hard code here
  SGSkirmishSceneObj* obj = SGSkirmishSceneObj::create(obj_name.c_str());
  obj->setPosition(mapPos2OpenGLPos(Vec2(x, y)));
  this->addChild(obj);
  return true;
}

bool SGSkirmishScene::onHandleEventMagicCall(tinyxml2::XMLElement* event)
{
  std::string magic_name = event->Attribute("magic");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  Scene* scene = SGSkirmishSceneMagicCall::createScene(magic_name, mapPos2OpenGLPos(Vec2(x, y)));
  Director::getInstance()->pushScene(scene);
  return true;
}

bool SGSkirmishScene::onHandleEventHeroStatusChange(tinyxml2::XMLElement* event)
{
  if (event->Attribute("side")) {
    std::string side = event->Attribute("side");
    std::string status = event->Attribute("status");
    SGSKirmishSceneHeroList& hero_list = __our_heroes;
    if (side == "enemy") {
      hero_list = __enemy_heroes;
    } else if (side == "friend"){
      hero_list = __friend_heroes;
    } 
    SGSKirmishSceneHeroList::iterator iter;
    for (iter = hero_list.begin(); iter != hero_list.end(); iter++) {
      SGSkirmishSceneHero* hero = *iter;
      hero->setStatus(status);
    }

    
  }
  return true;
}

void SGSkirmishScene::startSceneScript(float dt)
{
  scheduleUpdate();
}

void SGSkirmishScene::checkTests()
{
  SGSceneEventList::iterator it;
  for (it = __test_list.begin(); it != __test_list.end(); it++) {
    tinyxml2::XMLElement* one_test = *it;
    //check the condition
    bool condition = false;
    if (one_test->Attribute("round")) {
      if (__round != atoi(one_test->Attribute("round"))) {
        continue;
      }
    }

    if (one_test->Attribute("turn")) {
      std::string turn_string = one_test->Attribute("turn");
      SKIRMISH_TURN turn;
      if (turn_string == "enemy") {
        turn = SKIRMISH_TURN_ENEMY;
      } else if (turn_string == "our") {
        turn = SKIRMISH_TURN_OUR;
      } else {
        turn = SKIRMISH_TURN_FRIEND;
      }
      if (turn != __turn) {
        continue;
      }
    }

    CCLog("Test condition meets");
    tinyxml2::XMLElement* one_event = one_test->FirstChildElement();
    while(one_event) {
      __event_list.push_back(one_event);
      one_event = one_event->NextSiblingElement();
    }
    __test_list.erase(it);
    return;

    
  }
}

void SGSkirmishScene::gameLogic()
{
  if (__round == 0) {
    __round++;
    __turn = SKIRMISH_TURN_OUR;
    switchToNextRound();
    return;
  }

  checkTests();

  switch(__turn) {
  case SKIRMISH_TURN_OUR:
    if (!getHero(__our_heroes)) {
      __turn = SKIRMISH_TURN_FRIEND;
      switchToNextRound();
    }
    break;
  case SKIRMISH_TURN_FRIEND:
    gameLogicFriendTurn();
    break;
  case SKIRMISH_TURN_ENEMY:
    if (true == gameLogicEnemyTurn()) {
      resetAllHeroActivity();
    }
    break;
  }
}

void SGSkirmishScene::resetAllHeroActivity()
{
  SGSKirmishSceneHeroList::iterator it;
  for (it = __our_heroes.begin(); it != __our_heroes.end(); it++) {
    SGSkirmishSceneHero* hero = *it;
    hero->resetActivity();
  }
  for (it = __friend_heroes.begin(); it != __friend_heroes.end(); it++) {
    SGSkirmishSceneHero* hero = *it;
    hero->resetActivity();
  }
  for (it = __enemy_heroes.begin(); it != __enemy_heroes.end(); it++) {
    SGSkirmishSceneHero* hero = *it;
    hero->resetActivity();
  }
}
bool SGSkirmishScene::gameLogicFriendTurn() 
{
  SGSkirmishSceneHero* hero = getHero(__friend_heroes);
  if (!hero) {
    __turn = SKIRMISH_TURN_ENEMY;
    switchToNextRound();
    return true;
  }
  hero->oneMove();
  CCLOG("friend %s has moved", hero->getName().c_str());
  return false;
}

bool SGSkirmishScene::gameLogicEnemyTurn()
{
  SGSkirmishSceneHero* hero = getHero(__enemy_heroes);
  if (!hero) {
    __turn = SKIRMISH_TURN_OUR;
    __round++;
    switchToNextRound();
    return true;
  }
  hero->oneMove();
  CCLOG("enemy %s has moved", hero->getName().c_str());
  return false;
}
SGSkirmishSceneHero* SGSkirmishScene::getHero(SGSKirmishSceneHeroList& list)
{
  for (int i = 0; i < list.size(); i++) {
    SGSkirmishSceneHero* hero = list.at(i);
    if (hero->isActive()) {
      return hero;
    }
  }
  return NULL;
}
void SGSkirmishScene::switchToNextRound()
{
  CCLOG("switch to next round = %d turn = %d", __round, __turn);
  return;
  Scene* scene = SGSkirmishSwitchScene::createScene(__round, __turn);
  Director::getInstance()->pushScene(scene);
}

void SGSkirmishScene::update(float dt) {
  if (__event_list.size() == 0) {
    gameLogic() ;
    return;
  } 
  tinyxml2::XMLElement* event = __event_list.front();
  const char* name = event->Name();

  bool ret = false;

  if (!strcmp(name, "SoundTrack")) {
    ret = onHandleEventSoundTrack(event);
  } else if (!strcmp(name, "Dialog")) {
    ret = onHandleEventDialog(event);
  } else if (!strcmp(name, "HeroAction")) {
    ret = onHandleEventHeroAction(event);
  } else if (!strcmp(name, "SoundEffect")) {
    ret = onHandleEventSoundEffect(event);
  } else if (!strcmp(name, "Delay")) {
    ret = onHandleEventDelay(event);
  } else if (!strcmp(name, "HeroRemove")) {
    ret = onHandleEventHeroRemove(event);
  } else if (!strcmp(name, "HeroTurn")) {
    ret = onHandleEventHeroTurn(event);
  } else if (!strcmp(name, "HidenHeroAppear")) {
    ret = onHandleEventHidenHeroAppear(event);
  } else if (!strcmp(name, "HeroMove")) {
    ret = onHandleEventHeroMove(event);
  } else if (!strcmp(name, "SkirmishObjAdd")) {
    ret = onHandleEventObjAdd(event);
  } else if (!strcmp(name, "MagicCall")) {
    ret = onHandleEventMagicCall(event);
  } else if (!strcmp(name, "HeroStatusChange")) {
    ret = onHandleEventHeroStatusChange(event);
  }

  if (ret) {
    __event_list.pop_front();
  }
}

Vec2 SGSkirmishScene::mapPos2OpenGLPos(Vec2 origin)
{
  Vec2 new_pos;

  Size size = this->getContentSize();

  new_pos.x = (origin.x + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH ;
  new_pos.y = size.height - (origin.y + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
  return new_pos;
}