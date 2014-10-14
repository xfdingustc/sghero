#include "SimpleAudioEngine.h"
#include "SGGlobalSettings.h"
#include "SGSkirmishInfo.h"
#include "SGSObj.h"
#include "SGSkirmishScene.h"
#include "SGSStrategy.h"
#include "SGSSwitchScene.h"
#include "SGSMagicCall.h"
#include "json/document.h"

using namespace CocosDenshion;

const char* SGSkirmishScene::WALK_PATH = "walk_path"; 
const char* SGSkirmishScene::HERO_ACTION_MENU = "hero_action_menu";
SGSkirmishScene* SGSkirmishScene::__current_skirmish_scene;

Scene* SGSkirmishScene::createScene()
{
  Scene* scene = Scene::create();

  SGSkirmishScene* layer = SGSkirmishScene::create();

  SGSkirmishScene::__current_skirmish_scene = layer;
  layer->__control_panel = SGSControlPanel::create();
  layer->__info_panel = SGSInfoPanel::create();
  scene->addChild(layer);
  scene->addChild(layer->__control_panel);
  scene->addChild(layer->__info_panel);
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
  __selected_hero = NULL;
  __event_handle_state = EVENT_HANDLE_STATE_NO_HERO_SELECTED;



  scheduleOnce(schedule_selector(SGSkirmishScene::startSkirmish), 1.0f);
  return true;
}

SGSkirmishScene::~SGSkirmishScene()
{
  delete __scene_xml;
  delete __terrain;
}


void SGSkirmishScene::mapMove(Vec2& delta)
{
  Vec2 cur_postion = this->getPosition();
  Vec2 new_pos = cur_postion + delta;
  Size size = Director::getInstance()->getVisibleSize();
  Sprite* map = (Sprite*)this->getChildByName("map");
  Size map_size = map->getContentSize();

  if (new_pos.x > 0) {
    new_pos.x = 0;
  }

  int x_min = size.width - map_size.width - size.height/3;

  if (new_pos.x < x_min) {
    new_pos.x = x_min;
  }

  if (new_pos.y > map_size.height - size.height) {
    new_pos.y = map_size.height - size.height;
  }

  if (new_pos.y < 0) {
    new_pos.y = 0;
  }

  if (map_size.width < size.width) {
    //new_pos.x = cur_postion.x;
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

void SGSkirmishScene::notify(const char* reason, void* ptr)
{
  std::string notify_reason = reason;
  if (notify_reason == "hero_move_finished") {
    startSkirmish(1.0f);
  }
}


bool SGSkirmishScene::onTouchBegan(Touch *touch, Event *unused_event)
{
  return touchHandleStateMachine(touch);
}

bool SGSkirmishScene::touchHandleStateMachine(Touch *touch)
{
  Vec2 pos = this->convertToNodeSpace(touch->getLocation());
  SGSHero* hero = NULL;
  switch (__event_handle_state)
  {
  case EVENT_HANDLE_STATE_NO_HERO_SELECTED:
    hero = __terrain->findHeroByPosition(pos);
    if (hero) {
      if (hero->isActive()) {
        showHeroAvailabePath(hero);
        __selected_hero = hero;
        __selected_hero->__previous_map_position = __selected_hero->getMapPosition();
        __event_handle_state = EVENT_HANDLE_STATE_HERO_SELECTED;
        return true;
      } else {
        std::string info_msg = "action_finished";
        showInfo(info_msg);
      }
    }
    break;
  case EVENT_HANDLE_STATE_HERO_SELECTED:
    hero = __terrain->findHeroByPosition(pos);
    if (hero && hero != __selected_hero) {
      showHeroAvailabePath(hero);
      __selected_hero = hero;
      __event_handle_state = EVENT_HANDLE_STATE_HERO_SELECTED;
      return true;
    }
    if ((hero && hero == __selected_hero) || (!hero && __selected_hero)) {
      SGSArea* area = (SGSArea*)this->getChildByName(WALK_PATH);
      if (area && area->containPoint(pos)) {
        __selected_hero->moveTo(SGSPoint::openGLPos2MapPos(pos));
        this->removeChildByName(WALK_PATH);
        createActionSelectMenu();
        __event_handle_state = EVENT_HANDLE_STATE_HERO_MOVED;
        return true;
      }
    } 
    break;
  case EVENT_HANDLE_STATE_HERO_MOVED:

    break;
  case EVENT_HANDLE_STATE_ATTACK_SELECTED:
    hero = __terrain->findHeroByPosition(pos);
    if (hero && !__selected_hero->isRival(hero)) {
      std::string info_msg =  "not_enemy";
      showInfo(info_msg);
      return false;
    }
    break;
  default:
    break;
  }

  return true;

}

void SGSkirmishScene::createActionSelectMenu()
{
  rapidjson::Document menu_json;
  std::string res_json_file = FileUtils::getInstance()->fullPathForFilename(MENU_ITEM_TEXT_JSON_FILE);
  std::string json_data = FileUtils::getInstance()->getStringFromFile(res_json_file.c_str());

  menu_json.Parse<rapidjson::kParseDefaultFlags>(json_data.c_str());
  if (menu_json.HasParseError()) {
    log("Parsing hero resource json file error!! %s", menu_json.GetParseError());
    return;
  } else if (menu_json.IsObject()) {
    const rapidjson::Value &res_list = menu_json["HeroActionMenu"];
    if (res_list.IsArray()) {
      int i = 0;
      const rapidjson::Value &val = res_list[i];
      Label *attackLabel = Label::create(val["text"].GetString(),TEXT_FONT_NAME, TEXT_FONT_SIZE);
      attackLabel->setColor(Color3B::BLACK);
      MenuItemLabel *attackMenuItem = MenuItemLabel::create(attackLabel, this,
        menu_selector(SGSkirmishScene::onAttack));

      attackMenuItem->setPosition(ccp(0, TEXT_FONT_SIZE*4));

      const rapidjson::Value &val1 = res_list[1];
      Label *magicLabel = Label::create(val1["text"].GetString(),TEXT_FONT_NAME, TEXT_FONT_SIZE);
      magicLabel->setColor(Color3B::BLACK);
      MenuItemLabel *magicMenuItem = MenuItemLabel::create(magicLabel, this,
        menu_selector(SGSkirmishScene::onMagic));
      magicMenuItem->setPosition(ccp(0, TEXT_FONT_SIZE*3));

      const rapidjson::Value &val2  = res_list[2];
      Label *itemLabel = Label::create(val2["text"].GetString(),TEXT_FONT_NAME, TEXT_FONT_SIZE);
      itemLabel->setColor(Color3B::BLACK);
      MenuItemLabel *itemMenuItem = MenuItemLabel::create(itemLabel, this,
        menu_selector(SGSkirmishScene::onItem));
      itemMenuItem->setPosition(ccp(0, TEXT_FONT_SIZE*2));

      const rapidjson::Value &val3  = res_list[3];
      Label *idleLabel = Label::create(val3["text"].GetString(),TEXT_FONT_NAME, TEXT_FONT_SIZE);
      idleLabel->setColor(Color3B::BLACK);
      MenuItemLabel *idleMenuItem = MenuItemLabel::create(idleLabel, this,
        menu_selector(SGSkirmishScene::onIdle));
      idleMenuItem->setPosition(ccp(0, TEXT_FONT_SIZE*1));

      const rapidjson::Value &val4  = res_list[4];
      Label *cancelLabel = Label::create(val4["text"].GetString(),TEXT_FONT_NAME, TEXT_FONT_SIZE);
      cancelLabel->setColor(Color3B::BLACK);
      MenuItemLabel *cancelMenuItem = MenuItemLabel::create(cancelLabel, this,
        menu_selector(SGSkirmishScene::onCancel));
      cancelMenuItem->setPosition(ccp(0, 0));

      Menu* hero_action_menu = Menu::create(attackMenuItem, magicMenuItem,
        itemMenuItem, idleMenuItem, cancelMenuItem,NULL);
      hero_action_menu->setAnchorPoint(Vec2(0.0f, 0.5f));
      Vec2 pos = __selected_hero->getPosition();
      pos.x += __selected_hero->getContentSize().width;
      hero_action_menu->setPosition(pos);
      hero_action_menu->setName(HERO_ACTION_MENU);
      this->addChild(hero_action_menu);
    }
  }
}

bool SGSkirmishScene::showAttackArea()
{
  std::string res_name = SG_SKIRMISH_AREA_ATTACK;
  SGSArea* attack_area = SGSArea::create(res_name, *__selected_hero->getAttackArea());
  attack_area->show();

  if (!__terrain->findEnemyHeroInArea(attack_area, __selected_hero)) {
    std::string info_msg =  "no_enemy_in_attack_area";
    showInfo(info_msg);
    return false;
  } else {
    this->addChild(attack_area);
    return true;
  }

}


void SGSkirmishScene::showInfo(std::string& info)
{
  Scene* info_scene = SGSkirmishInfo::createScene(info);
  Director::getInstance()->pushScene(info_scene);
}


void SGSkirmishScene::onAttack(Ref* pSender)
{
  if (showAttackArea()) {
    this->removeChildByName(HERO_ACTION_MENU);
    __event_handle_state = EVENT_HANDLE_STATE_ATTACK_SELECTED;
  }
}
void SGSkirmishScene::onMagic(Ref* pSender) 
{
  this->removeChildByName(HERO_ACTION_MENU);
  __event_handle_state = EVENT_HANDLE_STATE_MAGIC_SELECTED;
}
void SGSkirmishScene::onItem(Ref* pSender) 
{
  this->removeChildByName(HERO_ACTION_MENU);
  __event_handle_state = EVENT_HANDLE_STATE_ITEM_SELECTED;
}
void SGSkirmishScene::onIdle(Ref* pSender)
{
  this->removeChildByName(HERO_ACTION_MENU);
  __selected_hero->setActive(false);
  __event_handle_state = EVENT_HANDLE_STATE_NO_HERO_SELECTED;
}
void SGSkirmishScene::onCancel(Ref* pSender)
{
  this->removeChildByName(HERO_ACTION_MENU);
  __selected_hero->setMapPosition(__selected_hero->__previous_map_position);
  __event_handle_state = EVENT_HANDLE_STATE_NO_HERO_SELECTED;
}


void SGSkirmishScene::onTouchMoved(Touch *touch, Event *unused_event)
{
  mapMove(touch->getDelta());
  
}



bool SGSkirmishScene::parseSkirmishSceneXmlFile(const char* file_name)
{
  __scene_xml = new tinyxml2::XMLDocument();
  if (NULL == __scene_xml) {
    return false;
  }


  tinyxml2::XMLError error = __scene_xml->LoadFile(file_name);
  if (tinyxml2::XML_SUCCESS != error) {
    CCLOG("Parsing skirmish xml file error!!!");
    return false;
  }

  tinyxml2::XMLElement* scene = __scene_xml->RootElement();
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
  return true;
}

bool SGSkirmishScene::parseSkirmishSettings(tinyxml2::XMLElement* setting)
{
  std::string name = setting->Name();
  if (name == "Map") {
    onHandleSettingMap(setting);
  } else if (name == "Terrain") {
    onHandleSettingTerrain(setting);
  } else if (name == "OurSetting") {
    onHandleHeroAdd(setting, SGSHero::HERO_SIDE_OURS);
  } else if (name == "FriendSetting") {
    onHandleHeroAdd(setting, SGSHero::HERO_SIDE_FRIEND);
  } else if (name == "EnemySetting") {
    onHandleHeroAdd(setting, SGSHero::HERO_SIDE_ENEMY);
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
bool SGSkirmishScene::onHandleSettingTerrain(tinyxml2::XMLElement* setting)
{
  std::string terrain_file = FileUtils::getInstance()->fullPathForFilename(setting->Attribute("terrain"));
  __terrain = SGSTerrain::create(terrain_file, Size(__map_width, __map_height));
  return true;

}
bool SGSkirmishScene::onHandleHeroAdd(tinyxml2::XMLElement* setting, SGSHero::HERO_SIDE side)
{
  tinyxml2::XMLElement* one_hero = setting->FirstChildElement();

  while(one_hero) {
    std::string hero_name = one_hero->Attribute("hero");
    int x = atoi(one_hero->Attribute("x"));
    int y = atoi(one_hero->Attribute("y"));
    std::string direction = one_hero->Attribute("face");
    const char* hide = one_hero->Attribute("hide");

    SGSHero* hero = SGSHero::create(hero_name.c_str(), side, __terrain);
    if (!hero) {
      log("Failed to allocate hero");
      return true;
    }
    hero->setMapPosition(SGSPoint(x, y));
    hero->setTerrain(__terrain);
    if (!strcmp(hide, "true")) {
      hero->setVisible(false);
    }

    this->addChild(hero);
    hero->faceTo(direction.c_str());
    if (one_hero->Attribute("AI")) {
      std::string hero_ai = one_hero->Attribute("AI");
      hero->setAI(hero_ai);
    }

    // add into hero list
    switch (side)
    {
    case SGSHero::HERO_SIDE_OURS:
      __our_heroes.pushBack(hero);
      break;
    case SGSHero::HERO_SIDE_FRIEND:
      __friend_heroes.pushBack(hero);
      break;
    case SGSHero::HERO_SIDE_ENEMY:
      __enemy_heroes.pushBack(hero);
      break;
    default:
      break;
    }
    one_hero = one_hero->NextSiblingElement();
  }
  return true;
}

bool SGSkirmishScene::onHandleEventHeroAction(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string action = event->Attribute("action");

  SGSHero* hero = (SGSHero*)this->getChildByName(hero_name);

  hero->doAction(action.c_str());
  return true;
}


bool SGSkirmishScene::onHandleEventHeroMove(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  SGSHero* hero = (SGSHero*)this->getChildByName(hero_name);
  hero->moveTo(SGSPoint(x, y));
  std::string direction = event->Attribute("face");
  return true;
}


bool SGSkirmishScene::onHandleEventDelay(tinyxml2::XMLElement* event)
{
  float time = float(atoi(event->Attribute("time"))) ;
  stopSkirmish();
  scheduleOnce(schedule_selector(SGSkirmishScene::startSkirmish), time*0.1f);
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
  SGSHero* hero_sprite = (SGSHero*)this->getChildByName(hero_name);
  if (!hero_sprite) {
    return true;
  }
  if (event->Attribute("face")) {
    direction = event->Attribute("face");
  } else {
    std::string target_hero_name = event->Attribute("target_hero");
   
    SGSHero* target_hero_sprite = (SGSHero*)this->getChildByName(target_hero_name);

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
  SGSHero* hero = (SGSHero*)this->getChildByName(hero_name);
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
  SGSHero* hero = (SGSHero*)this->getChildByName(hero_name);
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
  SGSObj* obj = SGSObj::create(obj_name.c_str(), __terrain);
  obj->setMapPosition(SGSPoint(x, y));
  this->addChild(obj);
  return true;
}

bool SGSkirmishScene::onHandleEventMagicCall(tinyxml2::XMLElement* event)
{
  std::string magic_name = event->Attribute("magic");
  int x = atoi(event->Attribute("x"));
  int y = atoi(event->Attribute("y"));
  Scene* scene = SGSMagicCall::createScene(magic_name, SGSPoint::mapPos2OpenGLPos(SGSPoint(x,y)));
  Director::getInstance()->pushScene(scene);

  return true;
}

bool SGSkirmishScene::onHandleEventHeroStatusChange(tinyxml2::XMLElement* event)
{
  if (event->Attribute("side")) {
    std::string side = event->Attribute("side");
    std::string status = event->Attribute("status");
    SGSHeroList* hero_list = &__our_heroes;
    if (side == "enemy") {
      hero_list = &__enemy_heroes;
    } else if (side == "friend"){
      hero_list = &__friend_heroes;
    } 
    SGSHeroList::iterator iter;
    for (iter = hero_list->begin(); iter != hero_list->end(); iter++) {
      SGSHero* hero = *iter;
      hero->setStatus(status);
    }

    
  }
  return true;
}

void SGSkirmishScene::startSkirmish(float dt)
{
  scheduleUpdate();
}
void SGSkirmishScene::stopSkirmish()
{
  unscheduleUpdate();
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

    log("Test condition meets");
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
  case SKIRMISH_TURN_OUR: {
    if (!getHero(__our_heroes)) {
      __turn = SKIRMISH_TURN_FRIEND;
      switchToNextRound();
    } 
    break;
                          }
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
  SGSHeroList::iterator it;
  for (it = __our_heroes.begin(); it != __our_heroes.end(); it++) {
    SGSHero* hero = *it;
    hero->setActive(true);
  }
  for (it = __friend_heroes.begin(); it != __friend_heroes.end(); it++) {
    SGSHero* hero = *it;
    hero->setActive(true);
  }
  for (it = __enemy_heroes.begin(); it != __enemy_heroes.end(); it++) {
    SGSHero* hero = *it;
    hero->setActive(true);
  }
}
bool SGSkirmishScene::gameLogicFriendTurn() 
{
  SGSHero* hero = getHero(__friend_heroes);
  if (!hero) {
    __turn = SKIRMISH_TURN_ENEMY;
    switchToNextRound();
    return true;
  }
  gameLogicMoveOneHero(hero);
  CCLOG("friend %s has moved", hero->getName().c_str());
  return false;
}

bool SGSkirmishScene::gameLogicEnemyTurn()
{
  SGSHero* hero = getHero(__enemy_heroes);
  if (!hero) {
    __turn = SKIRMISH_TURN_OUR;
    __round++;
    switchToNextRound();
    return true;
  }
  gameLogicMoveOneHero(hero);
  CCLOG("enemy %s has moved", hero->getName().c_str());
  return false;
}

bool SGSkirmishScene::gameLogicMoveOneHero(SGSHero* hero)
{
  stopSkirmish();
  hero->oneAIMove(std::bind(&SGSkirmishScene::strategyOneMoveFinished, this), __terrain);
  return true;
}


void SGSkirmishScene::showHeroAvailabePath(SGSHero* hero)
{
  this->removeChildByName("walk_path");
  std::string res_name = SG_SKIRMISH_AREA_PATH;
  SGSArea* area = SGSArea::create(res_name, __terrain->calcHeroAvailabePath(hero));
  area->setName("walk_path");
  this->addChild(area);
  area->show();
}

void SGSkirmishScene::strategyOneMoveFinished()
{
  startSkirmish(1.0f);
}


SGSHero* SGSkirmishScene::getHero(SGSHeroList& list)
{
  for (int i = 0; i < list.size(); i++) {
    SGSHero* hero = list.at(i);
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
  Scene* scene = SGSSwitchScene::createScene(__round, __turn);
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

