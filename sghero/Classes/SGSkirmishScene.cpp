#include "SGSkirmishScene.h"
#include "SGSkirmishSceneHero.h"
#include "SGGlobalSettings.h"

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
  Director::getInstance()->getEventDispatcher()->removeEventListener(__event_listener);
  Layer::onExit();
}


void SGSkirmishScene::onTouchMoved(Touch *touch, Event *unused_event)
{
  
  Vec2 pos_diff = touch->getDelta();
  Vec2 new_pos = this->getPosition();
  new_pos.add(pos_diff);
  if (new_pos.x > 0) {
    new_pos.x = 0;
  }
  if (new_pos.y < 0) {
    new_pos.y = 0;
  }
  this->setPosition(new_pos);
  
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
  return true;
}

bool SGSkirmishScene::parseSkirmishSettings(tinyxml2::XMLElement* setting)
{
  const char* name = setting->Name();
  if (!strcmp(name, "Map")) {
    onHandleSettingMap(setting);
  } else if (!strcmp(name, "FriendSetting")) {
    onHandleSettingFriend(setting);
  }
  return true;
}

void SGSkirmishScene::onHandleSettingMap(tinyxml2::XMLElement* setting)
{
  std::string map = setting->Attribute("map");

  std::string map_full_path = FileUtils::getInstance()->fullPathForFilename(map);
  Sprite* bg_map = Sprite::create(map_full_path);
  bg_map->setAnchorPoint(Vec2(0.0f, 1.0f));
  Size size = Director::getInstance()->getVisibleSize();
  bg_map->setPosition(Vec2(0.0f, size.height));
  this->addChild(bg_map);
}

void SGSkirmishScene::onHandleSettingFriend(tinyxml2::XMLElement* setting)
{
  tinyxml2::XMLElement* one_friend_hero = setting->FirstChildElement();

  while(one_friend_hero) {
    std::string hero_name = one_friend_hero->Attribute("hero");
    int x = atoi(one_friend_hero->Attribute("x"));
    int y = atoi(one_friend_hero->Attribute("y"));
    const char* hide = one_friend_hero->Attribute("hide");

    SGSkirmishSceneHero* hero = SGSkirmishSceneHero::create(hero_name.c_str(), SGSkirmishSceneHero::HERO_SIDE_FRIEND);
    hero->setPosition(mapPos2OpenGLPos(Vec2(x,y)));
    if (!strcmp(hide, "true")) {
      //hero->setVisible(false);
    }

    this->addChild(hero);
    one_friend_hero = one_friend_hero->NextSiblingElement();
  }

}

Vec2 SGSkirmishScene::mapPos2OpenGLPos(Vec2 origin)
{
  Vec2 new_pos;

  Size size = this->getContentSize();

  new_pos.x = origin.x * SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH;
  new_pos.y = size.height - origin.y * SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
  return new_pos;
}