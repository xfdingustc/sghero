
#include "SGDramaScene.h"
#include "SGDramaSceneHero.h"
#include "SimpleAudioEngine.h"
#include "xxhash/xxhash.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SGDramaScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = SGDramaScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

bool SGDramaScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }

  parseDramaSceneXmlFile("DramaScenes/DramaScene00.xml");
  scheduleUpdate();
  
  return true;
}


bool SGDramaScene::parseDramaSceneXmlFile(const char* file_name)
{
  tinyxml2::XMLDocument* drama_scene_xml = new tinyxml2::XMLDocument();
  if (NULL == drama_scene_xml) {
    return false;
  }


  tinyxml2::XMLError error = drama_scene_xml->LoadFile(file_name);
  if (tinyxml2::XML_SUCCESS != error) {
    return false;
  }


  tinyxml2::XMLElement* scene = drama_scene_xml->RootElement();
  tinyxml2::XMLElement* section = scene->FirstChildElement("Section");
  while(section) {
    tinyxml2::XMLElement* event = section->FirstChildElement("Event");
    while(event) {
      tinyxml2::XMLElement* one_event = event->FirstChildElement();
      while(one_event) {
        //parseDrameSceneEvents(one_event);
        event_list.push_back(one_event);
        one_event = one_event->NextSiblingElement();
      }
      event = event->NextSiblingElement();
    }
    section = section->NextSiblingElement();
  }

  return true;

}

bool SGDramaScene::parseDrameSceneEvents(tinyxml2::XMLElement* event)
{
  const char* name = event->Name();
  CCLOG("event name = %s", name);

  if (!strcmp(name, "BackgroundImage")) {
    const char* map_name = event->Attribute("image");
    auto bg_image = Sprite::create(map_name);
    bg_image->setAnchorPoint(Vec2(0,0));
    bg_image->setPosition(Vec2::ZERO);
    this->addChild(bg_image);

  } else if (!strcmp(name, "HeroAppear")) {
    //const tinyxml2::XMLAttribute* attribute = event->Attribute("hero");
    const char* hero_name = event->Attribute("hero");
    CCLOG("hero name = %s", hero_name);
  } 
  return true;
}

void SGDramaScene::update(float dt)
{
  // TODO: no event list, we need move to the next scene
  if (event_list.size() == 0) {
    return ;
  } 
  tinyxml2::XMLElement* event = event_list.front();

  const char* name = event->Name();
  if (!strcmp(name, "BackgroundImage")) {
    const char* map_name = event->Attribute("image");
    auto bg_image = Sprite::create(map_name);
    bg_image->setAnchorPoint(Vec2(0,0));
    bg_image->setPosition(Vec2::ZERO);
    this->addChild(bg_image);
    event_list.pop_front();
  } else if (!strcmp(name, "SoundEffect")) {
    const char* sound_effect = event->Attribute("effect");
    SimpleAudioEngine::sharedEngine()->playEffect(sound_effect);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroAppear")) {
    std::string hero_name = event->Attribute("hero");
    int x = atoi(event->Attribute("x"));
    int y = atoi(event->Attribute("y"));
    SGDramaSceneHero* hero = SGDramaSceneHero::create(hero_name.c_str());
    hero->setAnchorPoint(Vec2(1.0f, 1.0f));
    hero->setPosition(convertCoordinate(Vec2(x,y)));
    this->addChild(hero);
    event_list.pop_front();
  } else if (!strcmp(name, "HeroMove")) {
	  std::string hero_name = event->Attribute("hero");
	  int target_x = atoi(event->Attribute("x"));
	  int target_y = atoi(event->Attribute("y"));
    SGDramaSceneHero* hero = (SGDramaSceneHero*)this->getChildByName(hero_name.c_str());
    if (hero) {
      hero->moveTo(convertCoordinate(Vec2(target_x,target_x)));
    }

	  event_list.pop_front();
  }
}

Vec2 SGDramaScene::convertCoordinate(Vec2 origin)
{
  Vec2 new_pos;
  
  int zero_x = 54;
  int zero_y = 95;

  float sina = 0.53f;
  float cosa = 0.848f;

  int scale = 13;

  new_pos.x = ((origin.x - zero_x) * sina - (origin.y - zero_y) * cosa) * scale;
  new_pos.y = ((zero_x - origin.x) * cosa + (zero_y - origin.y) * sina) * scale;
  return new_pos;
}