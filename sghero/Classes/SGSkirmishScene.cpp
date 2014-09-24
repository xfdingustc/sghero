#include "SGSkirmishScene.h"
#include "SimpleAudioEngine.h"
#include "SGGlobalSettings.h"

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
  Vec2 new_pos_diff = new_pos - cur_postion;

  this->setPosition(this->getPosition() + new_pos_diff);
}

void SGSkirmishScene::requireFocus(const Vec2& pos)
{
  Size size = Director::getInstance()->getVisibleSize();
  Vec2 center(size.width, size.height);

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


  scheduleUpdate();
  return true;
}

bool SGSkirmishScene::parseSkirmishSettings(tinyxml2::XMLElement* setting)
{
  const char* name = setting->Name();
  if (!strcmp(name, "Map")) {
    onHandleSettingMap(setting);
  } else if (!strcmp(name, "FriendSetting")) {
    onHandleHeroAdd(setting, SGSkirmishSceneHero::HERO_SIDE_FRIEND);
  } else if (!strcmp(name, "EnemySetting")) {
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

void SGSkirmishScene::onHandleSettingMap(tinyxml2::XMLElement* setting)
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
 
}

void SGSkirmishScene::onHandleHeroAdd(tinyxml2::XMLElement* setting, SGSkirmishSceneHero::HERO_SIDE side)
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
    one_friend_hero = one_friend_hero->NextSiblingElement();
  }

}

void SGSkirmishScene::onHandleEventHeroAction(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string action = event->Attribute("action");

  SGSkirmishSceneHero* hero = (SGSkirmishSceneHero*)this->getChildByName(hero_name);

  hero->doAction(action.c_str());
  __event_list.pop_front();
}

void SGSkirmishScene::onHandleEventDelay(tinyxml2::XMLElement* event)
{
  float time = float(atoi(event->Attribute("time"))) ;
  unscheduleUpdate();
  scheduleOnce(schedule_selector(SGSkirmishScene::startSceneScript), time*0.1f);
  __event_list.pop_front();
}

void SGSkirmishScene::onHandleEventHeroRemove(tinyxml2::XMLElement* event)
{
  std::string name = event->Attribute("hero");
  this->removeChildByName(name);
  __event_list.pop_front();

}

bool SGSkirmishScene::onHandleEventHeroTurn(tinyxml2::XMLElement* event)
{
  std::string hero_name = event->Attribute("hero");
  std::string target_hero_name = event->Attribute("target_hero");

  SGSkirmishSceneHero* hero_sprite = (SGSkirmishSceneHero*)this->getChildByName(hero_name);
  SGSkirmishSceneHero* target_hero_sprite = (SGSkirmishSceneHero*)this->getChildByName(target_hero_name);

  Vec2 hero_pos = hero_sprite->getPosition();
  Vec2 target_hero_pos = target_hero_sprite->getPosition();

  std::string direction;
  if (target_hero_pos.x > hero_pos.x) {
    direction = "east";
  } else if (target_hero_pos.x < hero_pos.x) {
    direction = "west";
  } else if (target_hero_pos.y > hero_pos.y) {
    direction = "north";
  } else {
    direction = "south";
  }
  hero_sprite->faceTo(direction.c_str());

  __event_list.pop_front();
  return true;
}


void SGSkirmishScene::onHandleEventDialog(tinyxml2::XMLElement* event)
{
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

  SGSceneBase::onHandleEventDialog(event);
}

void SGSkirmishScene::startSceneScript(float dt)
{
  scheduleUpdate();
}

void SGSkirmishScene::update(float dt) {
  if (__event_list.size() == 0) {
    return ;
  } 
  tinyxml2::XMLElement* event = __event_list.front();
  const char* name = event->Name();

  if (!strcmp(name, "SoundTrack")) {
    onHandleEventSoundTrack(event);
  } else if (!strcmp(name, "Dialog")) {
    onHandleEventDialog(event);
  } else if (!strcmp(name, "HeroAction")) {
    onHandleEventHeroAction(event);
  } else if (!strcmp(name, "SoundEffect")) {
    onHandleEventSoundEffect(event);
  } else if (!strcmp(name, "Delay")) {
    onHandleEventDelay(event);
  } else if (!strcmp(name, "HeroRemove")) {
    onHandleEventHeroRemove(event);
  } else if (!strcmp(name, "HeroTurn")) {
    onHandleEventHeroTurn(event);
  }
}

Vec2 SGSkirmishScene::mapPos2OpenGLPos(Vec2 origin)
{
  Vec2 new_pos;

  Size size = this->getContentSize();

  new_pos.x = origin.x * SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH;
  new_pos.y = size.height - (origin.y + 1) * SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
  return new_pos;
}